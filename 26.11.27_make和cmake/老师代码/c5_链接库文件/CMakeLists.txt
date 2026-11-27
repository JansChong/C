# 声明所需cmake最低版本
cmake_minimum_required(VERSION 3.8)

#指定项目名称和版本号
project(main VERSION 1.0.0 LANGUAGES C)

# 定义一个变量 SRCDIR，使其值等于当前路径
set(SRCDIR $(pwd))

#指定头文件的路径
include_directories($(SRCDIR)/inc)


#生成main可执行文件,main.c是源文件
add_executable(main ./src/main.c)
#链接库文件
target_link_libraries(main sub)
target_link_libraries(main add)

add_subdirectory(lib/)