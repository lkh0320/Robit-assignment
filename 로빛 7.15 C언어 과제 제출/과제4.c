#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main() {
    char equation[100];
    float num1, num2, result;
    char op;

    // 수식 입력
    printf("input Arithmetic Operator\n");
    printf("ex)\t\t3.4 + 8.5\n");
    printf("\t\t2.9 - 5.4\n");
    printf("\t\t3.9 * 8.0\n");
    printf("\t\t3.9 ^ 8\n\n");
    printf("input : ");

    fgets(equation, sizeof(equation), stdin);

    // 입력 형식 검사
    if (sscanf(equation, "%f %c %f", &num1, &op, &num2) != 3) {
        printf("입력 형식이 올바르지 않습니다.\n");
        return 1;
    }

    // 연산 수행
    switch (op)
    {
    case '+':
        result = num1 + num2;
        break;

    case '-':
        result = num1 - num2;
        break;

    case '*':
        result = num1 * num2;
        break;

    case '/':
        // 0으로 나누기 예외 처리
        if (num2 == 0) {
            printf("0으로 나눌 수 없습니다.\n");
            return 1;
        }
        result = num1 / num2;
        break;

    case '^':
        result = pow(num1, num2);
        break;

    default:
        printf("잘못된 연산자입니다.\n");
        return 1;
    }

    // 결과 출력
    printf("%.2f %c %.2f = %.2f\n", num1, op, num2, result);

    return 0;
}