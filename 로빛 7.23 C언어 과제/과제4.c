#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택에서 사용할 하나의 노드를 표현하는 구조체이다.
// 문자 데이터와 다음 노드의 주소를 저장하여
// 연결리스트 형태의 스택과 큐를 구현하였다.
typedef struct Node
{
    char data;
    struct Node* next;
} Node;

// 스택을 관리하기 위한 구조체이다.
// top은 가장 마지막에 저장된 노드를 가리킨다.
typedef struct
{
    Node* top;
} Stack;

// ==========================================================
// 스택의 가장 위(top)에 문자를 저장하는 함수이다.
// 새로운 노드를 생성한 후
// 기존 top 앞에 연결하는 방식으로 구현하였다.
// ==========================================================
void push(Stack* s, char ch)
{
    // 새로운 노드를 생성한다.
    Node* newNode = (Node*)malloc(sizeof(Node));

    // 입력받은 문자를 저장한다.
    newNode->data = ch;

    // 새 노드가 기존 top을 가리키도록 연결한다.
    newNode->next = s->top;

    // 새 노드를 새로운 top으로 변경한다.
    s->top = newNode;
}

// ==========================================================
// 스택의 가장 위(top)에 있는 문자를 꺼내는 함수이다.
// 스택은 후입선출(LIFO) 구조이므로
// 가장 마지막에 저장된 문자를 반환한다.
// ==========================================================
char pop(Stack* s)
{
    // 삭제할 노드를 임시로 저장한다.
    Node* temp = s->top;

    // 반환할 문자를 저장한다.
    char ch = temp->data;

    // 다음 노드가 새로운 top이 되도록 변경한다.
    s->top = temp->next;

    // 사용이 끝난 노드의 메모리를 반환한다.
    free(temp);

    return ch;
}

// ==========================================================
// 스택이 비어 있는지 확인하는 함수이다.
// ==========================================================
int stackEmpty(Stack* s)
{
    return s->top == NULL;
}

// 큐를 관리하기 위한 구조체이다.
// front는 가장 먼저 저장된 노드를,
// rear는 가장 마지막 노드를 가리킨다.
typedef struct
{
    Node* front;
    Node* rear;
} Queue;

// ==========================================================
// 큐의 뒤(rear)에 새로운 문자를 저장하는 함수이다.
// 큐는 선입선출(FIFO) 구조이므로
// 항상 마지막 위치에 데이터를 추가한다.
// ==========================================================
void enqueue(Queue* q, char ch)
{
    // 새로운 노드를 생성한다.
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = ch;
    newNode->next = NULL;

    // 큐가 비어 있으면 첫 번째 노드가 된다.
    if (q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        // 기존 마지막 노드 뒤에 새 노드를 연결한다.
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// ==========================================================
// 큐의 가장 앞(front)에 있는 문자를 꺼내는 함수이다.
// 먼저 들어온 문자부터 반환하도록 구현하였다.
// ==========================================================
char dequeue(Queue* q)
{
    // 삭제할 노드를 임시로 저장한다.
    Node* temp = q->front;

    // 반환할 문자를 저장한다.
    char ch = temp->data;

    // 다음 노드가 새로운 front가 되도록 변경한다.
    q->front = temp->next;

    // 마지막 노드까지 삭제했다면
    // rear도 NULL로 변경한다.
    if (q->front == NULL)
        q->rear = NULL;

    // 사용이 끝난 노드의 메모리를 반환한다.
    free(temp);

    return ch;
}

// ==========================================================
// 큐가 비어 있는지 확인하는 함수이다.
// ==========================================================
int queueEmpty(Queue* q)
{
    return q->front == NULL;
}

int main()
{
    // 스택과 큐를 모두 초기 상태로 생성한다.
    Stack s = { NULL };
    Queue q = { NULL, NULL };

    // 입력받을 문자열을 저장하는 배열이다.
    char str[100];

    printf("문자열 입력 : ");

    // 공백을 포함한 문자열을 입력받는다.
    fgets(str, sizeof(str), stdin);

    // 문자열의 모든 문자를 하나씩 확인한다.
    for (int i = 0; str[i] != '\0'; i++)
    {
        // 공백과 엔터는 회문 판단에 필요하지 않으므로 제외하였다.
        if (str[i] == ' ' || str[i] == '\n')
            continue;

        char ch = str[i];

        // 대문자는 모두 소문자로 변환하여
        // 대소문자와 관계없이 비교하도록 구현하였다.
        if (ch >= 'A' && ch <= 'Z')
            ch = ch + ('a' - 'A');

        // 같은 문자를 스택과 큐에 모두 저장한다.
        // 스택은 역순,
        // 큐는 원래 순서를 유지하게 된다.
        push(&s, ch);
        enqueue(&q, ch);
    }

    // 회문 여부를 저장하는 변수이다.
    // 처음에는 회문이라고 가정한다.
    int palindrome = 1;

    // 스택과 큐에서 하나씩 문자를 꺼내 비교한다.
    // 앞에서 읽은 문자와 뒤에서 읽은 문자가 모두 같으면
    // 회문이 된다.
    while (!stackEmpty(&s))
    {
        if (pop(&s) != dequeue(&q))
        {
            // 하나라도 다르면 회문이 아니다.
            palindrome = 0;
            break;
        }
    }

    if (palindrome)
        printf("회문입니다.\n");
    else
        printf("회문이 아닙니다.\n");

    return 0;
}