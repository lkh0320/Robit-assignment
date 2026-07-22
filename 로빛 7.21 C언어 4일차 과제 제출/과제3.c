#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[30];
    int price;
} Item;

int main()
{
    // 입력받을 상품의 개수를 저장하는 변수이다.
    int n;

    printf("입력 : ");
    scanf("%d", &n);

    // 상품 개수만큼 구조체 배열을 동적으로 생성한다.
    // 입력 개수를 미리 알 수 없기 때문에
    // 실행 중 필요한 크기만큼 메모리를 할당하도록 구현하였다.
    Item* item = (Item*)malloc(sizeof(Item) * n);

    // 메모리 할당에 실패하면
    // 이후 데이터를 저장할 수 없으므로 프로그램을 종료한다.
    if (item == NULL)
    {
        printf("메모리 할당 실패");
        return 1;
    }

    // 각 상품의 이름과 가격을 입력받아
    // 구조체 배열에 차례대로 저장한다.
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", item[i].name, &item[i].price);
    }

    // 검색할 상품 이름을 저장하는 배열이다.
    char search[30];

    // 사용자가 찾고 싶은 상품 이름을 입력받는다.
    scanf("%s", search);

    // 같은 이름을 가진 상품들의 가격 합계를 저장하는 변수이다.
    int sum = 0;

    // 저장된 모든 상품을 하나씩 확인하면서
    // 입력한 이름과 같은 상품인지 비교한다.
    for (int i = 0; i < n; i++)
    {
        // 현재 비교 중인 문자열의 위치를 나타내는 변수이다.
        int j = 0;

        // 두 문자열을 문자 하나씩 비교한다.
        // strcmp()를 사용하지 않고
        // 문자열 비교 과정을 직접 구현하였다.
        while (1)
        {
            // 서로 다른 문자가 나오면
            // 같은 이름이 아니므로 비교를 종료한다.
            if (item[i].name[j] != search[j])
                break;

            // 두 문자열이 동시에 끝났다면
            // 이름이 완전히 일치하는 경우이므로
            // 해당 상품의 가격을 합계에 더한다.
            if (item[i].name[j] == '\0' && search[j] == '\0')
            {
                sum += item[i].price;
                break;
            }

            // 다음 문자도 계속 비교한다.
            j++;
        }
    }

    // 같은 이름을 가진 상품들의 가격 합계를 출력한다.
    printf("%d\n", sum);

    // 동적으로 할당한 메모리를 반환하여
    // 메모리 누수가 발생하지 않도록 처리하였다.
    free(item);

    // 프로그램을 정상적으로 종료한다.
    return 0;
}