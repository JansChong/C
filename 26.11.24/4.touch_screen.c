#include <stdio.h>
#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // read. close

#include <linux/input.h> // 导入 输入设备 的头文件

#if 0
这是输入设备存储信息的 结构体类型
struct input_event {
      struct timeval time;//事件发生的时间
      __u16 type;//事件的类型   -> 鼠标/键盘/触摸屏
      __u16 code; //事件的编码   -> 对事件进一步的描述  左键/A键/x轴/y轴
      __s32 value;//事件的值
};
#endif

// 定义一个相同类型的结构体, 用来存储触摸数据
// struct input_event buf = {}
// 更正: 因为已经导入了头文件, 所以不需要自己定义结构体, 头文件中有现成的

int main(int argc, char const *argv[])
{
      // 1. 打开触摸屏, 设备名字：/dev/input/event0
      // 更早 终端输入 `cat /proc/bus/input/devices` 找 touchScreen 字段, 我的开发版挂载在event6
      int fd = open("/dev/input/event6", O_RDONLY);
      if (fd < 0)
      {
            perror("打开触摸屏失败");
      }

      // 定义输入类型的结构体 buf, 用来存储触摸数据
      struct input_event buf;

      while (1)
      {
            // 不断读取数据
            read(fd, &buf, sizeof(buf));

            // 输出读取到的 事件类型, 事件代码, 输入的值
            // printf("buf.type = %d\n", buf.type); // 返回3, 类型等于 EV_ABS时, 表示输入事件的类型是 触摸屏 (type可能是一个数组, 因为下标3刚好就是EV_ABS)
            // printf("buf.code = %d\n", buf.code); // 返回1 , code用于对事件的类型作进一步的描述, 当上面的type等于EV_ABS时, code有ABS_X、ABS_Y可选 (可能以0、1表示)
            // printf("buf.value = %d\n", buf.value); // 返回坐标, x或y 需要看code的返回值(ABS_X、ABS_Y)确定
            // 手指移动时, 基本都是输出
            // buf.type = 3
            // buf.code = 1
            // buf.value = x和y坐标

            // 所以:
            int ts_x, ts_y;
            if (buf.type == EV_ABS) // 触摸屏 事件类型
            {
                  if (buf.code == ABS_X)
                  {
                        ts_x = buf.value;
                  }
                  if (buf.code == ABS_Y)
                  {
                        ts_y = buf.value;
                  }
            }
            printf("坐标为: x = %d  y = %d\n", ts_x, ts_y);

            // 另外: 当 type返回EV_KEY时, 可以描述键盘、按键、或类似键盘设备(具体看code确定) 的状态变化,比如按下或松开
            // 当 code 返回 BTN_TOUCH 时, 则可以确认是触摸屏发生了 按下和松开事件
            // 最后: 当满足上面两个条件时, 当value>0表示按下, value=0表示松开

            // 当手指松开时
            if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
            {
                  printf("触摸结束: x = %d  y = %d\n", ts_x, ts_y);
            }
      }

      // 关闭文件
      close(fd);
      return 0;
}