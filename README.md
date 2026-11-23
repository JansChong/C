# C
C语言&amp;嵌入式学习


修改浏览器内容: document.documentElement.contentEditable = true


数据结构 + 算法 = 程序


在设置中将默认终端改为 Git Bash：
按 Ctrl + Shift + P 打开命令面板。
输入 Terminal: Select Default Profile。
选择 ‌Git Bash‌。

中国大陆下载加速： GitHub 直连慢或超时的话，给下载地址加一个公共加速前缀即可，例如把 Releases 页复制出来的链接改成 https://ghfast.top/https://github.com/Yudaotor/lyrimuse/releases/download/…。镜像域名可能会失效，失效了就换一个可用的 gh-proxy 类前缀（用法相同，都是原链接前面加前缀）


沈华龙: 【有道云笔记】GZ2634
https://share.note.youdao.com/s/AMtJbdk8


1BIT, 1BYTE, 1KB, 1MB, 1GB, 1TB
mac连接开发板: 
1. 网线直连, 终端输入 `networksetup -listallhardwareports` 查看mac用哪个网卡连接的开发板, 
      + 能看到"以太网 / USB 10/100/1000 LAN"对应的设备名，
      + 比如`en3` 。 记住这个名字 ，下面假设是`en3`
2. 给这块网卡配上和开发板同网段的 IP
      + 方法 A: 系统设置 → 网络 → 选中那块"USB 以太网 / 以太网"网卡 → 详细信息 → TCP/IP：
            `配置 IPv4:  手动
            IP 地址:   192.168.63.1
            子网掩码:  255.255.255.0
            路由器:    留空（直连不需要网关）`
      + 方法 B: 命令行（临时，重启失效，先验证用）
            `sudo ifconfig en3 192.168.63.1 netmask 255.255.255.0 up`
3. 测试连通性
      + 先看这块网卡地址配上去了没 ifconfig en3 
      + ping 开发板 ping 192.168.63.72
4. 通了之后: ssh 开发板用户名@192.168.63.72