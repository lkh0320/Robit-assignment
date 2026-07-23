#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 스택에 저장되는 하나의 노드를 표현하는 구조체이다.
// 실제 데이터와 다음 노드를 가리키는 포인터를 저장하여
// 연결리스트 형태의 스택을 구현하였다.
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 스택 전체를 관리하기 위한 구조체이다.
// top은 가장 위에 있는 노드를 가리키며,
// size는 현재 저장되어 있는 데이터의 개수를 관리한다.
typedef struct Stack {
    Node* top;
    int size;
} Stack;

// 스택을 처음 사용할 수 있도록 초기화하는 함수이다.
// 처음에는 저장된 데이터가 없으므로
// top은 NULL, 크기는 0으로 초기화하였다.
void initStack(Stack* s)
{
    s->top = NULL;
    s->size = 0;
}

// 스택의 가장 위(top)에 새로운 데이터를 추가하는 함수이다.
// 연결리스트를 이용하므로 새로운 노드를 생성한 후
// 기존 top 앞에 연결하는 방식으로 구현하였다.
void push(Stack* s, int data)
{
    // 새로운 데이터를 저장할 노드를 동적으로 생성한다.
    Node* newNode = (Node*)malloc(sizeof(Node));

    // 입력받은 데이터를 저장한다.
    newNode->data = data;

    // 새 노드가 기존 top을 가리키도록 연결한다.
    newNode->next = s->top;

    // 새 노드가 새로운 top이 되도록 변경한다.
    s->top = newNode;

    // 데이터가 하나 추가되었으므로 스택의 크기를 증가시킨다.
    s->size++;
}

// 스택의 가장 위(top)에 있는 데이터를 제거하는 함수이다.
// 스택은 후입선출(LIFO) 구조이므로
// 가장 마지막에 들어온 데이터부터 삭제하도록 구현하였다.
void pop(Stack* s)
{
    // 스택이 비어 있으면 삭제할 데이터가 없으므로 종료한다.
    if (s->top == NULL)
    {
        printf("비어있습니다.\n");
        return;
    }

    // 삭제할 노드를 임시로 저장한다.
    Node* temp = s->top;

    // 삭제되는 데이터를 확인할 수 있도록 출력한다.
    printf("%d\n", temp->data);

    // 두 번째 노드가 새로운 top이 되도록 변경한다.
    s->top = temp->next;

    // 삭제한 노드의 메모리를 반환한다.
    free(temp);

    // 데이터가 하나 제거되었으므로 크기를 감소시킨다.
    s->size--;
}

// 현재 스택의 가장 위(top)에 저장된 데이터를 반환하는 함수이다.
// 데이터를 삭제하지 않고 값만 확인할 때 사용한다.
int top(Stack* s)
{
    // 스택이 비어 있으면 반환할 데이터가 없다.
    if (s->top == NULL)
    {
        printf("비어있습니다.\n");
        return -1;
    }

    return s->top->data;
}

// 현재 스택에 저장된 데이터의 개수를 반환하는 함수이다.
int size(Stack* s)
{
    return s->size;
}

// 스택이 비어 있는지 확인하는 함수이다.
// 비어 있으면 1(true),
// 데이터가 존재하면 0(false)을 반환한다.
int isEmpty(Stack* s)
{
    if (s->top == NULL)
        return 1;

    return 0;
}

// 현재 스택의 모든 데이터를 출력하는 함수이다.
// top부터 마지막 노드까지 순서대로 출력하여
// 현재 스택 상태를 확인할 수 있도록 하였다.
void printStack(Stack* s)
{
    // 출력할 데이터가 없는 경우이다.
    if (s->top == NULL)
    {
        printf("비어있습니다.\n");
        return;
    }

    // 현재 탐색 중인 노드를 저장하는 포인터이다.
    Node* cur = s->top;

    // 마지막 노드까지 이동하면서 데이터를 출력한다.
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

// 프로그램 종료 전에 스택의 모든 노드를 삭제하는 함수이다.
// 동적 메모리를 사용했기 때문에
// 모든 노드를 free()하여 메모리 누수를 방지하였다.
void destroyStack(Stack* s)
{
    // 첫 번째 노드부터 순서대로 메모리를 해제한다.
    Node* cur = s->top;

    while (cur != NULL)
    {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }

    // 모든 노드가 제거되었으므로 초기 상태로 되돌린다.
    s->top = NULL;
    s->size = 0;
}

int main()
{
    // 하나의 스택을 생성하고 사용할 준비를 한다.
    Stack s;
    initStack(&s);

    // 사용자 명령어와 push에 사용할 값을 저장하는 변수이다.
    char cmd[20];
    int value;

    // 사용자가 종료 명령을 입력하기 전까지
    // 여러 명령을 계속 수행할 수 있도록 반복문으로 구현하였다.
    while (1)
    {
        // 사용 가능한 명령어를 출력하여
        // 사용자가 쉽게 기능을 선택할 수 있도록 하였다.
        printf("\n========================\n");
        printf("사용 가능한 명령어\n");
        printf("push [정수]\n");
        printf("pop\n");
        printf("top\n");
        printf("size\n");
        printf("isEmpty\n");
        printf("printStack\n");
        printf("exit\n");
        printf("========================\n");

        printf(">> ");
        scanf("%s", cmd);

        // push 명령이면 저장할 값을 입력받아 스택에 추가한다.
        if (strcmp(cmd, "push") == 0)
        {
            scanf("%d", &value);
            push(&s, value);
        }

        // 가장 위의 데이터를 삭제한다.
        else if (strcmp(cmd, "pop") == 0)
        {
            pop(&s);
        }

        // 가장 위의 데이터를 삭제하지 않고 확인한다.
        else if (strcmp(cmd, "top") == 0)
        {
            if (!isEmpty(&s))
                printf("%d\n", top(&s));
            else
                printf("비어있습니다.\n");
        }

        // 현재 저장된 데이터 개수를 출력한다.
        else if (strcmp(cmd, "size") == 0)
        {
            printf("%d\n", size(&s));
        }

        // 스택이 비어 있는지 확인하여 결과를 출력한다.
        else if (strcmp(cmd, "isEmpty") == 0)
        {
            if (isEmpty(&s))
                printf("true\n");
            else
                printf("false\n");
        }

        // 현재 스택에 저장된 모든 데이터를 출력한다.
        else if (strcmp(cmd, "printStack") == 0)
        {
            printStack(&s);
        }

        // exit 명령이 입력되면 반복문을 종료한다.
        else if (strcmp(cmd, "exit") == 0)
        {
            break;
        }

        // 정의되지 않은 명령어가 입력된 경우이다.
        else
        {
            printf("잘못된 명령어입니다.\n");
        }
    }

    // 프로그램 종료 전에 남아 있는 모든 노드의 메모리를 반환한다.
    destroyStack(&s);

    // 종료 메시지를 출력한다.
    printf("프로그램을 종료합니다.\n");

    return 0;
}