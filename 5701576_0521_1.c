#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUITS 10
#define MAX_NAME_LENGTH 50

typedef struct ListNode {
    char fruit[MAX_NAME_LENGTH];
    struct ListNode* link;
} ListNode;

const char* initial_fruits[MAX_FRUITS] = {
    "Mango", "Orange", "Apple", "Grape", "Cherry",
    "Plum", "Guava", "Raspberry", "Banana", "Peach"
};

ListNode* insert_last(ListNode* head, ListNode** tail, const char* fruit) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->fruit, fruit);
    newNode->link = NULL;

    if (head == NULL) {
        *tail = newNode;
        return newNode;
    }

    (*tail)->link = newNode;
    *tail = newNode;
    return head;
}

ListNode* delete_fruit(ListNode* head, ListNode** tail, const char* fruit, ListNode** deleted_head) {
    ListNode* p = head, * prev = NULL;

    while (p != NULL && strcmp(p->fruit, fruit) != 0) {
        prev = p;
        p = p->link;
    }

    if (p == NULL) {
        printf("�ش� ������ ����Ʈ�� �����ϴ�.\n");
        return head;
    }

    if (prev == NULL) {
        head = head->link;
    }
    else {
        prev->link = p->link;
    }

    if (*tail == p) {
        *tail = prev;
    }

    p->link = *deleted_head;
    *deleted_head = p;

    printf("���� '%s'��(��) �����߽��ϴ�.\n", fruit);
    return head;
}

void print_list(const ListNode* head) {
    const ListNode* p = head;
    while (p != NULL) {
        printf("%s ", p->fruit);
        p = p->link;
    }
    printf("\n");
}

int is_fruit_found(const ListNode* head, const char* fruit) {
    const ListNode* p = head;
    while (p != NULL) {
        if (strcmp(p->fruit, fruit) == 0) {
            return 1;
        }
        p = p->link;
    }
    return 0;
}

// ���� �Լ�
int main() {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    ListNode* deleted_head = NULL;
    int choice;
    char fruit[MAX_NAME_LENGTH];

    // �ʱ� ���� ����Ʈ ����
    for (int i = 0; i < MAX_FRUITS; i++) {
        head = insert_last(head, &tail, initial_fruits[i]);
    }

    while (1) {
        printf("�޴�:\n");
        printf("1. ����Ʈ�� �������� ���� �߰�\n");
        printf("2. ����Ʈ���� ���� ����\n");
        printf("3. ������ ���� ��� ���\n");
        printf("4. ����\n");
        printf("����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("�߰��� ���� �Է�: ");
            scanf("%s", fruit);
            if (is_fruit_found(head, fruit)) {
                printf("[%s] �̹� ����Ʈ�� �����մϴ�.\n", fruit);
            }
            else {
                head = insert_last(head, &tail, fruit);
                printf("[%s] ����Ʈ�� �߰��߽��ϴ�.\n", fruit);
            }
            break;
        case 2:
            printf("������ ���� �̸� �Է�: ");
            scanf("%s", fruit);
            head = delete_fruit(head, &tail, fruit, &deleted_head);
            break;
        case 3:
            printf("������ ���� ���:\n");
            print_list(deleted_head);
            break;
        case 4:
            while (head != NULL) {
                ListNode* temp = head;
                head = head->link;
                free(temp);
            }
            while (deleted_head != NULL) {
                ListNode* temp = deleted_head;
                deleted_head = deleted_head->link;
                free(temp);
            }
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
    return 0;
}
