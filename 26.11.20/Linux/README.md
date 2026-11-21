### 
1. ubuntu进入 放交叉编译工具 的目录， 运行命令：
    + `sudo tar -xvf aarch64-rk3568-linux-gnu-20231028.tar.xz  -C  /`  解压交叉编译工具到 ubuntu 的 "/" 目录下
    + `echo 'export PATH=/aarch64-rk3568-linux-gnu/bin:$PATH'   >> ~/.bashrc`  配置环境变量
    + `source ~/.bashrc` 让当前终端立即重新加载 Bash 配置文件
    + `aarch64-linux-gcc -v` 输出命令查看是否安装成功， 如果成功输出版本号
2. 交叉编译: 
    + 交叉编译器         要编译的C文件             生成的二进制文件
    + aarch64-linux-gcc   hello.c         -o       hello
3. 文件验证：输入 file 编译出来文件名： 如果显示x86则电脑可执行文件， arm则是开发板可执行文件
()[!交叉编译的指令和文件验证.png]
