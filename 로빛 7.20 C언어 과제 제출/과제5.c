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

    // 행 입력
    printf("행 입력 : ");
    if (scanf("%d", &row) != 1 || row <= 0)
    {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 열 입력
    printf("열 입력 : ");
    if (scanf("%d", &col) != 1 || col <= 0)
    {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 2차원 배열 동적 할당
    A = (int **)malloc(row * sizeof(int *));
    if (A == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    for (i = 0; i < row; i++)
    {
        A[i] = (int *)malloc(col * sizeof(int));

        // 메모리 할당 실패
        if (A[i] == NULL)
        {
            printf("메모리 할당 실패\n");

            // 이미 할당한 메모리 해제
            for (j = 0; j < i; j++)
                free(A[j]);
            free(A);

            return 1;
        }
    }

    // 대각선 방향으로 숫자 채우기
    for (i = 0; i < row + col - 1; i++)
    {
        // 시작 위치 설정
        if (i < col)
        {
            r = 0;
            c = i;
        }
        else
        {
            r = i - col + 1;
            c = col - 1;
        }

        // 왼쪽 아래 방향으로 이동하며 숫자 저장
        while (r < row && c >= 0)
        {
            A[r][c] = num++;
            r++;
            c--;
        }
    }

    // 배열 출력
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            printf("%3d", A[i][j]);
        printf("\n");
    }

    // 동적 메모리 해제
    for (i = 0; i < row; i++)
        free(A[i]);
    free(A);

    return 0;
}