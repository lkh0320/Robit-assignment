#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 5

int main()
{
    int arr[SIZE][SIZE];
    int i, j;
    int num = 1;

    // 배열에 숫자 채우기
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            // 첫 번째 줄과 마지막 줄은 모두 숫자 저장
            if (i == 0 || i == SIZE - 1)
                arr[i][j] = num++;

            // 두 번째 줄의 가운데 3칸
            else if (i == 1 && j >= 1 && j <= 3)
                arr[i][j] = num++;

            // 가운데 한 칸
            else if (i == 2 && j == 2)
                arr[i][j] = num++;

            // 네 번째 줄의 가운데 3칸
            else if (i == 3 && j >= 1 && j <= 3)
                arr[i][j] = num++;

            // 숫자가 들어가지 않는 곳은 0 저장
            else
                arr[i][j] = 0;
        }
    }

    // 예외처리(배열 크기 확인)
    if (SIZE <= 0)
    {
        printf("배열의 크기가 올바르지 않습니다.\n");
        return 1;
    }

    // 배열 출력
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}