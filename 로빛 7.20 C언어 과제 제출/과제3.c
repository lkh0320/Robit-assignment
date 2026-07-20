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

    printf("행 입력 : ");
    scanf("%d", &n1);

    printf("열 입력 : ");
    scanf("%d", &n2);

    // 동적할당
    A = (int **)malloc(n1 * sizeof(int *));
    for(i = 0; i < n1; i++)
    {
        A[i] = (int *)malloc(n2 * sizeof(int));
    }

    top = 0;
    bottom = n1 - 1;
    left = 0;
    right = n2 - 1;

    while(top <= bottom && left <= right)
    {
        // 위
        for(j = left; j <= right; j++)
            A[top][j] = num++;
        top++;

        // 오른쪽
        for(i = top; i <= bottom; i++)
            A[i][right] = num++;
        right--;

        // 아래
        if(top <= bottom)
        {
            for(j = right; j >= left; j--)
                A[bottom][j] = num++;
            bottom--;
        }

        // 왼쪽
        if(left <= right)
        {
            for(i = bottom; i >= top; i--)
                A[i][left] = num++;
            left++;
        }
    }

    // 출력
    for(i = 0; i < n1; i++)
    {
        for(j = 0; j < n2; j++)
        {
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }

    // 메모리 해제
    for(i = 0; i < n1; i++)
        free(A[i]);
    free(A);

    return 0;
}