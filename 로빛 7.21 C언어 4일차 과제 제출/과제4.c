#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct
{
    int year;
    int month;
    int day;
} DATE;

typedef struct
{
    int hour;
    int min;
    int sec;
} TIME;

typedef struct
{
    DATE Date;
    TIME Time;
} TIMESTAMP;

// 입력받은 연도가 윤년인지 판별하는 함수이다.
int leapyear(int year)
{
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        return 1;

    return 0;
}

// 입력받은 날짜가 기준 시점부터 며칠이 지났는지를 계산하는 함수이다.
// 두 날짜의 차이를 쉽게 계산하기 위해
// 날짜를 모두 총 일수 형태로 변환하도록 구현하였다.
long long totaldays(DATE d)
{
    // 각 달의 기본 날짜 수를 저장한 배열이다.
    // 윤년인 경우에는 2월의 날짜를 29일로 변경하여 사용한다.
    int monthDay[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // 기준 시점부터 누적된 총 일수를 저장하는 변수이다.
    long long days = 0;

    // 현재 연도 이전까지의 모든 날짜를 더한다.
    // 윤년 여부에 따라 365일 또는 366일을 누적하였다.
    for (int y = 0; y < d.year; y++)
    {
        if (leapyear(y))
            days += 366;
        else
            days += 365;
    }

    // 현재 연도가 윤년이라면
    // 2월의 날짜를 29일로 변경하여 계산한다.
    if (leapyear(d.year))
        monthDay[1] = 29;

    // 현재 달 이전까지의 날짜를 모두 더한다.
    for (int i = 0; i < d.month - 1; i++)
    {
        days += monthDay[i];
    }

    // 현재 달에서 이미 지난 날짜를 더한다.
    // 첫째 날을 기준으로 계산하기 위해 day-1을 사용하였다.
    days += d.day - 1;

    return days;
}

int main()
{
    // 두 개의 날짜와 시간을 저장하기 위한 구조체 배열이다.
    TIMESTAMP stamp[2];

    printf("입력 : ");

    // 첫 번째 날짜와 시간을 입력받는다.
    scanf("%d %d %d %d %d %d",
          &stamp[0].Date.year,
          &stamp[0].Date.month,
          &stamp[0].Date.day,
          &stamp[0].Time.hour,
          &stamp[0].Time.min,
          &stamp[0].Time.sec);

    printf("       ");

    // 두 번째 날짜와 시간을 입력받는다.
    scanf("%d %d %d %d %d %d",
          &stamp[1].Date.year,
          &stamp[1].Date.month,
          &stamp[1].Date.day,
          &stamp[1].Time.hour,
          &stamp[1].Time.min,
          &stamp[1].Time.sec);

    // 날짜를 총 초(second) 단위로 변환한다.
    // 날짜는 총 일수로 계산한 뒤 초 단위로 바꾸고,
    // 시, 분, 초를 모두 더하여 하나의 기준 시간으로 만든다.
    long long totalSec1 =
        totaldays(stamp[0].Date) * 24LL * 60 * 60
        + stamp[0].Time.hour * 3600LL
        + stamp[0].Time.min * 60LL
        + stamp[0].Time.sec;

    // 두 번째 입력도 같은 방식으로 총 초 단위로 변환한다.
    long long totalSec2 =
        totaldays(stamp[1].Date) * 24LL * 60 * 60
        + stamp[1].Time.hour * 3600LL
        + stamp[1].Time.min * 60LL
        + stamp[1].Time.sec;

    // 두 시간의 차이를 초 단위로 계산한다.
    long long diff = totalSec2 - totalSec1;

    // 입력 순서와 관계없이 항상 양수의 시간 차이를 출력하기 위해
    // 음수인 경우 절댓값으로 변환하였다.
    if (diff < 0)
    {
        diff = -diff;
    }

    // 총 초를 시 단위로 변환한다.
    int hour = diff / 3600;

    // 시를 제외한 나머지 초를 계산한다.
    diff %= 3600;

    // 남은 초를 분과 초로 나누어 계산한다.
    int min = diff / 60;
    int sec = diff % 60;

    // 계산된 시간 차이를 출력한다.
    printf("%d시 %d분 %d초\n", hour, min, sec);

    // 프로그램을 정상적으로 종료한다.
    return 0;
}