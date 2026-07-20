#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;
    int num, count = 1;
    int rmax, cmax;
    int cr, cc;
    int k = 1;
    int *arr;
    int i, j, r;

    // 행과 열 입력
    printf("행렬의 행과 열을 띄어쓰기로 구분하여 입력하세요. ");
    if (scanf("%d %d", &n1, &n2) != 2 || n1 <= 0 || n2 <= 0)
    {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 전체 배열 크기 계산
    num = n1 * n2;

    // 1차원 동적 배열 생성
    arr = (int *)calloc(num, sizeof(int));
    if (arr == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 행렬의 중심 위치 계산
    rmax = n1 / 2;
    cmax = n2 / 2;
    cr = rmax;
    cc = cmax;

    // 중심에 첫 번째 숫자 저장
    arr[cr * n2 + cc] = count++;

    // 중심에서 바깥쪽으로 한 겹씩 채우기
    while (count <= num)
    {
        // 오른쪽 아래 → 아래
        for (r = 1; r <= k && count <= num; r++)
        {
            int c = r - k;

            if (r >= -rmax && r <= rmax &&
                c >= -cmax && c <= cmax)
                arr[(cr + r) * n2 + (cc + c)] = count++;
        }

        // 아래 → 오른쪽 위
        for (r = k - 1; r >= 0 && count <= num; r--)
        {
            int c = k - r;

            if (r >= -rmax && r <= rmax &&
                c >= -cmax && c <= cmax)
                arr[(cr + r) * n2 + (cc + c)] = count++;
        }

        // 오른쪽 위 → 위
        for (r = -1; r >= -k && count <= num; r--)
        {
            int c = k + r;

            if (r >= -rmax && r <= rmax &&
                c >= -cmax && c <= cmax)
                arr[(cr + r) * n2 + (cc + c)] = count++;
        }

        // 위 → 왼쪽 아래
        for (r = -k + 1; r <= 0 && count <= num; r++)
        {
            int c = -k - r;

            if (r >= -rmax && r <= rmax &&
                c >= -cmax && c <= cmax)
                arr[(cr + r) * n2 + (cc + c)] = count++;
        }

        // 다음 바깥 레이어로 이동
        k++;
    }

    // 결과 출력
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            printf("%d  ", arr[i * n2 + j]);
        }
        printf("\n");
    }

    // 동적 메모리 해제
    free(arr);

    return 0;
}