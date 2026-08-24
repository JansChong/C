#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    // 选一个不大不小的尺寸：4000 字节 ≈ 1000 个 int
    // 这个尺寸在 macOS 上属于 small 块，不走 mmap，堆里原地切分概率极高
    size_t N = 1000;
    int *p = (int *)malloc(N * sizeof(int));
    if (!p) { perror("malloc"); return 1; }

    printf("=== 第一步：malloc(%zu 字节)，地址 p = %p ===\n",
           N * sizeof(int), (void *)p);

    // 把整块内存全部写成明显的标记值 0xdeadbeef
    for (size_t i = 0; i < N; i++) {
        p[i] = (int)0xdeadbeef;
    }
    printf("已将全部 %zu 个 int 写为 0xdeadbeef\n\n", N);

    // 第二步：realloc 缩小到 4 个 int（16 字节）
    // 分配器会把后面的 996 个 int 切下来放回空闲链表，但页面还在使用中
    int *p2 = (int *)realloc(NULL, 4 * sizeof(int));
    if (!p2) { perror("realloc缩小"); free(p); return 1; }
    p = p2;
    printf("=== 第二步：realloc 缩小到 16 字节，地址 p = %p ===\n", (void *)p);

    // 把前 4 个改成正常值，方便区分
    for (int i = 0; i < 4; i++) {
        p[i] = i;
    }
    printf("前 4 个 int 已设置为 0,1,2,3\n\n");

    // 第三步：realloc 再扩大回原来的 1000 个 int
    // 这时候大概率原地扩展，后面的 996 个 int 就是刚才写过的 0xdeadbeef
    int *p3 = (int *)realloc(NULL, N * sizeof(int));
    if (!p3) { perror("realloc扩大"); free(p); return 1; }
    p = p3;
    printf("=== 第三步：realloc 再扩大回 %zu 字节，地址 p = %p ===\n",
           N * sizeof(int), (void *)p);

    // 打印前 4 个（应该保留 0,1,2,3）
    printf("\n前 4 个 int（realloc 保证保留）：\n");
    for (int i = 0; i < 4; i++) {
        printf("  p[%d] = %d\n", i, p[i]);
    }

    // 采样打印后面的部分，并统计
    printf("\n新扩展部分（从 i=4 开始）采样：\n");
    int dirty_cnt = 0, zero_cnt = 0, other_cnt = 0;
    for (size_t i = 4; i < N; i++) {
        unsigned v = (unsigned)p[i];
        if (v == 0xdeadbeef) dirty_cnt++;
        else if (v == 0) zero_cnt++;
        else other_cnt++;

        // 只打印前 20 个和每隔 200 个采样，避免刷屏
        if (i < 20 || i % 200 == 0) {
            printf("  p[%3zu] = 0x%08x  %s\n", i, v,
                   v == 0xdeadbeef ? "← 就是刚才写的脏数据！" :
                   v == 0 ? "← 碰巧是0" : "← 其他垃圾值");
        }
    }

    printf("\n==== 统计结果 ====\n");
    printf("新扩展的 %zu 个 int 中：\n", N - 4);
    printf("  0xdeadbeef（残留脏数据）：%d 个\n", dirty_cnt);
    printf("  0x00000000：%d 个\n", zero_cnt);
    printf("  其他值：%d 个\n", other_cnt);

    if (dirty_cnt > 0) {
        printf("\n✅ 结论：realloc 扩展出的新内存保留了之前写入的数据，");
        printf("证明它【不会】初始化新内存！\n");
        printf("   （你看到的 0xdeadbeef 就是第一步写进去的，realloc 没有清零它）\n");
    } else {
        printf("\n⚠️  本次扩大时发生了内存移动（realloc 分配了全新区域），\n");
        printf("   请再运行一次，原地扩展的概率非常高。\n");
    }

    free(p);
    return 0;
}
