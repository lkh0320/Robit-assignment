#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int input;

    // 출력할 별의 크기 입력
    printf("값을 입력하세요. ");

    // 정수가 아닌 입력 예외 처리
    if (scanf("%d", &input) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 1 이하의 값 입력 예외 처리
    if (input < 1) {
        printf("1 이상의 정수를 입력하세요.\n");
        return 1;
    }

    // 윗부분 출력
    for (int i = 0; i < input; i++) {

        // 왼쪽 삼각형
        for (int j = 0; j < input; j++) {
            if (i >= j)
                printf("*");
            else
                printf(" ");
        }

        // 오른쪽 삼각형
        for (int j = input - 1; j >= 0; j--) {
            if (i >= j)
                printf("*");
            else
                printf(" ");
        }

        printf("\n");
    }

    // 아랫부분 출력
    for (int i = input - 2; i >= 0; i--) {

        // 왼쪽 삼각형
        for (int j = 0; j < input; j++) {
            if (i >= j)
                printf("*");
            else
                printf(" ");
        }

        // 오른쪽 삼각형
        for (int j = input - 1; j >= 0; j--) {
            if (i >= j)
                printf("*");
            else
                printf(" ");
        }

        printf("\n");
    }

    return 0;
}