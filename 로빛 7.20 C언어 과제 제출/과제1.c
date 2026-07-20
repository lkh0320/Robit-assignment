#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int arr[5][5];
    int i, j;
    int num = 1;

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(i == 0 || i == 4)
                arr[i][j] = num++;
            else if(i == 1 && j >= 1 && j <= 3)
                arr[i][j] = num++;
            else if(i == 2 && j == 2)
                arr[i][j] = num++;
            else if(i == 3 && j >= 1 && j <= 3)
                arr[i][j] = num++;
            else
                arr[i][j] = 0;
        }
    }

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}