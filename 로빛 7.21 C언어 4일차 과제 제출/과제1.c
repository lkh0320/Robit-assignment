#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _Student {
    int grade;
    float point;
    char name[20];
} Student;

int main(void)
{
    Student s[5];

    // 학생 정보를 차례대로 입력받는다.
    for (int i = 0; i < 5; i++) {
        printf("학년 성적 이름 : ");
        scanf("%d %f %19s", &s[i].grade, &s[i].point, s[i].name);
    }

    // 선택 정렬 과정에서 데이터를 교환하기 위한 임시 변수이다.
    Student temp;

    // 선택 정렬을 이용하여 학생 정보를 정렬한다.
    // 앞에서부터 가장 작은 데이터를 찾아 현재 위치와 교환하는 방식으로 구현하였다.
    for (int i = 0; i < 4; i++) {

        // 현재 위치를 가장 작은 값이라고 가정하고 탐색을 시작한다.
        int min = i;

        // 현재 위치 이후의 학생들과 비교하여
        // 가장 우선순위가 높은 학생을 찾는다.
        for (int j = i + 1; j < 5; j++) {

            // 먼저 학년을 비교한다.
            // 학년이 더 낮은 학생을 우선하도록 하였다.
            if (s[j].grade < s[min].grade)
                min = j;

            // 학년이 같다면 성적을 비교한다.
            else if (s[j].grade == s[min].grade) {

                // 성적이 더 낮은 학생을 먼저 배치한다.
                if (s[j].point < s[min].point)
                    min = j;

                // 학년과 성적이 모두 같은 경우에는
                // 이름을 사전순으로 비교한다.
                else if (s[j].point == s[min].point) {

                    // 문자열의 각 문자를 하나씩 비교하기 위한 변수이다.
                    int k = 0;

                    // strcmp()를 사용하지 않고
                    // 문자열 비교 과정을 직접 구현하였다.
                    while (1) {

                        // 현재 문자가 더 앞서는 문자라면
                        // 새로운 최소값으로 선택한다.
                        if (s[j].name[k] < s[min].name[k]) {
                            min = j;
                            break;
                        }

                        // 현재 문자가 더 뒤의 문자라면
                        // 기존 최소값을 그대로 유지한다.
                        if (s[j].name[k] > s[min].name[k]) {
                            break;
                        }

                        // 두 문자열이 동시에 끝났다면
                        // 완전히 같은 이름이므로 비교를 종료한다.
                        if (s[j].name[k] == '\0' &&
                            s[min].name[k] == '\0') {
                            break;
                        }

                        // 다음 문자도 계속 비교한다.
                        k++;
                    }
                }
            }
        }

        // 가장 앞에 와야 하는 학생과 현재 위치의 학생을 교환한다.
        temp = s[i];
        s[i] = s[min];
        s[min] = temp;
    }

    // 정렬이 완료된 학생 정보를 순서대로 출력한다.
    printf("\n입력 결과\n");

    for (int i = 0; i < 5; i++) {
        printf("%d %.1f %s\n", s[i].grade, s[i].point, s[i].name);
    }

    // 프로그램을 정상적으로 종료한다.
    return 0;
}