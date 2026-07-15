#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    int year;

    // 연도 입력
    printf("년도를 입력하세요 : ");

    // 정수가 아닌 값 입력 시 예외 처리
    if (scanf("%d", &year) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 음수 또는 0 입력 시 예외 처리
    if (year <= 0) {
        printf("1 이상의 연도를 입력하세요.\n");
        return 1;
    }

    // 윤년 판별
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        printf("윤년\n");
    } else {
        printf("평년\n");
    }

    return 0;
}