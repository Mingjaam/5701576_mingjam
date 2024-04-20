#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX_STACK_SIZE 5

typedef int element;
typedef struct Stacktype {
    element* data;
    int capacity;
    int top;
} StackType;

void init(StackType* sptr, int ofs) {
    sptr->data = (element*)malloc(sizeof(element) * ofs);
    sptr->top = -1;
    sptr->capacity = ofs;
}

int is_full(StackType* sptr) {
    if (sptr->top == sptr->capacity - 1) {
        sptr->capacity = sptr->capacity * 2;
        sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));
    }
    return 0;
}

int is_empty(StackType* sptr) {
    return (sptr->top == -1);
}

void push(StackType* sptr, element item) {
    if (is_full(sptr)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    else {
        sptr->top = sptr->top + 1;
        sptr->data[sptr->top] = item;
    }
}

element pop(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "stack is empty\n");
        return -1;
    }
    else {
        return (sptr->data[(sptr->top)--]);
    }
}

element peek(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "stack is empty\n");
        return -1;
    }
    else {
        return (sptr->data[sptr->top]);
    }
}

void stack_print(StackType* sptr) {
    for (int i = sptr->top; i >= 0; i--) {
        printf("[%d]", sptr->data[i]);
    }
    printf("\n");
}

int prec(char op) {
    switch (op) {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

void infix_to_postfix(char expr[], char postfix[]) {
    StackType s;
    init(&s, MAX_STACK_SIZE);
    int len = strlen(expr);
    int idx = 0;
    for (int i = 0; i < len; i++) {
        switch (expr[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
            while (!is_empty(&s) && prec(expr[i]) <= prec((char)peek(&s))) {
                postfix[idx++] = (char)pop(&s);
            }
            push(&s, (int)expr[i]);
            break;
        case '(':
            push(&s, (int)expr[i]);
            break;
        case ')':
            while (!is_empty(&s) && (char)peek(&s) != '(') {
                postfix[idx++] = (char)pop(&s);
            }
            pop(&s);
            break;
        default:
            postfix[idx++] = expr[i];
            break;
        }
    }
    while (!is_empty(&s)) {
        postfix[idx++] = (char)pop(&s);
    }
    postfix[idx] = '\0';
}

int eval(char expr[]) {
    int len;
    StackType s;

    init(&s, 20);
    len = strlen(expr);

    for (int i = 0; i < len; i++) {
        int ch = expr[i];
        int value;
        int op1, op2;

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            op1 = pop(&s);
            op2 = pop(&s);
            switch (ch) {
            case '+':
                push(&s, op2 + op1);
                break;
            case '-':
                push(&s, op2 - op1);
                break;
            case '*':
                push(&s, op2 * op1);
                break;
            case '/':
                push(&s, op2 / op1);
                break;
            default:
                break;
            }
        }
        else if (ch >= '0' && ch <= '9') {
            value = ch - '0';
            push(&s, value);
        }
    }
    return pop(&s);
}

int main() {
    char expr[100];
    char postfix[100];
    int result;

    while (1) {
        printf("������ ���� �޴��� �����ϴ� ���α׷��Դϴ�.\n");
        printf("1. �������� �Է¹���\n");
        printf("2. �������� ���������� ��ȯ\n");
        printf("3. �������� ���\n");
        printf("4. ����\n");
        printf("�޴��� �����ϼ���: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("������ ǥ�� �Է�: ");
            getchar();
            fgets(expr, sizeof(expr), stdin);
            expr[strcspn(expr, "\n")] = '\0';
            printf("�Էµ� ������ : %s\n", expr);
            break;

        case 2:
            infix_to_postfix(expr, postfix);
            printf("������ ǥ��: %s\n", postfix);
            break;

        case 3:
            result = eval(postfix);
            printf("������ ��� ���: %d\n", result);
            break;
        case 4:
            printf("���α׷��� �����մϴ�.\n");
            exit(1);
            break;
        default:
            printf("�߸��� �޴� �����Դϴ�.\n");
            break;
        }
    }
    return 0;
}
