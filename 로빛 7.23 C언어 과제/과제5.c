#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생의 정보를 하나로 관리하기 위한 구조체이다.
// 학생 번호, 이름, 주소, 성적을 하나의 자료형으로 묶어
// 데이터를 관리하기 쉽도록 구현하였다.
typedef struct
{
    int id;
    char name[30];
    char country[30];
    char province[30];
    char city[30];
    char district[30];
    int score;
} Student;

// 최대 학생 수를 100명으로 제한하였다.
// 배열의 크기를 일정하게 유지하기 위해 사용하였다.
#define MAX 100

// 메뉴 출력 함수
void menu();

// 학생 관리 함수
void addStudent(Student student[], int* count);
void deleteStudent(Student student[], int* count);
void printStudent(Student student[], int count);
void findStudent(Student student[], int count);
void sortStudent(Student student[], int count);

// 파일 저장 및 불러오기 함수
void saveStudent(Student student[], int count);
void loadStudent(Student student[], int* count);

// 정수만 입력받기 위한 함수이다.
// 문자가 입력되더라도 프로그램이 종료되지 않도록
// 올바른 숫자가 입력될 때까지 반복하도록 구현하였다.
int inputInt()
{
    int num;

    while (scanf("%d", &num) != 1)
    {
        printf("숫자를 입력하세요 : ");

        // 입력 버퍼에 남아 있는 잘못된 문자를 제거한다.
        while (getchar() != '\n');
    }

    return num;
}

// 메인 메뉴를 출력하는 함수이다.
// 반복적으로 같은 메뉴를 출력해야 하므로
// 별도의 함수로 분리하여 코드의 가독성을 높였다.
void menu()
{
    printf("출석부 프로그램\n\n");
    printf("1. 학생 추가\n");
    printf("2. 학생 삭제\n");
    printf("3. 학생 찾기\n");
    printf("4. 학생 정렬\n");
    printf("5. 학생 목록 출력\n");
    printf("6. 저장\n");
    printf("7. 불러오기\n");
    printf("0. 종료\n\n");
    printf("메뉴 선택 : ");
}


int main()
{
    // 학생 정보를 저장할 배열이다.
    Student student[MAX];

    // 현재 저장되어 있는 학생 수를 저장한다.
    int count = 0;

    // 사용자가 선택한 메뉴 번호를 저장한다.
    int menuNum;

    // 종료를 선택하기 전까지 프로그램을 계속 실행한다.
    while (1)
    {
        // 메뉴를 출력한다.
        menu();

        // 메뉴 번호를 입력받는다.
        menuNum = inputInt();

        // 선택한 메뉴에 따라 해당 기능을 수행한다.
        switch (menuNum)
        {
        case 1:
            addStudent(student, &count);
            break;

        case 2:
            deleteStudent(student, &count);
            break;

        case 3:
            findStudent(student, count);
            break;

        case 4:
            sortStudent(student, count);
            break;

        case 5:
            printStudent(student, count);
            break;

        case 6:
            saveStudent(student, count);
            break;

        case 7:
            loadStudent(student, &count);
            break;

        case 0:
            printf("프로그램 종료\n");
            return 0;

        // 정의되지 않은 메뉴를 입력한 경우이다.
        default:
            printf("잘못 입력했습니다.\n");
        }
    }

    return 0;
}

// 새로운 학생 정보를 입력받아 배열에 저장하는 함수이다.
// 학생 수가 최대 인원을 초과하지 않는지 확인한 후
// 번호, 이름, 주소, 성적을 입력받도록 구현하였다.
void addStudent(Student student[], int* count)
{
    // 배열이 가득 찬 경우에는 더 이상 학생을 추가할 수 없다.
    if (*count >= MAX)
    {
        printf("더 이상 학생을 추가할 수 없습니다.\n");
        return;
    }

    // 학생 번호를 입력받는다.
    printf("\n번호 : ");
    student[*count].id = inputInt();

    // 학생 이름을 입력받는다.
    printf("이름 : ");
    scanf("%s", student[*count].name);

    // 학생이 거주하는 나라를 입력받는다.
    printf("나라 : ");
    scanf("%s", student[*count].country);

    // 학생이 거주하는 도를 입력받는다.
    printf("도 : ");
    scanf("%s", student[*count].province);

    // 학생이 거주하는 시를 입력받는다.
    printf("도시 : ");
    scanf("%s", student[*count].city);

    // 학생이 거주하는 구를 입력받는다.
    printf("구 : ");
    scanf("%s", student[*count].district);

    // 성적은 0~100 사이만 입력할 수 있도록 검사한다.
    // 잘못된 값이 입력되면 다시 입력받는다.
    while (1)
    {
        printf("성적 : ");
        student[*count].score = inputInt();

        if (student[*count].score >= 0 &&
            student[*count].score <= 100)
            break;

        printf("성적은 0~100만 입력 가능합니다.\n");
    }

    // 학생 한 명이 추가되었으므로 저장된 학생 수를 증가시킨다.
    (*count)++;

    printf("\n학생이 추가되었습니다.\n");
}

// 학생 번호를 이용하여 학생 정보를 삭제하는 함수이다.
// 삭제할 학생을 찾은 후 뒤에 있는 학생 정보를 한 칸씩 앞으로
// 이동시켜 빈 공간이 생기지 않도록 구현하였다.
void deleteStudent(Student student[], int* count)
{
    // 저장된 학생이 없는 경우 삭제할 데이터가 없다.
    if (*count == 0)
    {
        printf("삭제할 학생이 없습니다.\n");
        return;
    }

    int id;
    int i;

    // 삭제할 학생의 위치를 저장하는 변수이다.
    // 처음에는 찾지 못한 상태를 의미하도록 -1로 초기화하였다.
    int index = -1;

    printf("삭제할 학생 번호 : ");
    id = inputInt();

    // 입력한 번호와 일치하는 학생을 찾는다.
    for (i = 0; i < *count; i++)
    {
        if (student[i].id == id)
        {
            index = i;
            break;
        }
    }

    // 해당 번호의 학생이 존재하지 않는 경우이다.
    if (index == -1)
    {
        printf("해당 학생이 없습니다.\n");
        return;
    }

    // 삭제된 위치 이후의 학생들을 한 칸씩 앞으로 이동시켜
    // 배열이 빈 공간 없이 유지되도록 한다.
    for (i = index; i < *count - 1; i++)
    {
        student[i] = student[i + 1];
    }

    // 학생이 한 명 삭제되었으므로 저장 개수를 감소시킨다.
    (*count)--;

    printf("삭제되었습니다.\n");
}

// 현재 저장되어 있는 모든 학생 정보를 출력하는 함수이다.
// 학생 번호, 이름, 주소, 성적을 순서대로 출력하도록 구현하였다.
void printStudent(Student student[], int count)
{
    // 출력할 학생이 없는 경우이다.
    if (count == 0)
    {
        printf("학생이 없습니다.\n");
        return;
    }

    int i;

    printf("\n=============================================\n");

    // 저장된 학생 정보를 차례대로 출력한다.
    for (i = 0; i < count; i++)
    {
        printf("학생 %d\n", i + 1);
        printf("번호 : %d\n", student[i].id);
        printf("이름 : %s\n", student[i].name);

        // 나라, 도, 시, 구를 하나의 주소 형태로 출력하였다.
        printf("주소 : %s %s %s %s\n",
            student[i].country,
            student[i].province,
            student[i].city,
            student[i].district);

        printf("성적 : %d\n", student[i].score);
        printf("==============================================\n");
    }
}

// 다양한 조건으로 학생을 검색하는 함수이다.
// 번호, 성적, 나라, 도시, 구를 기준으로
// 원하는 학생을 찾을 수 있도록 구현하였다.
void findStudent(Student student[], int count)
{
    // 학생이 없는 경우에는 검색할 수 없다.
    if (count == 0)
    {
        printf("학생이 없습니다.\n");
        return;
    }

    int menu;
    int id;
    int score;

    // 문자열 검색에 사용할 임시 배열이다.
    char str[30];

    int i;

    // 검색 성공 여부를 저장하는 변수이다.
    // 검색 결과가 하나도 없으면 마지막에 안내 문구를 출력한다.
    int found = 0;

    printf("1. 번호로 찾기\n");
    printf("2. 성적으로 찾기\n");
    printf("3. 나라로 찾기\n");
    printf("4. 도로 찾기\n");
    printf("5. 시로 찾기\n");
    printf("6. 구로 찾기\n");
    printf("선택 : ");

    menu = inputInt();

    switch (menu)
    {
    // 학생 번호로 검색
    case 1:

        printf("번호 입력 : ");
        id = inputInt();

        // 입력한 번호와 같은 학생을 찾는다.
        for (i = 0; i < count; i++)
        {
            if (student[i].id == id)
            {
                printf("\n번호 : %d\n", student[i].id);
                printf("이름 : %s\n", student[i].name);
                printf("주소 : %s %s %s %s\n",
                    student[i].country,
                    student[i].province,
                    student[i].city,
                    student[i].district);
                printf("성적 : %d\n", student[i].score);

                found = 1;
            }
        }

        break;

    // 성적으로 검색
    case 2:

        printf("성적 입력 : ");
        score = inputInt();

        // 입력한 성적과 같은 학생을 모두 출력한다.
        for (i = 0; i < count; i++)
        {
            if (student[i].score == score)
            {
                printf("\n번호 : %d\n", student[i].id);
                printf("이름 : %s\n", student[i].name);
                printf("주소 : %s %s %s %s\n",
                    student[i].country,
                    student[i].province,
                    student[i].city,
                    student[i].district);
                printf("성적 : %d\n", student[i].score);

                found = 1;
            }
        }

        break;

    // 나라 이름으로 검색
    // strcmp()를 이용하여 문자열이 같은지 비교하였다.
    case 3:

        printf("나라 입력 : ");
        scanf("%s", str);

        for (i = 0; i < count; i++)
        {
            if (strcmp(student[i].country, str) == 0)
            {
                printf("\n번호 : %d\n", student[i].id);
                printf("이름 : %s\n", student[i].name);
                printf("주소 : %s %s %s %s\n",
                    student[i].country,
                    student[i].province,
                    student[i].city,
                    student[i].district);
                printf("성적 : %d\n", student[i].score);

                found = 1;
            }
        }

        break;
    // 도 이름으로 검색
    case 4:

        printf("도 입력 : ");
        scanf("%s", str);
    
        for (i = 0; i < count; i++)
        {
            if (strcmp(student[i].province, str) == 0)
            {
                printf("\n번호 : %d\n", student[i].id);
                printf("이름 : %s\n", student[i].name);
                printf("주소 : %s %s %s %s\n",
                    student[i].country,
                    student[i].province,
                    student[i].city,
                    student[i].district);
                printf("성적 : %d\n", student[i].score);
    
                found = 1;
            }
        }
        break;
    // 시 이름으로 검색
    case 5:

        printf("도시 입력 : ");
        scanf("%s", str);

        for (i = 0; i < count; i++)
        {
            if (strcmp(student[i].city, str) == 0)
            {
                printf("\n번호 : %d\n", student[i].id);
                printf("이름 : %s\n", student[i].name);
                printf("주소 : %s %s %s %s\n",
                    student[i].country,
                    student[i].province,
                    student[i].city,
                    student[i].district);
                printf("성적 : %d\n", student[i].score);

                found = 1;
            }
        }

        break;

    // 구 이름으로 검색
    case 6:

        printf("구 입력 : ");
        scanf("%s", str);

        for (i = 0; i < count; i++)
        {
            if (strcmp(student[i].district, str) == 0)
            {
                printf("\n번호 : %d\n", student[i].id);
                printf("이름 : %s\n", student[i].name);
                printf("주소 : %s %s %s %s\n",
                    student[i].country,
                    student[i].province,
                    student[i].city,
                    student[i].district);
                printf("성적 : %d\n", student[i].score);

                found = 1;
            }
        }

        break;

    // 잘못된 메뉴를 입력한 경우이다.
    default:
        printf("잘못된 입력입니다.\n");
        return;
    }

    // 검색 결과가 하나도 없는 경우 안내 문구를 출력한다.
    if (!found)
    {
        printf("검색 결과가 없습니다.\n");
    }
}

// 학생 정보를 원하는 기준으로 정렬하는 함수이다.
// 번호, 이름, 나라, 도시, 구, 성적을 기준으로
// 오름차순 정렬하도록 구현하였다.
// 정렬 알고리즘은 구현이 간단한 버블 정렬(Bubble Sort)을 사용하였다.
void sortStudent(Student student[], int count)
{
    // 학생 정보가 하나도 없으면 정렬할 수 없다.
    if (count == 0)
    {
        printf("학생이 없습니다.\n");
        return;
    }

    // 사용자가 선택한 정렬 기준을 저장하는 변수이다.
    int menu;

    // 반복문에서 사용할 변수이다.
    int i, j;

    // 두 학생의 정보를 서로 교환하기 위한 임시 변수이다.
    Student temp;

    // 정렬 기준을 선택할 메뉴를 출력한다.
    printf("1. 번호순\n");
    printf("2. 이름순\n");
    printf("3. 나라순\n");
    printf("4. 도순\n");
    printf("5. 시순\n");
    printf("6. 구순\n");
    printf("7. 성적순\n");
    printf("\n");
    printf("선택 : ");

    // 정렬 기준을 입력받는다.
    menu = inputInt();

    switch (menu)
    {
    // 학생 번호를 기준으로 오름차순 정렬한다.
    // 숫자이므로 대소 비교 연산자를 이용하였다.
    case 1:

        for (i = 0; i < count - 1; i++)
        {
            // 가장 큰 값이 뒤로 이동하도록 구현하였다.
            for (j = 0; j < count - 1 - i; j++)
            {
                // 앞의 번호가 더 크면 위치를 서로 교환한다.
                if (student[j].id > student[j + 1].id)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;

    // 이름을 가나다순으로 정렬한다.
    // 문자열 비교를 위해 strcmp() 함수를 사용하였다.
    case 2:

        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                // strcmp()의 결과가 0보다 크면
                // 앞 문자열이 뒤 문자열보다 뒤에 와야 한다.
                if (strcmp(student[j].name, student[j + 1].name) > 0)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;

    // 나라 이름을 기준으로 정렬한다.
    case 3:

        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (strcmp(student[j].country,
                           student[j + 1].country) > 0)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;
    // 도 이름을 기준으로 정렬한다.
    case 4:

        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (strcmp(student[j].province,
                    student[j+1].province) > 0)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;
    
    
    // 시 이름을 기준으로 정렬한다.
    case 5:

        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (strcmp(student[j].city,
                           student[j + 1].city) > 0)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;
    
    // 구 이름을 기준으로 정렬한다.
    case 6:

        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (strcmp(student[j].district,
                           student[j + 1].district) > 0)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;

    // 성적을 기준으로 오름차순 정렬한다.
    // 숫자 비교이므로 > 연산자를 사용하였다.
    case 7:

        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (student[j].score > student[j + 1].score)
                {
                    temp = student[j];
                    student[j] = student[j + 1];
                    student[j + 1] = temp;
                }
            }
        }

        break;

    // 존재하지 않는 메뉴를 입력한 경우이다.
    default:

        printf("잘못된 입력입니다.\n");
        return;
    }

    // 정렬이 완료되었음을 사용자에게 알린다.
    printf("정렬이 완료되었습니다.\n");

    // 정렬된 결과를 바로 확인할 수 있도록
    // 학생 목록 출력 함수를 호출하였다.
    printStudent(student, count);
}

// 현재 저장되어 있는 학생 정보를 파일에 저장하는 함수이다.
// 프로그램을 종료해도 데이터를 다시 사용할 수 있도록
// 텍스트 파일(attendance.txt)에 학생 정보를 기록하였다.
void saveStudent(Student student[], int count)
{
    // 파일을 다루기 위한 파일 포인터이다.
    FILE* fp;

    // 반복문에서 사용할 변수이다.
    int i;

    // 쓰기 모드("w")로 파일을 연다.
    // 기존 파일이 존재하면 내용을 덮어쓰고,
    // 없으면 새로운 파일을 생성한다.
    fp = fopen("attendance.txt", "w");

    // 파일을 정상적으로 열지 못한 경우이다.
    if (fp == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 현재 저장된 학생 정보를 한 줄씩 파일에 기록한다.
    // 학생 한 명의 정보를 공백으로 구분하여 저장하였다.
    for (i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %s %s %s %s %d\n",
            student[i].id,
            student[i].name,
            student[i].country,
            student[i].province,
            student[i].city,
            student[i].district,
            student[i].score);
    }

    // 파일 저장이 끝났으므로 반드시 닫아준다.
    fclose(fp);

    printf("저장이 완료되었습니다.\n");
}

// ==========================================================
// 파일에 저장되어 있는 학생 정보를 다시 읽어오는 함수이다.
// 프로그램을 다시 실행하더라도 이전에 저장한 데이터를
// 계속 사용할 수 있도록 구현하였다.
// ==========================================================
void loadStudent(Student student[], int* count)
{
    // 파일을 다루기 위한 파일 포인터이다.
    FILE* fp;

    // 읽기 모드("r")로 파일을 연다.
    fp = fopen("attendance.txt", "r");

    // 저장된 파일이 존재하지 않는 경우이다.
    if (fp == NULL)
    {
        printf("저장된 파일이 없습니다.\n");
        return;
    }

    // 기존에 저장되어 있던 학생 정보를 모두 지우고
    // 파일의 내용으로 다시 채우기 위해 학생 수를 0으로 초기화한다.
    *count = 0;

    // fscanf()가 6개의 데이터를 모두 정상적으로 읽을 때까지 반복한다.
    // 번호, 이름, 나라, 도시, 구, 성적을 차례대로 읽어 배열에 저장한다.
    while (fscanf(fp, "%d %s %s %s %s %s %d",
        &student[*count].id,
        student[*count].name,
        student[*count].country,
        student[*count].province,
        student[*count].city,
        student[*count].district,
        &student[*count].score) == 6)
    {
        // 학생 한 명을 모두 읽었으므로 저장 개수를 증가시킨다.
        (*count)++;

        // 배열의 최대 크기를 넘지 않도록 검사한다.
        if (*count >= MAX)
            break;
    }

    // 파일 사용이 끝났으므로 닫아준다.
    fclose(fp);

    printf("불러오기가 완료되었습니다.\n");
}