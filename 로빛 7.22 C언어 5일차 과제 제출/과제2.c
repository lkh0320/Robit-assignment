#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 달팽이 형태로 배열에 값을 저장하는 함수
void arr_ij(int *sizeRow, int *sizeCol, int **pArr);

// 완성된 배열을 출력하는 함수
void print(int *row, int *col, int **pArr);

int main()
{
    // 2차원 동적 배열을 가리키는 포인터이다.
    int **arr = NULL;

    // 행과 열의 크기를 저장하는 변수이다.
    int row, col, sizeRow, sizeCol;

    printf("열의 수를 입력하세요 : ");
    scanf("%d", &sizeCol);

    printf("행의 수를 입력하세요 : ");
    scanf("%d", &sizeRow);

    // 입력받은 값을 출력과 메모리 해제에 사용할 수 있도록 저장하였다.
    row = sizeRow;
    col = sizeCol;

    // 사용자가 입력한 크기만큼만 메모리를 사용하기 위해
    // 실행 중 2차원 배열을 동적으로 생성하였다.
    // 먼저 행의 개수만큼 포인터 배열을 생성한 후,
    // 각 행마다 열의 개수만큼 메모리를 할당하였다.
    arr = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
        arr[i] = (int *)malloc(col * sizeof(int));

    // 생성한 배열에 숫자를 달팽이 모양으로 저장한다.
    arr_ij(&sizeRow, &sizeCol, arr);

    // 완성된 배열을 화면에 출력한다.
    print(&row, &col, arr);

    // 동적으로 할당한 메모리를 모두 반환한다.
    // 각 행을 먼저 해제한 후 마지막에 포인터 배열을 해제하여
    // 메모리 누수가 발생하지 않도록 처리하였다.
    for (int i = 0; i < row; i++)
        free(arr[i]);
    free(arr);

    // 프로그램을 정상적으로 종료한다.
    return 0;
}

void arr_ij(int *sizeRow, int *sizeCol, int **pArr)
{
    // 현재 채워야 할 영역의 위, 아래, 왼쪽, 오른쪽 경계를 저장한다.
    // 숫자를 한 바퀴 채울 때마다 경계를 안쪽으로 이동시켜
    // 자연스럽게 달팽이 모양이 만들어지도록 구현하였다.
    int top = 0;
    int bottom = *sizeRow - 1;
    int left = 0;
    int right = *sizeCol - 1;

    // 배열에 순서대로 저장할 숫자이다.
    int num = 1;

    // 아직 채워야 할 영역이 남아 있는 동안 반복한다.
    while (top <= bottom && left <= right)
    {
        // 현재 가장 위쪽 행을 왼쪽에서 오른쪽 방향으로 채운다.
        for (int j = left; j <= right; j++)
            pArr[top][j] = num++;

        // 위쪽 행을 모두 채웠으므로
        // 다음 반복에서는 한 줄 아래부터 시작한다.
        top++;

        // 현재 가장 오른쪽 열을 위에서 아래 방향으로 채운다.
        for (int i = top; i <= bottom; i++)
            pArr[i][right] = num++;

        // 오른쪽 열을 모두 채웠으므로
        // 경계를 한 칸 왼쪽으로 이동시킨다.
        right--;

        // 아직 아래쪽 행이 남아 있는 경우에만
        // 오른쪽에서 왼쪽 방향으로 값을 채운다.
        if (top <= bottom)
        {
            for (int j = right; j >= left; j--)
                pArr[bottom][j] = num++;

            // 아래쪽 행도 모두 채웠으므로
            // 경계를 한 칸 위로 이동시킨다.
            bottom--;
        }

        // 아직 왼쪽 열이 남아 있는 경우에만
        // 아래에서 위 방향으로 값을 채운다.
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
                pArr[i][left] = num++;

            // 왼쪽 열까지 모두 채웠으므로
            // 경계를 한 칸 오른쪽으로 이동시킨다.
            left++;
        }
    }
}

void print(int *row, int *col, int **pArr)
{
    // 배열의 모든 원소를 행과 열 순서대로 출력한다.
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *col; j++)
            // 출력 폭을 4칸으로 맞춰
            // 숫자의 자릿수가 달라도 배열 형태가 유지되도록 하였다.
            printf("%4d", pArr[i][j]);

        printf("\n");
    }
}