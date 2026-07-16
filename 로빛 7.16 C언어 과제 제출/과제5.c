#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 제곱ㄴㄴ수인지 판별하는 함수
int isSquareFree(int x)
{
    for(int i = 2; i * i <= x; i++)
    {
        if(x % (i * i) == 0)
            return 0;
    }
    return 1;
}

int main(void)
{
    int min, max;

    // 올바른 범위가 입력될 때까지 반복
    do
    {
        printf("min : ");
        if(scanf("%d", &min) != 1)
        {
            printf("숫자만 입력 가능합니다.\n");
            return 0;
        }

        printf("max : ");
        if(scanf("%d", &max) != 1)
        {
            printf("숫자만 입력 가능합니다.\n");
            return 0;
        }

        // 범위를 벗어나거나 min > max인 경우
        if(min > max || min < 1 || min > 10000 || max < 1 || max > 10000)
        {
            printf("1~10000 범위에서 min <= max가 되도록 다시 입력하세요.\n");
        }

    } while(min > max || min < 1 || min > 10000 || max < 1 || max > 10000);

    int count = 0;

    // 제곱ㄴㄴ수 개수 계산
    for(int x = min; x <= max; x++)
    {
        if(isSquareFree(x))
            count++;
    }

    printf("제곱ㄴㄴ수 : %d개\n", count);

    // 제곱ㄴㄴ수 출력
    for(int x = min; x <= max; x++)
    {
        if(isSquareFree(x))
            printf("%d ", x);
    }

    printf("\n");

    return 0;
}