#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 배열에서 B의 위치를 찾는 함수
int findPos(int *A, int N, int B)
{
    for(int i = 1; i <= N; i++)
    {
        if(A[i] == B)
            return i;
    }

    return -1;
}

// 중앙값이 B인 부분수열의 개수를 계산하는 함수
int countMedianSubarrays(int *A, int N, int B)
{
    int posB = findPos(A, N, B);
    int count = 0;

    // 예외처리 : B가 배열에 없는 경우
    if(posB == -1)
        return 0;

    // B를 포함하는 모든 부분수열 검사
    for(int l = 1; l <= posB; l++)
    {
        int greater = 0;
        int less = 0;

        for(int r = l; r <= N; r++)
        {
            // B보다 큰 값과 작은 값의 개수 계산
            if(A[r] > B)
                greater++;
            else if(A[r] < B)
                less++;

            // 큰 값과 작은 값의 개수가 같으면 중앙값이 B
            if(r >= posB && greater == less)
                count++;
        }
    }

    return count;
}

int main(void)
{
    int N, B;
    int A[1001];

    printf("N : ");

    // 예외처리 : N 입력 실패
    if(scanf("%d", &N) != 1)
    {
        printf("입력이 올바르지 않습니다.\n");
        return 0;
    }

    // 예외처리 : 배열 크기 확인
    if(N < 1 || N > 1000)
    {
        printf("N은 1~1000 사이의 값이어야 합니다.\n");
        return 0;
    }

    printf("B : ");

    // 예외처리 : B 입력 실패
    if(scanf("%d", &B) != 1)
    {
        printf("입력이 올바르지 않습니다.\n");
        return 0;
    }

    printf("\n배열 입력\n");

    for(int i = 1; i <= N; )
    {
        int duplicate = 0;

        printf("%d : ", i);

        // 숫자가 아닌 값 입력
        if(scanf("%d", &A[i]) != 1)
        {
            printf("숫자만 입력 가능합니다. 다시 입력하세요.\n");

            // 입력 버퍼 비우기
            while(getchar() != '\n');

            continue;
        }

        // 1 ~ N 범위가 아닌 경우
        if(A[i] < 1 || A[i] > N)
        {
            printf("1부터 %d 사이의 수만 입력 가능합니다. 다시 입력하세요.\n", N);
            continue;
        }

        // 중복 검사
        for(int j = 1; j < i; j++)
        {
            if(A[j] == A[i])
            {
                duplicate = 1;
                break;
            }
        }

        if(duplicate)
        {
            printf("중복된 숫자입니다. 다시 입력하세요.\n");
            continue;
        }

        // 정상 입력이면 다음 위치로 이동
        i++;
    }

    // 결과 계산
    int result = countMedianSubarrays(A, N, B);

    printf("중앙값이 %d인 부분수열의 개수 : %d\n", B, result);

    return 0;
}