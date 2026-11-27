# 声明所需cmake最低版本
cmake_minimum_required(VERSION 3.8)

#指定项目名称和版本号
project(main VERSION 1.0.0 LANGUAGES C)


#生成main可执行文件,main.c是源文件
add_executable(main main.c)