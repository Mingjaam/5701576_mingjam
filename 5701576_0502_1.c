#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100


typedef int element;

typedef struct {
    element data[MAX_SIZE];
    int top;
} StackType;

typedef struct {
    element data[MAX_SIZE];
    int front, rear;
} QueueType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_stack_full(StackType* s) {
    return (s->top == MAX_SIZE - 1);
}

void push(StackType* s, element item) {
    if (is_stack_full(s)) {
        printf("Stack is Full.\n");
        return;
    }
    s->data[++(s->top)] = item;
}

element pop(StackType* s) {
    if (s->top == -1) {
        printf("Stack is Empty.\n");
        return -1; 
    }
    return s->data[(s->top)--];
}

int is_full(QueueType* q) {
    return (q->front == (q->rear + 1) % MAX_SIZE);
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        printf("Queue is Full.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        printf("Queue is Empty.\n");
        return -1;
    }
    q->front = (q->front + 1) % MAX_SIZE;
    return q->data[q->front];
}

int is_palindrome(char* str) {
    int i, len = 0;
    QueueType queue;
    StackType stack;
    init_queue(&queue);
    init_stack(&stack);

    len = strlen(str);

    for (i = 0; i < len; i++) {
        char c = str[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            c = (c >= 'A' && c <= 'Z') ? c + 32 : c;
            enqueue(&queue, c);
            push(&stack, c);
        }
    }

    while (!is_empty(&queue)) {
        char front = dequeue(&queue);
        char top = pop(&stack);
        if (front != top) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str[100];
    int choice;

    do {
        printf("\n1. 회문 입력\n2. 회문 검사\n3. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("회문을 입력하세요: ");
            getchar();
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0'; 
            break;
        case 2:
            if (is_palindrome(str))
                printf("'%s'는 회문입니다.\n", str);
            else
                printf("'%s'는 회문이 아닙니다.\n", str);
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    } while (choice != 3);

    return 0;
}