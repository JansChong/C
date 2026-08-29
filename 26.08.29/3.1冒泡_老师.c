#include "stdio.h"


/*
 * 功能：冒泡排序
 * 参数：arr :保存数列的数组
 *      size: 数组的元素个数
 * 返回值：null
*/
void Bubble_sort(int arr[], int size)
{
    for(int j = size - 1 ; j > 0; j --)
    {
        for(int i = 0; i < j; i++)
        {
            if(arr[i] > arr[i+1])
            {//前面的值比后面的大，则交换位置
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }




    // for(int i = 0; i < 4; i++)
    // {
    //     if(arr[i] > arr[i+1])
    //     {//前面的值比后面的大，则交换位置
    //         int temp = arr[i];
    //         arr[i] = arr[i+1];
    //         arr[i+1] = temp;
    //     }
    // }

    // for(int i = 0; i < 3; i++)
    // {
    //     if(arr[i] > arr[i+1])
    //     {//前面的值比后面的大，则交换位置
    //         int temp = arr[i];
    //         arr[i] = arr[i+1];
    //         arr[i+1] = temp;
    //     }
    // }



//     if(arr[0] > arr[1])
//     {//前面的值比后面的大，则交换位置
//         int temp = arr[0];
//         arr[0] = arr[1];
//         arr[1] = temp;
//     }

//     if(arr[1] > arr[2])
//     {//前面的值比后面的大，则交换位置
//         int temp = arr[1];
//         arr[1] = arr[2];
//         arr[2] = temp;
//     }

// ...

//     if(arr[3] > arr[4])
//     {//前面的值比后面的大，则交换位置
//         int temp = arr[3];
//         arr[3] = arr[4];
//         arr[4] = temp;
//     }



}


int main()
{
    int arr[] = {7, 80, 20, -9, 46, 55, -100, 50, 21};
    Bubble_sort(arr, sizeof(arr)/4);    
    for(int i = 0; i < sizeof(arr)/4; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}