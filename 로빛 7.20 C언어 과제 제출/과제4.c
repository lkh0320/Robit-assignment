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

    printf("몇 개의 원소를 할당하겠습니까? : ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    for(i = 0; i < n; i++)
    {
        printf("정수 데이터 입력 : ");
        scanf("%d", &arr[i]);
    }

    max = arr[0];
    min = arr[0];

    for(i = 0; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];

        if(arr[i] < min)
            min = arr[i];

        sum += arr[i];
    }

    avg = (float)sum / n;

    printf("\n최댓값 : %d\n", max);
    printf("최솟값 : %d\n", min);
    printf("전체합 : %d\n", sum);
    printf("평균 : %.6f\n", avg);

    free(arr);

    return 0;
}