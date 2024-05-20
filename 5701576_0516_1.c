#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// ����Ʈ�� ó���� ��带 �����ϴ� �Լ�
ListNode* insert_first(ListNode* head, element value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->link = head;
    return newNode;
}

// �־��� ��ġ�� ��带 �����ϴ� �Լ�
ListNode* insert(ListNode* head, int pos, element value, int* move_count) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;

    *move_count = 0;
    if (pos == 0) {
        newNode->link = head;
        return newNode;
    }

    ListNode* p = head;
    while (*move_count < pos - 1 && p != NULL) {
        p = p->link;
        (*move_count)++;
    }

    if (p == NULL) {
        fprintf(stderr, "����: ��ġ�� ����Ʈ ���̸� �ʰ��߽��ϴ�\n");
        free(newNode);
        return head;
    }

    newNode->link = p->link;
    p->link = newNode;
    (*move_count)++;
    return head;
}

// �־��� ��ġ�� ��带 �����ϴ� �Լ�
ListNode* delete(ListNode* head, int pos, int* move_count) {
    *move_count = 0;

    if (head == NULL) {
        fprintf(stderr, "����: �� ����Ʈ\n");
        return NULL;
    }

    ListNode* temp;
    if (pos == 0) {
        temp = head;
        head = head->link;
        free(temp);
        (*move_count)++;
        return head;
    }

    ListNode* p = head;
    while (*move_count < pos - 1 && p->link != NULL) {
        p = p->link;
        (*move_count)++;
    }

    if (p->link == NULL) {
        fprintf(stderr, "����: ��ġ�� ����Ʈ ���̸� �ʰ��߽��ϴ�\n");
        return head;
    }

    temp = p->link;
    p->link = temp->link;
    free(temp);
    (*move_count) += 2;
    return head;
}

// ����Ʈ�� ����ϴ� �Լ�
void print_list(const ListNode* head) {
    const ListNode* p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL \n");
}

// ���� �Լ�
int main() {
    ListNode* head = NULL;
    int choice, value, pos, move_count;

    while (1) {
        printf("�޴�:\n");
        printf("1. ����Ʈ�� �߰�\n");
        printf("2. ����Ʈ���� ����\n");
        printf("3. ����Ʈ ���\n");
        printf("0. ����\n");
        printf("����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("�߰� �� ����: ");
            scanf("%d", &value);
            printf("�߰� �� ��ġ : ");
            scanf("%d", &pos);
            head = insert(head, pos, value, &move_count);
            printf("�̵��� ��ũ ��: %d\n", move_count);
            break;
        case 2:
            printf("������ ��ġ �Է�: ");
            scanf("%d", &pos);
            head = delete(head, pos, &move_count);
            printf("�̵��� ��ũ ��: %d\n", move_count);
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            // ����Ʈ �޸� ����
            while (head != NULL) {
                head = delete(head, 0, &move_count);
            }
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
    return 0;
}
