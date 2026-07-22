#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

int main()
{
    int n;

    printf("입력할 좌표의 개수 : ");
    scanf("%d", &n);

    // 입력받은 좌표 개수만큼 구조체 배열을 동적으로 생성한다.
    // 좌표 개수를 미리 알 수 없기 때문에
    // 실행 중 필요한 크기만큼 메모리를 할당하도록 구현하였다.
    Point* p = (Point*)malloc(sizeof(Point) * n);

    // 메모리 할당에 실패하면
    // 좌표를 저장할 공간이 없으므로 프로그램을 종료한다.
    if (p == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    printf("좌표를 입력하세요.\n");

    // 입력받은 좌표를 구조체 배열에 순서대로 저장한다.
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &p[i].x, &p[i].y);
    }

    // 가장 큰 거리의 합과 해당 좌표의 위치를 저장하기 위한 변수이다.
    double maxSum = 0;
    int maxIndex = 0;

    // 모든 좌표를 기준점으로 한 번씩 선택하여
    // 다른 모든 좌표와의 거리 합을 계산한다.
    for (int i = 0; i < n; i++)
    {
        // 현재 기준 좌표에서 다른 좌표까지의 거리 총합을 저장한다.
        double sum = 0;

        // 현재 기준 좌표와 나머지 모든 좌표를 비교한다.
        for (int j = 0; j < n; j++)
        {
            // 자기 자신과의 거리는 항상 0이므로
            // 계산할 필요가 없어 건너뛰도록 하였다.
            if (i == j)
                continue;

            // 두 좌표 사이의 x축 거리와 y축 거리를 계산한다.
            double dx = p[i].x - p[j].x;
            double dy = p[i].y - p[j].y;

            // 두 점 사이의 거리는 피타고라스 정리를 이용하여 계산하였다.
            // sqrt() 함수를 사용해 실제 직선거리를 구한 후
            // 현재 좌표의 거리 총합에 더한다.
            sum += sqrt(dx * dx + dy * dy);
        }

        // 첫 번째 좌표이거나
        // 현재 계산한 거리의 합이 기존 최대값보다 크다면
        // 최대 거리와 해당 좌표의 위치를 새롭게 저장한다.
        if (i == 0 || sum > maxSum)
        {
            maxSum = sum;
            maxIndex = i;
        }
    }

    // 가장 멀리 떨어져 있는 좌표와
    // 그 좌표에서 다른 모든 좌표까지의 거리 총합을 출력한다.
    printf("\n가장 거리가 먼 좌표는 (%d, %d)이며, 다른 좌표와의 거리 총합은 약 %.1lf입니다.\n",
        p[maxIndex].x, p[maxIndex].y, maxSum);

    // 동적으로 할당한 메모리를 반환하여
    // 메모리 누수가 발생하지 않도록 처리하였다.
    free(p);

    // 프로그램을 정상적으로 종료한다.
    return 0;
}