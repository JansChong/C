#include "utils.h"

int w;
int h;
int lcd_fd;
int *map; // 内存映射

#define SCREEN_SIZE (1024 * 600) // 显示屏大小

/**
 * @description: 读取任意大小的 bmp图片，返回 file_buf
 * @param: 要读取的文件
 * @return int * file_buf
 */
int *read_bmp_func(char *img_src)
{

    // 2. 打开图片
    int bmp_fd = open(img_src, O_RDONLY);
    if (bmp_fd == -1)
    {
        perror("open fail");
        return NULL;
    }

    // 添加: 通过bmp_head,获取图片尺寸
    char bmp_head[55] = {0};
    read(bmp_fd, bmp_head, 54);
    // printf("%s\n", bmp_head);

    // 获取图片宽高
    int *width = (int *)(bmp_head + 18);
    int *height = (int *)(bmp_head + 22);
    w = *width;
    h = *height;
    // printf("图片尺寸为 %d * %d\n", w, h); // 成功

    // 2. 读取文件 (图片)
    // 保存图片时，选择的是 bmp格式_24位图(3字节 rgb)_1024*600
    char bmp_buf[w * h * 3];       // char型数组(每个元素1字节), 需要乘3才是完整图片， 因为一个像素点 【BGR】 3个字节，有1024*600像素点
    memset(bmp_buf, 0, w * h * 3); // 用 memset 清零

    // 读取图片要跳过文件头
    // lseek(bmp_fd, 54, SEEK_SET);

    // 一次读取全部数据 到 缓冲区
    read(bmp_fd, bmp_buf, w * h * 3);

    // 定义一个int数组, 每个元素4字节
    // 这个malloc的空间有返回, 后面在main释放
    int *temp_buf = (int *)malloc(sizeof(int) * w * h); // 不用乘4, int数组一个元素有4字节

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // bmp位图上下颠倒，所以 用 (599 - 行数量) 纠正
            temp_buf[w * (h - 1 - i) + j] = bmp_buf[3 * (w * i + j)] | bmp_buf[3 * (w * i + j) + 1] << 8 | bmp_buf[3 * (w * i + j) + 2] << 16 | 0x00 << 24;
        }
    }

    close(bmp_fd);
    return temp_buf;
}

/**
 * @description: LCD 初始化, 整个程序只调用一次
 *               open + mmap 只做一次, 之后所有图片切换共用这块映射,
 *               避免每次切换都 open/mmap 导致 fd 耗尽、内存越吃越多
 * @return 0 成功, -1 失败
 */
int lcd_init(void)
{
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fb0 fail");
        return -1;
    }

    map = mmap(NULL, SCREEN_SIZE * 4, PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (map == MAP_FAILED) // mmap 失败必须检查, 否则后面拿 -1 当地址写会段错误
    {
        perror("mmap fail");
        close(lcd_fd);
        lcd_fd = -1;
        map = NULL;
        return -1;
    }
    return 0;
}

/**
 * @description: 显示图片到指定位置 (不再 open/mmap, 直接复用 lcd_init 建好的映射)
 * @param: {} x 指定x坐标
 * @param: {} y 指定y坐标
 * @return void
 */
void show_image_to_location(int *img_buf, int x, int y)
{
    // 没图或没初始化就直接返回, 防止空指针/野指针导致段错误
    if (img_buf == NULL || map == NULL || map == MAP_FAILED)
    {
        return;
    }

    // 定义一个新的指针, 指向要开始写入的位置
    int *p = map + 1024 * y + x; // 移动指针p, 一行有 1024个像素点 * y行 + x列;  指针在map中指向要写入的坐标
    // 循环遍历小图片的buf, 每一次写入一行, 结束跨下一行
    for (int i = 0; i < h; i++) // 行, 即图片的高度
    {
        for (int j = 0; j < w; j++) // 列, 即图片的宽度
        {
            // lcd一行有1024个像素, image一行有w个像素
            p[1024 * i + j] = img_buf[w * i + j];
        }
    }
}

/**
 * @description: 程序退出时调用一次, 解除映射并关闭 fb0
 */
void lcd_close(void)
{
    if (map != NULL && map != MAP_FAILED)
    {
        munmap(map, SCREEN_SIZE * 4); // 解除内存映射
        map = NULL;
    }
    if (lcd_fd >= 0)
    {
        close(lcd_fd); // 关闭文件
        lcd_fd = -1;
    }
}

// 自己定义的 触摸事件监听
void add_touch_event_listener(void)
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
}

// 触摸屏文件描述符(全局, 给下面函数共用)
static int g_fd = -1;

/* ========= 3. 打开触摸屏 ========= */
int touch_open(const char *dev_path)
{
    g_fd = open(dev_path, O_RDONLY);
    if (g_fd < 0)
    {
        perror("打开触摸屏失败");
        return -1;
    }
    return 0;
}

/* ========= 4. 关闭触摸屏 ========= */
void touch_close(void)
{
    if (g_fd >= 0)
    {
        close(g_fd);
        g_fd = -1;
    }
}

/* ========= 5. 读一次事件, 返回解析结果 ========= */
touch_event_t get_touch_event(void)
{
    touch_event_t result;
    memset(&result, 0, sizeof(result)); // 先清零
    /* 这几个变量要记住上一次的状态, 所以用 static */
    static int is_pressed = 0; // 当前是否按下
    static int start_x = 0;    // 按下那一刻的 x
    static int cur_x = 0;      // 当前 x
    static int cur_y = 0;      // 当前 y
    struct input_event buf;    /* 阻塞读一个事件, 读不到就返回全 0 */
    if (read(g_fd, &buf, sizeof(buf)) != sizeof(buf))
    {
        return result;
    }

    /* --- 处理坐标 --- */ /* 兼容两种上报方式: 老的 ABS_X/ABS_Y 和 多点触控的 ABS_MT_POSITION_X/Y */
    if (buf.type == EV_ABS)
    {
        if (buf.code == ABS_X || buf.code == ABS_MT_POSITION_X)
        {
            cur_x = buf.value;
        }
        else if (buf.code == ABS_Y || buf.code == ABS_MT_POSITION_Y)
        {
            cur_y = buf.value;
        }
    }
    /* --- 处理按下/松开 --- */
    if (buf.type == EV_KEY && buf.code == BTN_TOUCH)
    {
        if (buf.value > 0)
        { /* 按下: 记下起始坐标 */
            is_pressed = 1;
            start_x = cur_x;
        }
        else
        { /* 松开: 判断滑动方向 */
            is_pressed = 0;
            result.released = 1;      // 标记"本次刚松开"
            int dx = cur_x - start_x; // 横向位移
            if (dx > SWIPE_TOLERANCE)
            {
                result.swipe_right = 1; // 往右滑
            }
            else if (dx < -SWIPE_TOLERANCE)
            {
                result.swipe_left = 1; // 往左滑
            } /* 位移在容差内 → 什么都不标, 当作普通点击 */
        }
    }
    /* 把当前状态填进结构体 */
    result.pressed = is_pressed;
    result.x = cur_x;
    result.y = cur_y;
    return result;
}

/**
 * 读取路径下的文件, 存入双向循环链表中
 * @param path 要读取的目标路径, 如 "./"
 * @param file_extension 要读取的文件格式, 如 "bmp"
 * @return 返回顺序表
 */
bool get_dir_designated_file(char *path, char *file_extension)
{

    DIR *dir = opendir(path); //  打开目录以获得 DIR* 形态的目录流（目录指针）， 成功则返回 目录流， 失败返回null
    if (dir == NULL)
    {
        printf("open dir fail\n");
        return false;
    }

    // 字符串拼接 得到 文件后缀
    char *suffix; // .bmp
    sprintf(suffix, ".%s", file_extension);

    // 每个文件的名字
    char path_name[256];

    // 循环读取目录流下的文件，用其返回值类型的变量接收函数的返回值：
    while (1)
    {
        bzero(path_name, 0); //  sprintf 函数不会清空之前的文本, 所以每次循环手动清空一下

        struct dirent *dp = readdir(dir); // 循环读取指定目录下的文件
        // 如果文件读取返回 NULL, 则表示读取失败

        if (dp == NULL)
        {
            printf("读取结束\n");
            closedir(dir); // 关闭目录读取
            return true;
        }

        // 读取指定格式的文件
        if (dp->d_type == DT_REG)
        {
            char *str = strrchr(dp->d_name, '.');        // 找到.的下标, char * 未读取到\0会一直往后读取，直到\0
            if (str != NULL && strcmp(str, suffix) == 0) // 这里是查找目录下所有的.bmp文件
            {
                // printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);

                // "./images/" + ".aaa.bmp"
                sprintf(path_name, "%s%s", path, dp->d_name);

                // printf("%s\n", path_name);
                // 把路径推入循环链表中
                // 头插
                insert_head(banner_list, path_name);
            }
        }
    }
}
