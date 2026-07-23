#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// 팩토리얼 계산 함수
int facto(int a) {
    int fac = 1;

    for (int i = 1; i <= a; i++) {
        fac *= i;
    }

    return fac;
}

int main(void)
{
    int n, r;
    int P, II, C, H;

    // n 입력
    printf("n값을 입력하세요. ");
    if (scanf("%d", &n) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // r 입력
    printf("r값을 입력하세요. ");
    if (scanf("%d", &r) != 1) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 입력값 예외 처리
    if (n < 0 || r < 0) {
        printf("n과 r은 0 이상의 정수여야 합니다.\n");
        return 1;
    }

    if (r > n) {
        printf("r은 n보다 클 수 없습니다.\n");
        return 1;
    }

    // 순열, 중복순열, 조합, 중복조합 계산
    P = facto(n) / facto(n - r);
    II = (int)pow(n, r);
    C = facto(n) / (facto(n - r) * facto(r));
    H = facto(n + r - 1) / (facto(n - 1) * facto(r));

    // 결과 출력
    printf("P(%d, %d) = %d\n", n, r, P);
    printf("II(%d, %d) = %d\n", n, r, II);
    printf("C(%d, %d) = %d\n", n, r, C);
    printf("H(%d, %d) = %d\n", n, r, H);

    return 0;
}