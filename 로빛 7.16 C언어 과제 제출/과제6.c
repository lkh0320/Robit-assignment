#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXN 20

int setArr[MAXN];      // 집합 원소 저장 배열
int setSize = 0;       // 현재 집합의 크기
int present[MAXN + 1]; // 원소 존재 여부 저장

// 원소 추가
void addX(int x)
{
    if (!present[x])
    {
        setArr[setSize++] = x;
        present[x] = 1;
    }
}

// 원소 삭제
void removeX(int x)
{
    if (present[x])
    {
        int idx = -1;

        // 삭제할 원소 위치 찾기
        for (int i = 0; i < setSize; i++)
        {
            if (setArr[i] == x)
            {
                idx = i;
                break;
            }
        }

        // 배열 당기기
        for (int i = idx; i < setSize - 1; i++)
            setArr[i] = setArr[i + 1];

        setSize--;
        present[x] = 0;
    }
}

// 원소 존재 여부 확인
int checkX(int x)
{
    return present[x] ? 1 : 0;
}

// 원소 토글 (있으면 삭제, 없으면 추가)
void toggleX(int x)
{
    if (present[x])
        removeX(x);
    else
        addX(x);
}

// 집합을 {1, 2, ..., 20}으로 설정
void allSet(void)
{
    setSize = 0;

    for (int x = 1; x <= MAXN; x++)
    {
        setArr[setSize++] = x;
        present[x] = 1;
    }
}

// 집합 비우기
void emptySet(void)
{
    setSize = 0;

    for (int x = 1; x <= MAXN; x++)
        present[x] = 0;
}

// 현재 집합 출력
void printSet(void)
{
    printf("집합 : { ");

    for (int i = 0; i < setSize; i++)
        printf("%d ", setArr[i]);

    printf("}\n");
}

int main(void)
{
    char cmd[20];
    int x;

    printf("연산을 선택하세요. (1 <= x <= 20)\n");
    printf("add X\n");
    printf("remove X\n");
    printf("check X\n");
    printf("toggle X\n");
    printf("all 0\n");
    printf("empty 0\n\n");

    printf("input : ");

    while (scanf("%s %d", cmd, &x) == 2)
    {
        // x 범위 예외처리
        if ((strcmp(cmd, "all") != 0 && strcmp(cmd, "empty") != 0)
            && (x < 1 || x > 20))
        {
            printf("x는 1~20 사이의 값만 입력 가능합니다.\n");
            printf("\ninput : ");
            continue;
        }

        if (strcmp(cmd, "add") == 0)
        {
            addX(x);
            printSet();
        }
        else if (strcmp(cmd, "remove") == 0)
        {
            removeX(x);
            printSet();
        }
        else if (strcmp(cmd, "check") == 0)
        {
            printf("%d\n", checkX(x));
        }
        else if (strcmp(cmd, "toggle") == 0)
        {
            toggleX(x);
            printSet();
        }
        else if (strcmp(cmd, "all") == 0)
        {
            allSet();
            printSet();
        }
        else if (strcmp(cmd, "empty") == 0)
        {
            emptySet();
            printSet();
        }
        else
        {
            // 잘못된 명령어 입력
            printf("잘못된 명령어입니다.\n");
        }

        printf("\ninput : ");
    }

    return 0;
}