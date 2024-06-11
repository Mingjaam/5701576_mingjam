#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

void init(DListNode* phead) {
    phead->llink = phead->rlink = phead;
}

void dinsert(DListNode* current, element data) {
    if (current == NULL) {
        printf("���� ��尡 ��ȿ���� �ʽ��ϴ�.\n");
        return;
    }

    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    if (newnode == NULL) {
        printf("�޸� �Ҵ� �����Դϴ�.\n");
        return;
    }

    strcpy(newnode->data, data);
    newnode->rlink = current->rlink;
    newnode->llink = current;
    current->rlink->llink = newnode;
    current->rlink = newnode;
}

void ddelete(DListNode* current) {
    if (current == NULL) {
        printf("���� ��尡 ��ȿ���� �ʽ��ϴ�.\n");
        return;
    }

    if (current->llink == current || current->rlink == current) {
        printf("��ȿ�� ��尡 �ϳ����̹Ƿ� ������ �� �����ϴ�.\n");
        return;
    }

    DListNode* removed = current;
    current->llink->rlink = current->rlink;
    current->rlink->llink = current->llink;
    current = current->llink;  // ���� ��带 ���� ���� ����
    free(removed);
}

void print_dlist(DListNode* head, DListNode* current) {
    DListNode* p;
    for (p = head->rlink; p != head; p = p->rlink) {
        printf("%s", p->data);
        if (p == current)
            printf(" <==");
        printf("\n");
    }
}

void print_menu() {
    printf("\n N(����), P(����), I(����), D(����), Q(����): ");
}

char get_command() {
    char command;
    scanf(" %c", &command);
    return command;
}

DListNode* do_command(DListNode* head, DListNode* current, char cmd) {
    element data;

    switch (cmd) {
    case 'N':
        if (current == NULL) {
            printf("���� ��尡 ��ȿ���� �ʽ��ϴ�.\n");
            return current;
        }
        if (current->rlink == head) {
            return head->rlink; // ù ��° ���� �̵�
        }
        return current->rlink;
    case 'P':
        if (current == NULL) {
            printf("���� ��尡 ��ȿ���� �ʽ��ϴ�.\n");
            return current;
        }
        if (current == head->rlink) {
            return head->llink; // ������ ���� �̵�
        }
        return current->llink;
    case 'I':
        printf("\n�뷡 ���� �Է�: ");
        scanf("%s", data);
        dinsert(current, data);
        printf("%s�� ���� ��� �ڿ� �����߽��ϴ�.\n", data);
        return current->rlink;  // ���� ��带 ���� ���� ����
    case 'D':
        ddelete(current);
        printf("���� ��带 �����߽��ϴ�.\n");
        return current->llink;  // ���� �� ���� ��带 ���� ���� ����
    case 'Q':
        printf("���α׷��� �����մϴ�.\n");
        exit(0);
    default:
        printf("�߸��� ����Դϴ�.\n");
        return current;
    }
}

int main() {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    if (head == NULL) {
        printf("�޸� �Ҵ� �����Դϴ�.\n");
        return -1;
    }
    init(head);

    // �ʱ⿡ ����Ʈ�� �˼� 5���� �߰�
    element songs[5] = { "Song1", "Song2", "Song3", "Song4", "Song5" };
    DListNode* current = head;
    for (int i = 0; i < 5; ++i) {
        dinsert(current, songs[i]);
        current = current->rlink;
        for (int i = 0; i < 5; ++i) {
            dinsert(current, songs[i]);
            current = current->rlink;
        }

        char command;

        while (1) {
            printf("\n���� ����Ʈ:\n");
            print_dlist(head, current);
            print_menu();
            command = get_command();
            current = do_command(head, current, command);
        }
    }

}
