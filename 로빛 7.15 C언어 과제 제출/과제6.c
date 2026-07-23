#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int input;

    // 출력할 크기 입력
    printf("값을 입력하세요. ");

    // 정수가 아닌 입력 예외 처리
    if (scanf("%d", &input) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 2 미만의 값 입력 예외 처리
    if (input < 2) {
        printf("2 이상의 정수를 입력하세요.\n");
        return 1;
    }

    // X 모양 출력
    for (int i = 1; i < input; i++)
    {
        // 왼쪽 대각선
        for (int j = input; j > 0; j--)
        {
            if (i == j)
                printf("*");
            else
                printf(" ");
        }

        // 오른쪽 대각선
        for (int j = 1; j < input; j++)
        {
            if (i - 1 == j)
                printf("*");
            else
                printf(" ");
        }

        printf("\n");
    }

    // 마지막 가로줄 출력
    for (int i = 0; i < input * 2 - 1; i++)
    {
        printf("*");
    }

    printf("\n");

    return 0;
}