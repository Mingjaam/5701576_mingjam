#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink, * rlink;
} DListNode;

void init(DListNode* phead) {
    phead->llink = phead->rlink = phead;
}

void dinsert_first(DListNode* head, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = head;
    newnode->rlink = head->rlink;
    head->rlink->llink = newnode;
    head->rlink = newnode;
}

void dinsert_last(DListNode* head, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = head->llink;
    newnode->rlink = head;
    head->llink->rlink = newnode;
    head->llink = newnode;
}

void ddelete_first(DListNode* head) {
    if (head->rlink == head) return;
    DListNode* removed = head->rlink;
    head->rlink = removed->rlink;
    removed->rlink->llink = head;
    free(removed);
}

void ddelete_last(DListNode* head) {
    if (head->rlink == head) return;
    DListNode* removed = head->llink;
    head->llink = removed->llink;
    removed->llink->rlink = head;
    free(removed);
}

void print_dlist(DListNode* head) {
    DListNode* p; 
    for (p = head->rlink; p != head; p = p->rlink) {
        printf("%d -> ", p->data);
    }
    printf("(head) \n");
}

int main() {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    int choice;
    element data;

    while (1) {
        printf("\n\n[�޴�]\n");
        printf("(1) ���� �Է� �޾Ƽ� ����Ʈ ó���� �߰�\n");
        printf("(2) ���� �Է� �޾Ƽ� ����Ʈ �������� �߰�\n");
        printf("(3) ����Ʈ ó�� ��� ����\n");
        printf("(4) ����Ʈ ������ ��� ����\n");
        printf("(5) ����Ʈ ����Ʈ\n");
        printf("(6) ����\n");
        printf("�޴� ����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("�߰��� ���� �Է�: ");
            scanf("%d", &data);
            dinsert_first(head, data);
            printf("����Ʈ�� %d �߰���.\n", data);
            break;
        case 2:
            printf("�߰��� ���� �Է�: ");
            scanf("%d", &data);
            dinsert_last(head, data);
            printf("����Ʈ�� %d �߰���.\n", data);
            break;
        case 3:
            if (head->rlink == head) {
                printf("����Ʈ�� ����ֽ��ϴ�.\n");
            }
            else {
                ddelete_first(head);
                printf("����Ʈ�� ó�� ��� ������.\n");
            }
            break;
        case 4:
            if (head->rlink == head) {
                printf("����Ʈ�� ����ֽ��ϴ�.\n");
            }
            else {
                ddelete_last(head);
                printf("����Ʈ�� ������ ��� ������.\n");
            }
            break;
        case 5:
            if (head->rlink == head) {
                printf("����Ʈ�� ����ֽ��ϴ�.\n");
            }
            else {
                printf("����Ʈ ���: ");
                print_dlist(head);
            }
            break;
        case 6:
            printf("���α׷��� �����մϴ�.\n");
            exit(0);
        default:
            printf("�߸��� �޴� �����Դϴ�.\n");
        }
    }

    return 0;
}
