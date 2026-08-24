#include <stdio.h>

void hanoi(int n, char from, char to, char aux);

int main(int argc, char const *argv[])
{
    int n;

    printf("请输入盘子数量: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("盘子数量必须大于 0\n");
        return 1;
    }

    printf("\n将 %d 个盘子从 A 柱移到 C 柱（借助 B 柱）:\n", n);
    hanoi(n, 'A', 'C', 'B');
    printf("\n共需移动 %d 步（理论值: %d）\n", (1 << n) - 1, (1 << n) - 1);

    return 0;
}

/*
 * 汉诺塔递归函数
 * n:    盘子数量
 * from: 源柱
 * to:   目标柱
 * aux:  辅助柱
 *
 * 思路:
 * 1. 把 n-1 个盘子从 from 移到 aux（借助 to）
 * 2. 把最大的盘子从 from 移到 to
 * 3. 把 n-1 个盘子从 aux 移到 to（借助 from）
 */
void hanoi(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        printf("将盘子 1 从 %c 移到 %c\n", from, to);
        return;
    }

    hanoi(n - 1, from, aux, to);
    printf("将盘子 %d 从 %c 移到 %c\n", n, from, to);
    hanoi(n - 1, aux, to, from);
}
