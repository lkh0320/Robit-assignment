#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int A[4][3];
    int B[3][4];
    int i, j;
    int num = 1;

    // 배열 A 채우기
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 3; j++)
        {
            A[i][j] = num++;
        }
    }

    // 배열 B에 행과 열 바꾸어 저장
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 3; j++)
        {
            B[j][i] = A[i][j];
        }
    }

    // 배열 A 출력
    printf("배열 A\n");
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }

    // 배열 B 출력
    printf("\n배열 B\n");
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 4; j++)
        {
            printf("%3d", B[i][j]);
        }
        printf("\n");
    }

    return 0;
}