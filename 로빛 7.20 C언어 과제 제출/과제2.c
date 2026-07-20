#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ROW_A 4
#define COL_A 3
#define ROW_B 3
#define COL_B 4

int main()
{
    int A[ROW_A][COL_A];
    int B[ROW_B][COL_B];
    int i, j;
    int num = 1;

    // 배열 크기가 맞는지 확인
    if (ROW_A != COL_B || COL_A != ROW_B)
    {
        printf("행렬의 크기가 맞지 않습니다.\n");
        return 1;
    }

    // 배열 A를 1부터 순서대로 채움
    for (i = 0; i < ROW_A; i++)
    {
        for (j = 0; j < COL_A; j++)
        {
            A[i][j] = num++;
        }
    }

    // 배열 A를 전치하여 배열 B에 저장
    for (i = 0; i < ROW_A; i++)
    {
        for (j = 0; j < COL_A; j++)
        {
            B[j][i] = A[i][j];
        }
    }

    // 배열 A 출력
    printf("배열 A\n");
    for (i = 0; i < ROW_A; i++)
    {
        for (j = 0; j < COL_A; j++)
        {
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }

    // 배열 B 출력
    printf("\n배열 B\n");
    for (i = 0; i < ROW_B; i++)
    {
        for (j = 0; j < COL_B; j++)
        {
            printf("%3d", B[i][j]);
        }
        printf("\n");
    }

    return 0;
}