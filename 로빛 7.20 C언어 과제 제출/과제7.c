#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char tag[20];
    struct Node *next;
} Node;

Node *top = NULL;

// push
void push(char *tag) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->tag, tag);
    newNode->next = top;
    top = newNode;
}

// pop
void pop() {
    if (top == NULL)
        return;

    Node *temp = top;
    top = top->next;
    free(temp);
}

// peek
char *peek() {
    if (top == NULL)
        return NULL;
    return top->tag;
}

int isEmpty() {
    return top == NULL;
}

void printIndent(int depth) {
    for (int i = 0; i < depth; i++)
        printf(" ");
}

int main() {

    char input[1000];

    printf("입력 : ");
    fgets(input, sizeof(input), stdin);

    int i = 0;
    int depth = 0;

    while (input[i] != '\0') {

        if (input[i] == '<') {

            char tag[20];
            int j = 0;
            i++;

            while (input[i] != '>' && input[i] != '\0') {
                tag[j++] = input[i++];
            }
            tag[j] = '\0';

            // 닫는 태그
            if (tag[0] == '/') {

                char closeTag[20];
                strcpy(closeTag, tag + 1);

                if (isEmpty() || strcmp(peek(), closeTag) != 0) {
                    printf("\n오류 : 태그 구조가 올바르지 않습니다.\n");
                    return 0;
                }

                depth--;

                printIndent(depth);
                printf("</%s>\n", closeTag);

                pop();
            }
            // 여는 태그
            else {

                printIndent(depth);
                printf("<%s>\n", tag);

                push(tag);
                depth++;
            }
        }

        else {

            char text[200];
            int j = 0;

            while (input[i] != '<' && input[i] != '\0') {
                text[j++] = input[i++];
            }
            text[j] = '\0';

            if (strlen(text) > 0) {
                printIndent(depth);
                printf("%s\n", text);
            }

            continue;
        }

        i++;
    }

    if (!isEmpty()) {
        printf("\n오류 : 닫히지 않은 태그가 있습니다.\n");
        return 0;
    }

    return 0;
}