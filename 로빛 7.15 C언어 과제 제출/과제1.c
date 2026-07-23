#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    float user_response[5] = { 0 };   // 사용자 입력 저장 배열
    float max, min;
    float sum = 0;                    // 합계는 0으로 초기화

    // 실수 5개 입력
    for (int i = 0; i < 5; i++) {
        printf("%d 번째 실수를 입력하시오. ", i + 1);

        // 입력이 실수가 아니면 오류 처리
        if (scanf("%f", &user_response[i]) != 1) {
            printf("잘못된 입력입니다. 실수를 입력해주세요.\n");
            return 1;
        }

        // 첫 번째 입력으로 최대/최소값 초기화
        if (i == 0) {
            max = min = user_response[i];
        }
        // 최대값 갱신
        else if (user_response[i] > max) {
            max = user_response[i];
        }
        // 최소값 갱신
        else if (user_response[i] < min) {
            min = user_response[i];
        }
    }

    // 평균 계산을 위한 합계
    for (int i = 0; i < 5; i++) {
        sum += user_response[i];
    }
    sum /= 5;

    // 결과 출력
    printf("---- 결과 ----\n");
    printf("평균은 %.6f입니다.\n", sum);
    printf("최대값은 %.6f입니다.\n", max);
    printf("최소값은 %.6f입니다.\n", min);

    return 0;
}