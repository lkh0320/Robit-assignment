#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **A;
    int n1, n2;
    int i, j;
    int x, y;
    int num = 1;
    int step = 1;
    int dir = 0;

    // 아래, 오른쪽, 위, 왼쪽
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    printf("행 열 입력 : ");
    scanf("%d %d", &n1, &n2);

    A = (int **)malloc(n1 * sizeof(int *));
    for(i = 0; i < n1; i++)
        A[i] = (int *)malloc(n2 * sizeof(int));

    // 0으로 초기화
    for(i = 0; i < n1; i++)
        for(j = 0; j < n2; j++)
            A[i][j] = 0;

    // 중앙부터 시작
    x = n1 / 2;
    y = n2 / 2;
    A[x][y] = num++;

    while(num <= n1 * n2)
    {
        int k;

        for(k = 0; k < 2; k++)
        {
            int s;

            for(s = 0; s < step; s++)
            {
                x += dx[dir];
                y += dy[dir];

                if(x >= 0 && x < n1 && y >= 0 && y < n2)
                    A[x][y] = num++;

                if(num > n1 * n2)
                    break;
            }

            dir = (dir + 1) % 4;

            if(num > n1 * n2)
                break;
        }

        step++;
    }

    // 출력
    for(i = 0; i < n1; i++)
    {
        for(j = 0; j < n2; j++)
            printf("%3d", A[i][j]);
        printf("\n");
    }

    // 메모리 해제
    for(i = 0; i < n1; i++)
        free(A[i]);
    free(A);

    return 0;
}