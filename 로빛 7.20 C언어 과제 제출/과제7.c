#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int max_input_len = 1000;
    int max_tag_len = 50;

    int input_len = 0;
    int stack_size = 0;
    int i;

    // 입력 문자열을 저장할 메모리 할당
    char *input = (char *)calloc(max_input_len, sizeof(char));
    if (input == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    printf("입력 : ");

    // 문자열 입력
    if (scanf("%999s", input) != 1)
    {
        printf("입력 오류\n");
        free(input);
        return 1;
    }

    // 입력 문자열 길이 계산
    while (input[input_len] != '\0')
        input_len++;

    // 태그를 저장할 스택 생성
    int n = max_input_len * max_tag_len;
    char *stack = (char *)calloc(n, sizeof(char));

    if (stack == NULL)
    {
        printf("메모리 할당 실패\n");
        free(input);
        return 1;
    }

    printf("\n출력 :\n");

    // 문자열 끝까지 검사
    i = 0;
    while (i < input_len)
    {
        // 태그를 만난 경우
        if (input[i] == '<')
        {
            int start = i;

            // 태그 끝('>') 찾기
            while (i < input_len && input[i] != '>')
                i++;

            if (i >= input_len)
            {
                printf("[오류] '>'가 닫히지 않았습니다.\n");
                free(input);
                free(stack);
                return 1;
            }

            // 현재 태그 저장
            int tag_len = i - start + 1;
            char *current_tag = (char *)calloc(max_tag_len, sizeof(char));

            if (current_tag == NULL)
            {
                printf("메모리 할당 실패\n");
                free(input);
                free(stack);
                return 1;
            }

            for (int k = 0; k < tag_len && k < max_tag_len - 1; k++)
                current_tag[k] = input[start + k];

            i++;

            // -----------------------------
            // 닫는 태그 처리
            // -----------------------------
            if (current_tag[1] == '/')
            {
                if (stack_size == 0)
                {
                    printf("[오류] 태그 구조가 잘못되었습니다.\n");

                    free(current_tag);
                    free(input);
                    free(stack);
                    return 1;
                }

                int top_idx = (stack_size - 1) * max_tag_len;
                int is_match = 1;
                int tag_p = 1;

                // 태그 이름 비교
                while (stack[top_idx + tag_p] != '>' &&
                       current_tag[tag_p + 1] != '>')
                {
                    if (stack[top_idx + tag_p] != current_tag[tag_p + 1])
                    {
                        is_match = 0;
                        break;
                    }

                    tag_p++;
                }

                if (stack[top_idx + tag_p] != '>' ||
                    current_tag[tag_p + 1] != '>')
                {
                    is_match = 0;
                }

                if (!is_match)
                {
                    printf("[오류] 잘못된 태그 구조 : %s\n", current_tag);

                    free(current_tag);
                    free(input);
                    free(stack);
                    return 1;
                }

                // 스택에서 제거
                stack_size--;

                // 들여쓰기 출력
                for (int space = 0; space < stack_size; space++)
                    printf("    ");

                printf("%s\n", current_tag);
            }

            // -----------------------------
            // 여는 태그 처리
            // -----------------------------
            else
            {
                for (int space = 0; space < stack_size; space++)
                    printf("    ");

                printf("%s\n", current_tag);

                // 스택에 저장
                int push_idx = stack_size * max_tag_len;
                int k = 0;

                while (current_tag[k] != '\0')
                {
                    stack[push_idx + k] = current_tag[k];
                    k++;
                }

                stack_size++;
            }

            free(current_tag);
        }        
        // 일반 텍스트 처리
        else
        {
            int start = i;

            // 다음 태그가 나올 때까지 이동
            while (i < input_len &&
                   input[i] != '\0' &&
                   input[i] != '<')
            {
                i++;
            }

            int text_len = i - start;
            int is_empty = 1;

            // 공백만 있는지 확인
            for (int k = 0; k < text_len; k++)
            {
                char ch = input[start + k];

                if (ch != ' ' &&
                    ch != '\t' &&
                    ch != '\n' &&
                    ch != '\r')
                {
                    is_empty = 0;
                    break;
                }
            }

            // 공백이 아니라면 출력
            if (!is_empty)
            {
                for (int space = 0; space < stack_size; space++)
                    printf("    ");

                for (int k = 0; k < text_len; k++)
                    printf("%c", input[start + k]);

                printf("\n");
            }
        }
    }

    // 닫히지 않은 태그 확인
    if (stack_size > 0)
    {
        printf("[오류] 닫히지 않은 태그가 존재합니다.\n");
    }

    // 동적 메모리 해제
    free(input);
    free(stack);

    return 0;
}