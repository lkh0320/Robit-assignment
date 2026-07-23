#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define ASCENDING  1
#define DESCENDING 2
#define MIXED      3

// 입력된 음계의 순서를 판별하는 함수
int checkOrder(char *order)
{
    char asc[] = "cdefgabC";   // 오름차순
    char desc[] = "Cbagfedc";  // 내림차순

    // 오름차순인지 확인
    if(strcmp(order, asc) == 0)
        return ASCENDING;

    // 내림차순인지 확인
    else if(strcmp(order, desc) == 0)
        return DESCENDING;

    // 둘 다 아니면 mixed
    else
        return MIXED;
}

int main(void)
{
    char order[9];

    printf("음 입력\n");

    // 예외처리 : 문자열 입력 실패 시 종료
    if(scanf("%8s", order) != 1)
    {
        printf("입력이 올바르지 않습니다.\n");
        return 0;
    }

    // 음계 순서 판별
    int result = checkOrder(order);

    printf("\n결과 : ");

    // 판별 결과 출력
    switch(result)
    {
    case ASCENDING:
        printf("ascending\n");
        break;

    case DESCENDING:
        printf("descending\n");
        break;

    case MIXED:
        printf("mixed\n");
        break;
    }

    return 0;
}