#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 큐에 저장되는 하나의 노드를 표현하는 구조체이다.
// 데이터와 다음 노드의 주소를 저장하여
// 연결리스트 형태의 큐를 구현하였다.
typedef struct Node
{
    int data;
    struct Node* next;
} Node;

// 큐 전체를 관리하기 위한 구조체이다.
// front는 가장 먼저 들어온 데이터를,
// rear는 가장 마지막에 들어온 데이터를 가리키며,
// size는 현재 저장된 데이터의 개수를 관리한다.
typedef struct Queue
{
    Node* front;
    Node* rear;
    int size;
} Queue;

// 큐를 처음 사용할 수 있도록 초기화하는 함수이다.
// 처음에는 저장된 데이터가 없으므로
// front와 rear를 NULL로 설정하고
// 크기를 0으로 초기화하였다.
void initQueue(Queue* q)
{
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// 큐의 가장 뒤(rear)에 새로운 데이터를 추가하는 함수이다.
// 큐는 선입선출(FIFO) 구조이므로
// 항상 마지막 위치에 새로운 노드를 연결하도록 구현하였다.
void enqueue(Queue* q, int data)
{
    // 저장할 데이터를 위한 새로운 노드를 생성한다.
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    // 큐가 비어 있는 경우에는
    // 첫 번째 노드가 되므로 front와 rear가 모두 같은 노드를 가리킨다.
    if (q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        // 기존 마지막 노드 뒤에 새 노드를 연결하고
        // rear를 새 노드로 변경한다.
        q->rear->next = newNode;
        q->rear = newNode;
    }

    // 데이터가 하나 추가되었으므로 크기를 증가시킨다.
    q->size++;
}

// 큐의 가장 앞(front)에 있는 데이터를 삭제하는 함수이다.
// 큐는 먼저 들어온 데이터부터 제거하는
// FIFO 방식으로 구현하였다.
void dequeue(Queue* q)
{
    // 큐가 비어 있으면 삭제할 데이터가 없다.
    if (q->front == NULL)
    {
        printf("비어있습니다.\n");
        return;
    }

    // 삭제할 노드를 임시로 저장한다.
    Node* temp = q->front;

    // 삭제되는 데이터를 출력한다.
    printf("%d\n", temp->data);

    // 두 번째 노드가 새로운 front가 되도록 변경한다.
    q->front = temp->next;

    // 마지막 노드까지 삭제한 경우에는
    // rear도 NULL로 변경하여 빈 큐 상태를 유지한다.
    if (q->front == NULL)
        q->rear = NULL;

    // 삭제한 노드의 메모리를 반환한다.
    free(temp);

    // 데이터 개수를 감소시킨다.
    q->size--;
}

// 큐의 가장 앞(front)에 있는 데이터를 반환하는 함수이다.
// 데이터를 삭제하지 않고 값만 확인할 때 사용한다.
int front(Queue* q)
{
    if (q->front == NULL)
    {
        printf("비어있습니다.\n");
        return -1;
    }

    return q->front->data;
}

// 큐의 가장 뒤(rear)에 있는 데이터를 반환하는 함수이다.
// 가장 마지막에 입력된 값을 확인할 때 사용한다.
int rear(Queue* q)
{
    if (q->rear == NULL)
    {
        printf("비어있습니다.\n");
        return -1;
    }

    return q->rear->data;
}

// 현재 큐에 저장되어 있는 데이터의 개수를 반환하는 함수이다.
int size(Queue* q)
{
    return q->size;
}

// 큐가 비어 있는지 확인하는 함수이다.
// 비어 있으면 1(true),
// 데이터가 존재하면 0(false)을 반환한다.
int isEmpty(Queue* q)
{
    return q->front == NULL;
}

// 현재 큐에 저장된 데이터를 앞(front)부터 뒤(rear)까지
// 순서대로 출력하는 함수이다.
void printQueue(Queue* q)
{
    if (q->front == NULL)
    {
        printf("비어있습니다.\n");
        return;
    }

    // 현재 탐색 중인 노드를 저장하는 포인터이다.
    Node* cur = q->front;

    // 마지막 노드까지 이동하면서 데이터를 출력한다.
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

// 프로그램 종료 전에 큐에 남아 있는 모든 노드를 삭제하는 함수이다.
// 동적 메모리를 사용했기 때문에
// 모든 노드를 free()하여 메모리 누수를 방지하였다.
void destroyQueue(Queue* q)
{
    // 첫 번째 노드부터 순서대로 메모리를 해제한다.
    Node* cur = q->front;

    while (cur != NULL)
    {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }

    // 큐를 초기 상태로 되돌린다.
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int main()
{
    // 하나의 큐를 생성하고 초기화한다.
    Queue q;
    initQueue(&q);

    // 사용자 명령어와 enqueue에 사용할 값을 저장하는 변수이다.
    char cmd[20];
    int value;

    // 사용자가 종료 명령을 입력하기 전까지
    // 여러 기능을 반복해서 수행할 수 있도록 구현하였다.
    while (1)
    {
        // 사용 가능한 명령어를 출력한다.
        printf("사용 가능한 명령어\n");
        printf("enqueue [정수]\n");
        printf("dequeue\n");
        printf("front\n");
        printf("rear\n");
        printf("size\n");
        printf("isEmpty\n");
        printf("printQueue\n");
        printf("exit\n\n");

        printf(">> ");
        scanf("%s", cmd);

        // 새로운 데이터를 큐의 뒤쪽에 추가한다.
        if (strcmp(cmd, "enqueue") == 0)
        {
            scanf("%d", &value);
            enqueue(&q, value);
        }

        // 가장 먼저 들어온 데이터를 삭제한다.
        else if (strcmp(cmd, "dequeue") == 0)
        {
            dequeue(&q);
        }

        // 가장 앞에 있는 데이터를 출력한다.
        else if (strcmp(cmd, "front") == 0)
        {
            if (!isEmpty(&q))
                printf("%d\n", front(&q));
            else
                printf("비어있습니다.\n");
        }

        // 가장 뒤에 있는 데이터를 출력한다.
        else if (strcmp(cmd, "rear") == 0)
        {
            if (!isEmpty(&q))
                printf("%d\n", rear(&q));
            else
                printf("비어있습니다.\n");
        }

        // 현재 저장된 데이터 개수를 출력한다.
        else if (strcmp(cmd, "size") == 0)
        {
            printf("%d\n", size(&q));
        }

        // 큐가 비어 있는지 확인한다.
        else if (strcmp(cmd, "isEmpty") == 0)
        {
            if (isEmpty(&q))
                printf("true\n");
            else
                printf("false\n");
        }

        // 큐에 저장된 모든 데이터를 출력한다.
        else if (strcmp(cmd, "printQueue") == 0)
        {
            printQueue(&q);
        }

        // 종료 명령이 입력되면 반복문을 종료한다.
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
    destroyQueue(&q);

    printf("프로그램을 종료합니다.\n");

    return 0;
}