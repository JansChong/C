#include "stdio.h"

/*
 * 功能：选择排序
 * 参数：arr :保存数列的数组
 *      size: 数组的元素个数
 * 返回值：null
*/
void Selection_sort(int arr[], int size)
{
    for(int j = 0; j < size - 1; j++)
    {
        int min = arr[j];
        for(int i = 1 + j; i < size; i++)
        {
            if(min < arr[i])
            {

            }
            else
            {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                min = arr[j];
            }
        }
    }
    


    // int min = arr[1];
    // for(int i = 2; i < size - 1 - 1; i++)
    // {
    //     if(min < arr[i])
    //     {

    //     }
    //     else
    //     {
    //         int temp = arr[1];
    //         arr[1] = arr[i];
    //         arr[i] = temp;
    //         min = arr[1];
    //     }
    // }




    // if(min < arr[1])
    // {

    // }
    // else
    // {
    //     int temp = arr[0];
    //     arr[0] = arr[1];
    //     arr[1] = temp;
    //     min = arr[0];
    // }


    // if(min < arr[2])
    // {

    // }
    // else
    // {
    //     int temp = arr[0];
    //     arr[0] = arr[2];
    //     arr[2] = temp;
    //     min = arr[0];
    // }
    
    // if(min < arr[3])
    // {

    // }
    // else
    // {
    //     int temp = arr[0];
    //     arr[0] = arr[3];
    //     arr[3] = temp;
    //     min = arr[0];
    // }

    // if(min < arr[4])
    // {

    // }
    // else
    // {
    //     int temp = arr[0];
    //     arr[0] = arr[4];
    //     arr[4] = temp;
    //     min = arr[0]
    // }






}





int main()
{
    int arr[] = {55, 44, 33, -22, 11};
    Selection_sort(arr, sizeof(arr)/4);    
    for(int i = 0; i < sizeof(arr)/4; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}