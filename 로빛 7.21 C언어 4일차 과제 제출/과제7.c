#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 연결리스트에서 사용할 노드 구조체
// 하나의 노드는 실제 데이터를 저장하는 data와
// 다음 노드의 위치를 저장하는 link로 구성하였다.
// 단순 연결리스트이므로 이전 노드의 주소는 저장하지 않는다.
typedef struct Node
{
    int data;              // 노드가 저장할 실제 데이터
    struct Node* link;     // 다음 노드를 연결하기 위한 포인터
} Node;

// 리스트의 시작 위치를 항상 가리키기 위한 포인터이다.
// 처음에는 아무 노드도 존재하지 않으므로 NULL로 초기화하였다.
Node* head = NULL;

// 새로운 노드를 생성하는 함수
// 노드를 삽입할 때마다 동일한 생성 과정을 반복하지 않기 위해
// 별도의 함수로 분리하였다.
// 생성과 동시에 데이터 초기화와 link 초기화를 함께 수행하여
// 이후 삽입 함수에서는 연결 작업만 수행하도록 구성하였다.
Node* createNode(int value)
{
    Node* newNode;

    // 연결리스트는 저장되는 데이터 개수가 계속 달라질 수 있으므로
    // 필요한 순간에만 메모리를 할당하기 위해 malloc을 사용하였다.
    newNode = (Node*)malloc(sizeof(Node));

    // 메모리 할당에 실패하면 이후 노드 연결 자체가 불가능하므로
    // 프로그램을 계속 실행하는 것보다 종료하는 것이 안전하다고 판단하였다.
    if (newNode == NULL)
    {
        printf("메모리 할당 실패\n");
        exit(1);
    }

    // 전달받은 값을 저장하고,
    // 아직 연결된 노드가 없으므로 link는 NULL로 초기화하였다.
    newNode->data = value;
    newNode->link = NULL;

    return newNode;
}

// 현재 연결리스트의 상태를 출력하는 함수
// head부터 마지막 노드까지 순서대로 이동하며
// 저장되어 있는 데이터를 확인할 수 있도록 구현하였다.
void print_list()
{
    // 현재 탐색 중인 노드를 저장하기 위한 포인터이다.
    // head부터 하나씩 이동하면서 출력한다.
    Node* cur = head;

    printf("list = ");
    // 빈 리스트인 경우에는 더 이상 탐색할 필요가 없으므로
    // NULL만 출력하고 함수를 종료하였다.
    if (head == NULL)
    {
        printf("NULL\n");
        return;
    }

    while (cur != NULL) // 마지막 노드에 도착할 때까지 반복하면서 데이터를 출력한다.
    {
        printf("%d", cur->data);
        // 마지막 데이터 뒤에는 쉼표가 출력되지 않도록
        // 다음 노드가 존재하는 경우에만 ','를 출력하였다.
        if (cur->link != NULL) 
            printf(",");

        cur = cur->link;
    }

    printf("\n");
}

// 현재 연결리스트에 저장된 노드의 개수를 계산하는 함수
// 연결리스트는 크기를 따로 저장하지 않기 때문에
// 처음부터 끝까지 직접 탐색하여 개수를 계산하였다.
int get_length()
{
    Node* cur = head;
    int cnt = 0;

    while (cur != NULL)
    {
        cnt++;
        cur = cur->link;
    }

    return cnt;
}

// 새로운 데이터를 연결리스트의 가장 마지막에 삽입하는 함수
// 단순 연결리스트는 마지막 노드를 별도로 기억하지 않기 때문에
// head부터 마지막 노드까지 이동한 후 새 노드를 연결하였다.
void insert_back(int value)
{
    Node* newNode = createNode(value); // 먼저 삽입할 노드를 생성한다.

    // 리스트가 비어 있는 경우에는 새 노드가 첫 번째 노드가 되므로
    // head가 새 노드를 가리키도록 하였다.
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node* cur = head;

    // 다음 노드가 존재하는 동안 계속 이동하   
    // 마지막 노드에 도착하도록 구현하였다.
    while (cur->link != NULL)
    {
        cur = cur->link;
    }

    cur->link = newNode;
}

// 새로운 노드를 리스트의 가장 앞에 삽입하는 함수
// 새 노드가 기존 첫 번째 노드를 가리키게 만든 뒤
// head를 새 노드로 변경하는 방식으로 구현하였다.
void insert_first(int value)
{
    Node* newNode = createNode(value); // 먼저 삽입할 노드를 생성한다.

    newNode->link = head; // 기존 첫 번째 노드를 새 노드 뒤에 연결한다.
    
    // head를 새 노드로 변경하여
    // 새 노드가 리스트의 시작이 되도록 하였다.
    head = newNode;
}

// 입력한 데이터를 가진 노드를 탐색하는 함수
// 연결리스트는 임의 접근이 불가능하기 때문에
// head부터 순차적으로 비교하면서 원하는 데이터를 찾는다.
// 찾은 경우에는 해당 노드의 주소를 반환하고,
// 끝까지 찾지 못하면 NULL을 반환하도록 구현하였다.
Node* search_data(int value)
{
    Node* cur = head; 

    while (cur != NULL) 
    {
        if (cur->data == value) // 현재 노드의 데이터와 입력받은 값을 비교한다.
        {
            // 원하는 데이터를 찾았으므로
            // 해당 노드의 주소를 반환한다.
            return cur;
        }
        // 원하는 데이터를 아직 찾지 못했으므로
        // 다음 노드로 이동하여 계속 탐색한다.
        cur = cur->link;
    }

    return NULL;
}

// 입력한 index 위치의 노드를 찾는 함수
// 배열과 달리 연결리스트는 index로 바로 접근할 수 없기 때문에
// 첫 번째 노드부터 하나씩 이동하며 현재 위치를 계산하였다.
Node* search_index(int index)
{
    Node* cur = head;
    int cnt = 0;

    while (cur != NULL) 
    {
        if (cnt == index) // 현재 탐색 중인 위치가 원하는 index인지 확인한다.
            return cur;
        // 아직 원하는 위치가 아니므로
        // index를 증가시키면서 다음 노드로 이동한다.
        cnt++;
        cur = cur->link;
    }

    return NULL;
}

// 특정 데이터를 기준으로 그 앞에 새로운 노드를 삽입하는 함수
// 먼저 대상 데이터를 찾고,
// 이전 노드와 새 노드를 다시 연결하여
// 리스트의 순서를 유지하도록 구현하였다.
void insert_data(int target, int value)
{
    Node* newNode = createNode(value); // 삽입할 노드를 먼저 생성한다.

    // 빈 리스트에서는 삽입 기준이 존재하지 않으므로
    // 오류 메시지를 출력하고 생성한 노드를 해제하였다.
    if (head == NULL)
    {
        printf("리스트가 비어있습니다.\n");
        free(newNode);
        return;
    }

    // 첫 번째 노드 앞에 삽입하는 경우는
    // 일반적인 연결 방식과 다르므로 따로 처리하였다.
    if (head->data == target)
    {
        newNode->link = head;
        head = newNode;
        return;
    }

    // 탐색 과정에서 현재 노드와 이전 노드를 함께 기억하여
    // 원하는 위치를 찾으면 바로 연결할 수 있도록 구현하였다.
    Node* cur = head;
    Node* pre = NULL;

    while (cur != NULL)
    {
        if (cur->data == target)
            break;

        pre = cur;
        cur = cur->link;
    }
    // 대상 데이터를 찾지 못한 경우에는
    // 생성했던 노드의 메모리를 해제하여 메모리 누수를 방지하였다.
    if (cur == NULL)
    {
        printf("%d을(를) 찾을 수 없습니다.\n", target);
        free(newNode);
        return;
    }
    // 이전 노드와 새 노드를 연결한 뒤,
    // 새 노드가 기존 대상 노드를 가리키도록 하여 삽입을 완료하였다.
    pre->link = newNode;
    newNode->link = cur;
}

// 사용자가 입력한 index 위치 바로 앞에 새로운 노드를 삽입하는 함수
// 연결리스트는 배열처럼 원하는 위치로 바로 이동할 수 없기 때문에
// 첫 번째 노드부터 순서대로 이동하면서 원하는 위치를 찾도록 구현하였다.
void insert_index(int index, int value)
{
    // 먼저 삽입할 노드를 생성하여
    // 위치를 찾은 후 바로 연결할 수 있도록 준비하였다.
    Node* newNode = createNode(value);

    // index가 0이라는 것은 리스트의 가장 앞에 삽입하는 경우이다.
    // 이 경우에는 일반적인 연결 과정과 다르기 때문에
    // 별도의 예외 처리로 구현하였다.
    if (index == 0)
    {
        newNode->link = head;
        head = newNode;
        return;
    }

    // 현재 노드와 이전 노드를 모두 기억하면서
    // 원하는 index 위치까지 순차적으로 이동한다.
    Node* cur = head;
    Node* pre = NULL;
    int cnt = 0;

    // 아직 원하는 위치에 도착하지 않았으므로
    // 이전 노드를 갱신하고 다음 노드로 이동한다.
    while (cur != NULL)
    {
        if (cnt == index)
            break;

        pre = cur;
        cur = cur->link;
        cnt++;
    }

    // 사용자가 입력한 index가 현재 리스트의 길이를 초과한 경우이다.
    // 존재하지 않는 위치에는 삽입할 수 없으므로
    // 생성했던 노드의 메모리를 해제한 후 함수를 종료하였다.
    if (cnt != index)
    {
        printf("잘못된 index입니다.\n");
        free(newNode);
        return;
    }
    
    // 이전 노드가 새 노드를 가리키도록 연결하고,
    // 새 노드는 원래 해당 위치에 있던 노드를 가리키도록 하여
    // 리스트의 순서를 그대로 유지하였다.
    pre->link = newNode;
    newNode->link = cur;
}


// 입력한 데이터를 가진 노드의 위치(index)를 반환하는 함수
// 연결리스트는 index 정보를 저장하지 않기 때문에
// 탐색하면서 현재 위치를 직접 계산하도록 구현하였다.
int get_index_by_data(int value)
{
    
    Node* cur = head;
    int index = 0;

    while (cur != NULL)
    {
        if (cur->data == value){// 현재 노드의 데이터가 찾는 값인지 확인한다.
            // 원하는 데이터를 찾았으므로
            // 지금까지 계산한 index를 반환한다.
            return index;
        }
        // 아직 원하는 데이터가 아니므로
        // 다음 노드로 이동하면서 index도 함께 증가시킨다.
        cur = cur->link;
        index++;
    }
    // 끝까지 탐색했지만 원하는 데이터를 찾지 못했으므로
    // 실패를 의미하는 -1을 반환한다.
    return -1;
}

// 사용자가 입력한 index에 저장된 데이터를 반환하는 함수
// 배열과 달리 연결리스트는 임의 접근이 불가능하므로
// 첫 번째 노드부터 순차적으로 이동하며 위치를 계산하였다.
int get_data_by_index(int index)
{
    Node* cur = head;
    int cnt = 0;

    while (cur != NULL)
    {
        if (cnt == index){ // 현재 탐색 중인 위치가 사용자가 원하는 index인지 확인한다.
            // 원하는 위치에 도착했으므로
            // 해당 노드가 저장하고 있는 데이터를 반환한다.
            return cur->data;
        }
        // 아직 원하는 위치가 아니므로
        // 다음 노드로 이동하면서 현재 위치를 증가시킨다.
        cnt++;
        cur = cur->link;
    }
    // 존재하지 않는 index이므로
    // 오류를 의미하는 -1을 반환하였다.
    return -1;
}

// 리스트의 가장 앞에 있는 노드를 삭제하는 함수
// head가 다음 노드를 가리키도록 변경한 후
// 기존 첫 번째 노드의 메모리를 해제하는 방식으로 구현하였다.
void delete_first()
{
    // 삭제할 노드가 없는 경우에는
    // 더 이상 수행할 작업이 없으므로 함수만 종료한다.
    if (head == NULL)
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    // 삭제할 첫 번째 노드의 주소를 잠시 저장한다.
    // head를 먼저 변경하면 기존 노드의 주소를 잃어버리기 때문이다.
    Node* temp = head;

    // 두 번째 노드가 새로운 첫 번째 노드가 되도록 head를 이동시킨다.
    head = head->link;

    // 더 이상 사용하지 않는 노드의 메모리를 해제하여
    // 메모리 누수가 발생하지 않도록 처리하였다.
    free(temp);
}


// 리스트의 마지막 노드를 삭제하는 함수
// 마지막 노드와 그 이전 노드를 모두 알아야 연결을 끊을 수 있기 때문에
// 두 개의 포인터를 사용하여 탐색하였다.
void delete_back()
{
    if (head == NULL) // 빈 리스트에서는 삭제할 노드가 존재하지 않는다.
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    // 노드가 하나뿐인 경우에는
    // 삭제 후 리스트가 비어 있으므로 head도 NULL로 변경하였다.
    if (head->link == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    // 마지막 노드와 그 이전 노드를 함께 찾기 위해
    // 두 개의 포인터를 사용하여 이동한다.
    Node* cur = head;
    Node* pre = NULL;

    while (cur->link != NULL) // 마지막 노드가 나올 때까지 반복하여 이동한다.
    {
        // 마지막 노드를 제거했으므로
        // 이전 노드가 리스트의 마지막 노드가 된다.
        pre = cur;
        cur = cur->link;
    }

    pre->link = NULL;
    // 삭제한 노드의 메모리를 반환한다.
    free(cur);
}


// 사용자가 입력한 데이터를 가진 노드를 삭제하는 함수
// 삭제 대상과 이전 노드를 함께 찾은 후
// 연결 관계를 다시 설정하여 노드를 제거하도록 구현하였다.
void delete_data(int value)
{
    // 빈 리스트에서는 삭제할 대상이 존재하지 않는다.
    if (head == NULL)
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    // 삭제 대상과 이전 노드를 동시에 기억하면서 탐색한다.
    Node* cur = head;
    Node* pre = NULL;

    while (cur != NULL)
    {
        if (cur->data == value) // 원하는 데이터를 찾으면 반복문을 종료한다.
            break;

        pre = cur;
        cur = cur->link;
    }

    if (cur == NULL) // 원하는 데이터를 찾지 못한 경우이다.
    {
        printf("%d을(를) 찾을 수 없습니다.\n", value);
        return;
    }

    // 삭제 대상이 첫 번째 노드라면 이전 노드가 존재하지 않기 때문에 head만 다음 노드로 변경하면 된다.
    if (pre == NULL)
    {
        head = head->link;
    }
    else
    {
        pre->link = cur->link;
    }
    // 연결이 모두 끝났으므로
    // 삭제된 노드의 메모리를 해제하였다.
    free(cur);
}

// 사용자가 입력한 index 위치의 노드를 삭제하는 함수
// 연결리스트는 원하는 위치를 바로 찾을 수 없기 때문에
// 순차적으로 이동하면서 삭제 대상을 찾도록 구현하였다.
void delete_index(int index)
{
    if (head == NULL) // 빈 리스트에서는 삭제 작업을 수행할 수 없다.
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    // 첫 번째 노드를 삭제하는 경우에는
    // 이미 구현한 delete_first() 함수를 재사용하였다.
    // 같은 기능을 중복 작성하지 않기 위해 이렇게 구현하였다.
    if (index == 0)
    {
        delete_first();
        return;
    }
    
    // 삭제 대상과 이전 노드를 함께 기억하면서
    // 원하는 위치까지 이동한다.
    Node* cur = head;
    Node* pre = NULL;
    int cnt = 0;

    while (cur != NULL)
    {
        if (cnt == index)
            break;

        pre = cur;
        cur = cur->link;
        cnt++;
    }

    if (cur == NULL) // 사용자가 입력한 index가 존재하지 않는 경우이다.
    {
        printf("잘못된 index입니다.\n");
        return;
    }
    
    // 이전 노드가 삭제 대상의 다음 노드를 가리키도록 변경하여
    // 리스트가 끊어지지 않도록 연결하였다.
    pre->link = cur->link;

    free(cur);
}

// 연결리스트의 순서를 반대로 뒤집는 함수
// 새로운 리스트를 만들지 않고
// 기존 노드들의 연결 방향만 변경하는 방식으로 구현하였다.
// 메모리를 추가로 사용하지 않는 것이 목적이다.
void reverse()
{
    // 이전 노드, 현재 노드, 다음 노드를 각각 저장하기 위한 포인터이다.
    // 연결 방향을 변경하는 과정에서 기존 연결이 끊어지지 않도록
    // 세 개의 포인터를 함께 사용하였다.
    Node* pre = NULL;
    Node* cur = head;
    Node* next = NULL;

    while (cur != NULL)
    {
        // 다음 노드의 주소를 먼저 저장한다.
        // 현재 노드의 link를 변경하면 원래 다음 노드를 잃어버릴 수 있기 때문이다.
        next = cur->link;
        cur->link = pre; // 현재 노드의 연결 방향을 반대로 변경한다.
        // 한 단계 뒤집기가 끝났으므로
        // 이전 노드와 현재 노드를 다음 위치로 이동시킨다.
        pre = cur;
        cur = next;
    }
    // 모든 연결 방향이 변경되면
    // 마지막으로 처리한 노드가 새로운 첫 번째 노드가 되므로
    // head를 pre로 변경하여 뒤집기를 완료하였다.
    head = pre;
}


// -------------------------------
// 메인 함수
// -------------------------------
int main()
{
    char cmd[30];
    char type[30];

    int value;
    int target;
    int index;

    while (1)
    {
        printf("\n=========================================\n");
        printf("        단순 연결리스트 프로그램\n");
        printf("=========================================\n");
        printf("사용 가능한 명령어\n\n");

        printf("insert_back [data]\n");
        printf("   예) insert_back 5\n\n");

        printf("insert_first [data]\n");
        printf("   예) insert_first 5\n\n");

        printf("insert data [기존 data] [삽입 data]\n");
        printf("   예) insert data 3 10\n\n");

        printf("insert index [index] [삽입 data]\n");
        printf("   예) insert index 2 10\n\n");

        printf("delete data [data]\n");
        printf("   예) delete data 10\n\n");

        printf("delete index [index]\n");
        printf("   예) delete index 3\n\n");

        printf("delete_first\n");
        printf("delete_back\n\n");

        printf("get_entry data [data]\n");
        printf("   예) get_entry data 5\n\n");

        printf("get_entry index [index]\n");
        printf("   예) get_entry index 2\n\n");

        printf("get_length\n");
        printf("print_list\n");
        printf("reverse\n");
        printf("종료는 exit\n");

        printf("\n현재 ");
        print_list();
        printf("명령어를 입력하세요.\n ");
        printf(">> ");

        scanf("%s", cmd);

        // 사용자가 exit를 입력한 경우에는
        // 반복문을 종료하고 프로그램을 마무리하도록 구현하였다.
        if (strcmp(cmd, "exit") == 0)
        {
            break;
        }

        // 현재 연결리스트의 모든 데이터를 출력한다.
        else if (strcmp(cmd, "print_list") == 0)
        {
            print_list();
        }

        // 현재 저장되어 있는 노드의 개수를 계산하여 출력한다.
        // 연결리스트는 길이를 따로 저장하지 않기 때문에
        // 함수 내부에서 직접 계산한 결과를 출력한다.
        else if (strcmp(cmd, "get_length") == 0)
        {
            printf("length = %d\n", get_length());
        }

        // 연결리스트의 연결 방향을 모두 반대로 변경한다.
        // 작업이 끝난 후에는 변경된 결과를 바로 확인할 수 있도록
        // 리스트를 다시 출력하였다.
        else if (strcmp(cmd, "reverse") == 0)
        {
            reverse();

            print_list();
        }

        // 사용자가 입력한 데이터를
        // 연결리스트의 가장 마지막 위치에 추가한다.
        else if (strcmp(cmd, "insert_back") == 0)
        {
            scanf("%d", &value); // 삽입할 데이터를 입력받는다.

            insert_back(value);
            
            // 삽입이 완료된 후 결과를 바로 확인할 수 있도록 출력한다.
            print_list();
        }

        // 입력한 데이터를
        // 리스트의 가장 앞에 삽입하도록 호출하였다.
        else if (strcmp(cmd, "insert_first") == 0)
        {
            scanf("%d", &value);

            insert_first(value);

            print_list();
        }
        // insert 명령은 data 기준 삽입과
        // index 기준 삽입으로 나뉘기 때문에
        // 먼저 어떤 방식인지 확인하도록 구현하였다.
        else if (strcmp(cmd, "insert") == 0)
        {
            scanf("%s", type);

            // 사용자가 원하는 기준 데이터와
            // 새로 삽입할 데이터를 함께 입력받는다.
            if (strcmp(type, "data") == 0)
            {
                scanf("%d %d", &target, &value);

                insert_data(target, value);

                print_list();
            }

            // 삽입할 위치와
            // 새로 저장할 데이터를 입력받는다.
            else if (strcmp(type, "index") == 0)
            {
                scanf("%d %d", &index, &value);

                insert_index(index, value);

                print_list();
            }
            // data와 index 외의 명령이 입력된 경우에는
            // 잘못된 입력으로 판단하여 오류 메시지를 출력하였다.
            else
            {
                printf("잘못된 명령어입니다.\n");
            }
        }

        // delete 명령 역시
        // data 삭제와 index 삭제 두 가지 방식이 존재하므로
        // 먼저 삭제 기준을 입력받도록 구현하였다.
        else if (strcmp(cmd, "delete") == 0)
        {
            scanf("%s", type);
            
            // 삭제할 데이터를 입력받는다.
            if (strcmp(type, "data") == 0)
            {
                scanf("%d", &value);

                delete_data(value);

                print_list();
            }

            // 삭제할 위치(index)를 입력받는다.
            else if (strcmp(type, "index") == 0)
            {
                scanf("%d", &index);

                delete_index(index);

                print_list();
            }

            else
            {
                printf("잘못된 명령어입니다.\n");
            }
        }

        // 리스트의 첫 번째 노드를 삭제한다.
        // 삭제 후 결과를 바로 출력한다.
        else if (strcmp(cmd, "delete_first") == 0)
        {
            delete_first();

            print_list();
        }

        // 리스트의 마지막 노드를 삭제한다.
        // 수행 결과를 바로 확인할 수 있도록 출력하였다.
        else if (strcmp(cmd, "delete_back") == 0)
        {
            delete_back();

            print_list();
        }

        // get_entry 명령은
        // data와 index 두 가지 조회 방식이 존재하므로
        // 먼저 어떤 조회인지 확인하도록 구현하였다.
        else if (strcmp(cmd, "get_entry") == 0)
        {
            scanf("%s", type);

            // 찾고 싶은 데이터를 입력받는다.
            if (strcmp(type, "data") == 0)
            {
                scanf("%d", &value);

                int result = get_index_by_data(value); // 입력한 데이터를 가진 노드의 index를 검색한다.

                if (result == -1) // 반환값이 -1이면 해당 데이터를 찾지 못한 경우이다.
                    printf("찾을 수 없습니다.\n");
                else
                    printf("index = %d\n", result);
            }
            
            // 조회할 index를 입력받는다.
            else if (strcmp(type, "index") == 0)
            {
                scanf("%d", &index);

                int result = get_data_by_index(index); // 해당 위치에 저장된 데이터를 가져온다.
                
                // 존재하지 않는 위치라면 오류 메시지를 출력한다.
                if (result == -1)
                    printf("찾을 수 없습니다.\n");
                else
                    printf("data = %d\n", result);
            }

            else
            {
                printf("잘못된 명령어입니다.\n");
            }
        }

        // 프로그램에서 지원하지 않는 명령어가 입력된 경우이다.
        // 사용자가 올바른 명령을 다시 입력할 수 있도록
        // 오류 메시지만 출력하고 반복문을 계속 수행한다.
        else
        {
            printf("존재하지 않는 명령어입니다.\n");
        }
    }

    // 프로그램이 종료되기 전에
    // 지금까지 생성한 모든 노드의 메모리를 해제한다.
    // 동적 메모리를 사용했기 때문에
    // free()를 호출하지 않으면 메모리 누수가 발생할 수 있다.
    Node* cur = head;
    Node* temp;

    while (cur != NULL)
    {
        temp = cur;
        cur = cur->link;
        free(temp);
    }

    printf("프로그램을 종료합니다.\n");

    return 0;
}