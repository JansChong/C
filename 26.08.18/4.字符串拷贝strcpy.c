#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    // 头文件 <string.h>
    // 函数原型 char *strcpy(char *dest, const char *src);
    // 说明：strcpy() 会将参数 src 字符串拷贝至参数 dest 所指的地址。
    // 返回值：返回参数 dest 的字符串起始地址。
    // 附加说明：如果参数 dest 所指的内存空间不够大，可能会造成缓冲溢出（buffer Overflow）的错误情况，在编写程序时请特别留意，或者用 strncpy() 来取代。

        


    // strcpy(char * dest, const char *src);
    // strncpy(char * dest, const char *src, size_t n);   拷贝n个有效字符, 如果n个里面包含\0就拷贝 否则不拷贝


    // 注意: strcpy函数会把第二个字符串的结束符一起拷贝，但是使用的时候，必须要保证前面字符串申请的地址空间要足够大 
        // 定义一个长度为10的字符串 "a x 10"
        char teststr[10] = "aaaaaaaaaa";
        printf("%s\n", teststr);

        // 拷贝 "hello" 到上面的字符串, 会拷贝末尾的\0
        char *afterstr = "hello";

        char *res = strcpy(teststr, afterstr);       

        // 以 %d, 查看字符串每一项的 ascii, 发现第六位是 0
        // printf("%s\n", teststr); // %s读取到\0就结束了， 所以得用 %c逐个查看， 否则只能读取到 "hello\0"
        // printf("%s\n", res);// %s读取到\0就结束了， 所以得用 %c逐个查看， 否则只能读取到 "hello\0"

        for (int i = 0; i < 10; i++)
        {
            printf("%c: %d\n", teststr[i], teststr[i]);  // 第6位读取到 \0 空字符串
            printf("%c: %d\n", res[i], res[i]);  // 第6位读取到 \0 空字符串
        }
    
    
        
    // 注意:不能拿字符指针常量来做为strcpy函数的第一个参数    (本质是把一个地址中的值, 拷贝赋值另一个地址,  常量地址是不可以修改的)

}







/*
# strcpy 与 strncpy 主要区别

```
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
```

## 1. 参数不同

- **strcpy**：只有目标地址`dest`、源地址`src`，**没有长度参数**。
- **strncpy**：多了第三个参数`n`，代表最多拷贝**n 个字节**。

## 2. 拷贝逻辑

### strcpy

从`src`逐个字节复制到`dest`，**直到遇到 `\0` 结束，会把末尾的`\0`也复制过去**。

> 
> ⚠️风险：不会检查 dest 缓冲区大小，如果 src 字符串长度 ≥ dest 缓冲区，**缓冲区溢出（越界写），内存破坏，安全漏洞**。

### strncpy(dest, src, n)

1. 如果 `src` 的长度 **小于 n**：拷贝全部字符，后面剩余空间填充`\0`，直到写满 n 字节。
2. 如果 `src` 的长度 **大于等于 n**：只拷贝 n 个字符，**⚠️不会自动追加字符串结束符`\0`**！此时 dest 不是合法 C 字符串，后续`printf、strlen`等函数会越界访问内存。

> 
> 重点坑：strncpy 不保证目标字符串带`\0`，需要手动处理。

## 3. 安全性

- `strcpy`：**不安全**，极易缓冲区溢出，现代开发尽量避免。
- `strncpy`：相对安全，但不是万能，存在上面提到的**缺少结束符**的陷阱。

## 4. 返回值

两者都返回 dest 的首地址。

## 简单示例

```
char buf[5];
strcpy(buf, "abcdef"); // 溢出！buf只有5字节，源字符串6字节+\0

strncpy(buf, "abcdef", 5);
// 拷贝5个字节 'a','b','c','d','e'，**没有'\0'**，buf不是正常字符串
buf[4] = '\0'; // 必须手动补结束符！
```

## 总结对比表

表格

| 特性 | strcpy | strncpy |
| --- | --- | --- |
| 长度限制 | 无 | 最多拷贝 n 字节 |
| 是否拷贝`\0` | 会，遇到`\0`停止 | src 长度 < n 才补`\0`；否则不补 |
| 缓冲区溢出风险 | 很高 | 可控，但要手动处理结束符 |
| 停止条件 | 读到 src 的`\0` | 读满 n 字节 或读到 src 的`\0` |

> 
> 💡工程建议：
> strncpy 使用后，务必手动给缓冲区最后一位赋值`\0`；现代 C 更推荐`strlcpy`（glibc/bsd），会保证末尾带结束符。

*/