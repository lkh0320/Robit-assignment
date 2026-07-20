#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 배열의 현재 상태를 출력하는 함수
void printArray(int arr[], int size)
{
    int i;

    for(i = 0; i < size; i++)
        printf("%3d", arr[i]);

    printf("\n");
}

// 선택 정렬(Selection Sort) 함수
void selectionSort(int arr[], int size)
{
    int i, j;
    int max, temp;
    int sorted = 0;

    // 뒤에서부터 하나씩 정렬
    for(i = size - 1; i > 0; i--)
    {
        max = 0;

        // 0~i 구간에서 최댓값의 위치 찾기
        for(j = 1; j <= i; j++)
        {
            if(arr[j] > arr[max])
                max = j;
        }

        // 최댓값을 현재 위치(i)와 교환
        temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;

        // 중간 정렬 과정 출력
        printArray(arr, size);

        // 배열이 이미 오름차순인지 확인
        sorted = 1;
        for(j = 0; j < size - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                sorted = 0;
                break;
            }
        }

        // 이미 정렬되어 있으면 반복 종료
        if(sorted)
            break;
    }
}

int main(void)
{
    int arr[8];
    int i;

    printf("입력\n");

    // 배열 입력
    for(i = 0; i < 8; i++)
    {
        printf("%d : ", i);

        // 예외처리 : 숫자가 아닌 값 입력 시 종료
        if(scanf("%d", &arr[i]) != 1)
        {
            printf("숫자만 입력 가능합니다.\n");
            return 0;
        }
    }

    printf("\n정렬 과정\n");
    printArray(arr, 8);

    // 선택 정렬 수행
    selectionSort(arr, 8);

    printf("\n정렬 결과\n");
    for(i = 0; i < 8; i++)
        printf("%d : %d\n", i, arr[i]);

    return 0;
}