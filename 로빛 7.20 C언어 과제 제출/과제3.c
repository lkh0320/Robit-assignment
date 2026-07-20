#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;
    int **A;
    int i, j;
    int top, bottom, left, right;
    int num = 1;

    // 행 입력
    printf("행 입력 : ");
    if (scanf("%d", &n1) != 1 || n1 <= 0)
    {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 열 입력
    printf("열 입력 : ");
    if (scanf("%d", &n2) != 1 || n2 <= 0)
    {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 2차원 배열 동적 할당
    A = (int **)malloc(n1 * sizeof(int *));
    if (A == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    for (i = 0; i < n1; i++)
    {
        A[i] = (int *)malloc(n2 * sizeof(int));

        // 메모리 할당 실패
        if (A[i] == NULL)
        {
            printf("메모리 할당 실패\n");

            // 이미 할당된 메모리 해제
            for (j = 0; j < i; j++)
                free(A[j]);
            free(A);

            return 1;
        }
    }

    // 시작 위치 설정
    top = 0;
    bottom = n1 - 1;
    left = 0;
    right = n2 - 1;

    // 달팽이 모양으로 숫자 저장
    while (top <= bottom && left <= right)
    {
        // 위쪽 행
        for (j = left; j <= right; j++)
            A[top][j] = num++;
        top++;

        // 오른쪽 열
        for (i = top; i <= bottom; i++)
            A[i][right] = num++;
        right--;

        // 아래쪽 행
        if (top <= bottom)
        {
            for (j = right; j >= left; j--)
                A[bottom][j] = num++;
            bottom--;
        }

        // 왼쪽 열
        if (left <= right)
        {
            for (i = bottom; i >= top; i--)
                A[i][left] = num++;
            left++;
        }
    }

    // 결과 출력
    printf("\n");
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }

    // 동적 메모리 해제
    for (i = 0; i < n1; i++)
        free(A[i]);
    free(A);

    return 0;
}