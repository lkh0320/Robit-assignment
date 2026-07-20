#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **A;
    int row, col;
    int i, j;
    int r, c;
    int num = 1;

    printf("행 입력 : ");
    scanf("%d", &row);

    printf("열 입력 : ");
    scanf("%d", &col);

    A = (int **)malloc(row * sizeof(int *));
    for(i = 0; i < row; i++)
        A[i] = (int *)malloc(col * sizeof(int));

    // 대각선 채우기
    for(i = 0; i < row + col - 1; i++)
    {
        if(i < col)
        {
            r = 0;
            c = i;
        }
        else
        {
            r = i - col + 1;
            c = col - 1;
        }

        while(r < row && c >= 0)
        {
            A[r][c] = num++;
            r++;
            c--;
        }
    }

    // 출력
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
            printf("%3d", A[i][j]);
        printf("\n");
    }

    // 메모리 해제
    for(i = 0; i < row; i++)
        free(A[i]);
    free(A);

    return 0;
}