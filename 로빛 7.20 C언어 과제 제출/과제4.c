#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr;
    int n;
    int i;
    int max, min;
    int sum = 0;
    float avg;

    // 원소 개수 입력
    printf("몇 개의 원소를 할당하겠습니까? : ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 동적 메모리 할당
    arr = (int *)malloc(n * sizeof(int));

    // 메모리 할당 실패
    if (arr == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 배열에 데이터 입력
    for (i = 0; i < n; i++)
    {
        printf("정수 데이터 입력 : ");

        if (scanf("%d", &arr[i]) != 1)
        {
            printf("잘못된 입력입니다.\n");
            free(arr);
            return 1;
        }
    }

    // 첫 번째 값을 최대, 최소값으로 초기화
    max = arr[0];
    min = arr[0];

    // 최대값, 최소값, 합계 계산
    for (i = 0; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];

        if (arr[i] < min)
            min = arr[i];

        sum += arr[i];
    }

    // 평균 계산
    avg = (float)sum / n;

    // 결과 출력
    printf("\n최댓값 : %d\n", max);
    printf("최솟값 : %d\n", min);
    printf("전체합 : %d\n", sum);
    printf("평균 : %.6f\n", avg);

    // 동적 메모리 해제
    free(arr);

    return 0;
}