#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 절댓값을 반환하는 함수
int myAbs(int x) {
    return (x < 0) ? -x : x;
}

// 1번 모양 출력
void printType1(int n) {
    for (int i = 1; i <= n; i++) {
        // 위에서부터 증가하다가 중간 이후 감소하도록 별 개수 계산
        int count = (i < n - i + 1) ? i : n - i + 1;

        for (int j = 0; j < count; j++)
            printf("*");

        printf("\n");
    }
}

// 2번 모양 출력 (오른쪽 정렬)
void printType2(int n) {
    for (int i = 1; i <= n; i++) {
        int count = (i < n - i + 1) ? i : n - i + 1;
        int space = n - count;

        // 공백 출력
        for (int j = 0; j < space; j++)
            printf(" ");

        // 별 출력
        for (int j = 0; j < count; j++)
            printf("*");

        printf("\n");
    }
}

// 3번 모양 출력 (가운데가 가장 좁은 모양)
void printType3(int n) {
    int mid = (n + 1) / 2;

    for (int i = 1; i <= n; i++) {
        int dist = myAbs(mid - i);      // 가운데 줄과의 거리
        int count = 2 * dist + 1;       // 출력할 별 개수
        int space = (n - count) / 2;    // 앞 공백 개수

        for (int j = 0; j < space; j++)
            printf(" ");

        for (int j = 0; j < count; j++)
            printf("*");

        printf("\n");
    }
}

// 4번 모양 출력
void printType4(int n) {
    int i, j;

    // 위쪽
    for (i = (n + 1) / 2; i >= 1; i--) {

        for (j = 0; j < (n + 1) / 2 - i; j++)
            printf(" ");

        for (j = 0; j < i; j++)
            printf("*");

        printf("\n");
    }

    // 아래쪽
    for (i = 2; i <= (n + 1) / 2; i++) {

        for (j = 0; j < (n - 1) / 2; j++)
            printf(" ");

        for (j = 0; j < i; j++)
            printf("*");

        printf("\n");
    }
}

int main(void) {
    int n, type;

    printf("사이즈와 종류를 입력하시오. ");
    scanf("%d %d", &n, &type);

    // 예외처리 : n은 홀수이면서 1 이상이어야 함
    if (n < 1 || n % 2 == 0) {
        printf("사이즈는 1 이상의 홀수만 입력 가능합니다.\n");
        return 0;
    }

    // 예외처리 : 종류는 1~4만 허용
    if (type < 1 || type > 4) {
        printf("종류는 1~4 사이의 값이어야 합니다.\n");
        return 0;
    }

    // 입력한 종류에 따라 해당 모양 출력
    switch (type) {
    case 1:
        printType1(n);
        break;

    case 2:
        printType2(n);
        break;

    case 3:
        printType3(n);
        break;

    case 4:
        printType4(n);
        break;
    }

    return 0;
}