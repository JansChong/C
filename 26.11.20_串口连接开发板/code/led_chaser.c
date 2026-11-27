/*
 * RK3568 四LED交替闪烁程序
 * 使用 Linux sysfs GPIO 接口控制 4 个 LED
 *
 * 编译方法 (在开发板上):
 *   gcc -o led_chaser led_chaser.c
 *
 * 运行:
 *   ./led_chaser
 *   按 Ctrl+C 退出
 *
 * 注意: 需要 root 权限操作 GPIO
 *   sudo ./led_chaser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

/* ============================================================
 * 根据你的 gpioinfo 输出，gpiochip3 上有 5 个 sysfs 引脚:
 *   GPIO 111, 120, 121, 123, 124  (都在 gpiochip3 / GPIO3)
 *
 * 对应关系:
 *   GPIO111 = GPIO3_15
 *   GPIO120 = GPIO3_24
 *   GPIO121 = GPIO3_25
 *   GPIO123 = GPIO3_27
 *   GPIO124 = GPIO3_28
 *
 * 默认使用其中 4 个作为 LED (120, 121, 123, 124)
 * 如果不对，可以尝试换成 111, 120, 121, 123
 * 或者通过命令行参数指定: ./led_chaser 111 120 121 123
 * ============================================================ */

/* 默认 4 个 LED 对应的 GPIO 编号 (根据你的板子实测) */
static int led_gpios[] = {120, 121, 123, 124};  /* GPIO3_24, 25, 27, 28 */
#define LED_COUNT (sizeof(led_gpios) / sizeof(led_gpios[0]))

/* LED 点亮电平: 1=高电平点亮, 0=低电平点亮 (根据实际电路调整) */
#define LED_ACTIVE_LEVEL  1

/* 闪烁间隔 (毫秒) */
#define BLINK_DELAY_MS    300

static volatile int running = 1;

/* SIGINT 信号处理 */
static void sig_handler(int sig)
{
    (void)sig;
    running = 0;
}

/* 导出 GPIO */
static int gpio_export(int gpio)
{
    char buf[64];
    int fd, len;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        /* 可能已经导出过了, 不视为致命错误 */
        if (errno == EBUSY)
            return 0;
        fprintf(stderr, "无法导出 GPIO%d: %s\n", gpio, strerror(errno));
        return -1;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    if (write(fd, buf, len) < 0 && errno != EBUSY) {
        fprintf(stderr, "写入 export GPIO%d 失败: %s\n", gpio, strerror(errno));
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* 取消导出 GPIO */
static int gpio_unexport(int gpio)
{
    char buf[64];
    int fd, len;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "打开 unexport 失败: %s\n", strerror(errno));
        return -1;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    if (write(fd, buf, len) < 0) {
        /* 忽略错误, 可能本来就没导出 */
    }
    close(fd);
    return 0;
}

/* 设置 GPIO 方向 */
static int gpio_set_direction(int gpio, const char *direction)
{
    char path[128];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpio);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "打开 direction GPIO%d 失败: %s\n", gpio, strerror(errno));
        return -1;
    }

    if (write(fd, direction, strlen(direction)) < 0) {
        fprintf(stderr, "设置 direction GPIO%d 失败: %s\n", gpio, strerror(errno));
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* 设置 GPIO 输出值 */
static int gpio_set_value(int gpio, int value)
{
    char path[128];
    int fd;
    char val = value ? '1' : '0';

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "打开 value GPIO%d 失败: %s\n", gpio, strerror(errno));
        return -1;
    }

    if (write(fd, &val, 1) < 0) {
        fprintf(stderr, "写入 value GPIO%d 失败: %s\n", gpio, strerror(errno));
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* 点亮指定 LED */
static void led_on(int index)
{
    if (index >= 0 && index < (int)LED_COUNT)
        gpio_set_value(led_gpios[index], LED_ACTIVE_LEVEL);
}

/* 熄灭指定 LED */
static void led_off(int index)
{
    if (index >= 0 && index < (int)LED_COUNT)
        gpio_set_value(led_gpios[index], !LED_ACTIVE_LEVEL);
}

/* 熄灭所有 LED */
static void led_all_off(void)
{
    int i;
    for (i = 0; i < (int)LED_COUNT; i++)
        led_off(i);
}

/* 初始化所有 LED */
static int led_init(void)
{
    int i;
    for (i = 0; i < (int)LED_COUNT; i++) {
        if (gpio_export(led_gpios[i]) < 0)
            return -1;
        /* 小延时确保 sysfs 节点创建完成 */
        usleep(10000);
        if (gpio_set_direction(led_gpios[i], "out") < 0)
            return -1;
        led_off(i);
    }
    return 0;
}

/* 清理所有 LED */
static void led_cleanup(void)
{
    int i;
    led_all_off();
    for (i = 0; i < (int)LED_COUNT; i++) {
        gpio_unexport(led_gpios[i]);
    }
}

/* 打印用法 */
static void print_usage(const char *prog)
{
    fprintf(stderr, "用法: %s [GPIO1 GPIO2 GPIO3 GPIO4]\n", prog);
    fprintf(stderr, "  不指定参数时使用默认 GPIO 编号\n");
    fprintf(stderr, "  示例: %s 124 125 126 127\n", prog);
}

int main(int argc, char *argv[])
{
    int i;
    int pattern = 0;  /* 0=流水灯, 1=呼吸交替(奇数/偶数), 2=全部闪烁 */

    /* 解析命令行参数: 支持传入自定义 GPIO 编号 */
    if (argc > 1) {
        if (argc != 5) {
            print_usage(argv[0]);
            return 1;
        }
        for (i = 0; i < 4; i++) {
            led_gpios[i] = atoi(argv[i + 1]);
        }
    }

    printf("RK3568 四LED交替闪烁程序\n");
    printf("========================\n");
    printf("使用的 GPIO 编号: ");
    for (i = 0; i < (int)LED_COUNT; i++)
        printf("%d ", led_gpios[i]);
    printf("\n");
    printf("LED 有效电平: %s\n", LED_ACTIVE_LEVEL ? "高电平" : "低电平");
    printf("闪烁间隔: %d ms\n", BLINK_DELAY_MS);
    printf("按 Ctrl+C 退出\n\n");

    /* 注册信号处理 */
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    /* 初始化 LED */
    if (led_init() < 0) {
        fprintf(stderr, "LED 初始化失败!\n");
        fprintf(stderr, "请确认: \n");
        fprintf(stderr, "  1. 你是否有 root 权限 (sudo)\n");
        fprintf(stderr, "  2. GPIO 编号是否正确\n");
        fprintf(stderr, "  3. GPIO 是否被其他驱动占用\n");
        led_cleanup();
        return 1;
    }

    printf("LED 初始化成功, 开始交替闪烁...\n");

    /* 主循环: 交替点亮模式 */
    while (running) {
        /* ---- 模式1: 流水灯 (从左到右依次点亮) ---- */
        for (i = 0; i < (int)LED_COUNT && running; i++) {
            led_all_off();
            led_on(i);
            usleep(BLINK_DELAY_MS * 1000);
        }

        if (!running) break;

        /* ---- 模式2: 流水灯 (从右到左依次点亮) ---- */
        for (i = LED_COUNT - 1; i >= 0 && running; i--) {
            led_all_off();
            led_on(i);
            usleep(BLINK_DELAY_MS * 1000);
        }

        if (!running) break;

        /* ---- 模式3: 奇偶交替 (亮灭交替) ---- */
        for (pattern = 0; pattern < 4 && running; pattern++) {
            led_all_off();
            if (pattern % 2 == 0) {
                /* 偶数位亮: LED0, LED2 */
                led_on(0);
                led_on(2);
            } else {
                /* 奇数位亮: LED1, LED3 */
                led_on(1);
                led_on(3);
            }
            usleep(BLINK_DELAY_MS * 1000);
        }

        if (!running) break;

        /* ---- 模式4: 全部一起闪烁 ---- */
        for (pattern = 0; pattern < 3 && running; pattern++) {
            for (i = 0; i < (int)LED_COUNT; i++)
                led_on(i);
            usleep(BLINK_DELAY_MS * 1000);

            if (!running) break;

            led_all_off();
            usleep(BLINK_DELAY_MS * 1000);
        }
    }

    printf("\n正在退出, 关闭所有 LED...\n");
    led_cleanup();
    printf("已退出\n");

    return 0;
}
