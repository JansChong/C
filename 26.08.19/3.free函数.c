#include <stdio.h>

int main(int argc, char const *argv[])
{

      int *p = malloc(4);

      // 释放: 小尺寸空间释放, 仅是把空间标记为空闲, 并没有解除内存映射
      // free 没有返回值  (返回void)
      free(p);

      // 小空间释放后 仍然可以使用, 但是 是未定义行为
      *p = 50;
      printf("*p = %p, %d\n", p, *p);

      // 继续申请, 仍然可以申请到原来的空间
      int *p = malloc(4);



      int *p2 = malloc(1024*1024);
      free(p2);
      // 如果释放的是一个大尺寸空间, 那么free会解除内存映射, 后续无法解引用访问
      *p2 = 10;  // 段错误

      // 大空间再申请, 不一定能申请到原来的空间, 这里涉及最适应算法 和 最算法
}
