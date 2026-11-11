#include <stdio.h>
#include "sequential.h"

int main(int argc, char const *argv[])
{

    // 初始化
    Seq_type_p list = init_list(10);

    // 输入和显示
    input_and_show_list(list);
}