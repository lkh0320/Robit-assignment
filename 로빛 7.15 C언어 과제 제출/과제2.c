#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int fn_1 = 0;      // 현재 피보나치 수
    int fn_2 = 1;      // 다음 피보나치 수
    int n;

    printf("피보나치 수 n번째를 입력하세요. (n >= 2): ");

    // n이 2 이상이 될 때까지 반복 입력
    do
    {
        if (scanf("%d", &n) != 1) {
            printf("잘못된 입력입니다.\n");
            return 1;
        }

        if (n < 2) {
            printf("n이 2보다 작습니다. 다시 입력하세요: ");
        }

    } while (n < 2);

    // 피보나치 수 계산
    for (int i = 1; i < n; i++)
    {
        fn_1 = fn_1 + fn_2;
        fn_2 = fn_1 - fn_2;
    }

    // 결과 출력
    printf("피보나치 수열의 %d번째 항은 %d입니다.\n", n, fn_1);

    return 0;
}