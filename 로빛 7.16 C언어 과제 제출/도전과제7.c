#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 문자열에서 부분 문자열의 모든 위치를 찾는 함수
void findAllPositions(char *str, char *sub)
{
    char *p = str;
    int found = 0;

    printf("%s의 위치 : ", sub);

    // 부분 문자열을 반복해서 검색
    while ((p = strstr(p, sub)) != NULL)
    {
        int pos = (int)(p - str) + 1;   // 1부터 시작하는 위치 계산
        printf("%d ", pos);
        found = 1;
        p += 1;     // 다음 위치부터 다시 검색(겹치는 문자열도 검색)
    }

    // 찾지 못한 경우
    if (!found)
        printf("찾는 문자열이 없습니다.");

    printf("\n");
}

int main(void)
{
    char inputStr[100];
    char subStr[100];

    printf("최대 99개 문자 입력 <inputStr> : ");

    // 예외처리 : 입력 실패
    if (scanf("%99s", inputStr) != 1)
    {
        printf("입력이 올바르지 않습니다.\n");
        return 0;
    }

    printf("찾는 문자열 <subStr> : ");

    // 예외처리 : 입력 실패
    if (scanf("%99s", subStr) != 1)
    {
        printf("입력이 올바르지 않습니다.\n");
        return 0;
    }

    // 예외처리 : 찾는 문자열이 원본 문자열보다 긴 경우
    if (strlen(subStr) > strlen(inputStr))
    {
        printf("찾는 문자열이 원본 문자열보다 깁니다.\n");
        return 0;
    }

    // 부분 문자열의 위치 출력
    findAllPositions(inputStr, subStr);

    return 0;
}