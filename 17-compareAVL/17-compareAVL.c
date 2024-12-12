#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 비교 횟수와 검색 횟수를 저장하는 전역 변수
int compareCount = 0;
int searchCount = 0;

// AVL 트리 노드 구조체 정의
typedef struct Node {
    int key; // 노드의 키
    struct Node *left; // 왼쪽 자식 노드
    struct Node *right; // 오른쪽 자식 노드
    int height; // 노드의 높이
} Node;

// 새로운 노드 생성 함수
Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // 초기 높이는 1로 설정
    return node;
}

// 노드의 높이 반환 함수
int getHeight(Node *node) {
    if (node == NULL) {
        return 0; // 노드가 NULL인 경우 높이는 0으로 반환
    }
    return node->height; // 노드의 높이 반환
}

// 노드의 균형 계산 함수
int getBalance(Node *node) {
    if (node == NULL) {
        return 0; // 노드가 NULL인 경우 균형은 0으로 반환
    }
    return getHeight(node->left) - getHeight(node->right); // 왼쪽 자식과 오른쪽 자식의 높이 차이 반환
}

// 오른쪽으로 회전하는 함수
Node *rotateRight(Node *y) {
    Node *x = y->left; // 왼쪽 자식 노드
    Node *T2 = x->right; // 왼쪽 자식의 오른쪽 자식 노드

    x->right = y; // 왼쪽 자식의 오른쪽 자식으로 y 노드 설정
    y->left = T2; // y 노드의 왼쪽 자식으로 T2 노드 설정

    // 높이 재계산
    y->height = 1 + getHeight(y->left) > getHeight(y->right) 
                ? getHeight(y->left) : getHeight(y->right);
    x->height = 1 + getHeight(x->left) > getHeight(x->right) 
                ? getHeight(x->left) : getHeight(x->right);

    return x; // 회전된 노드 반환
}

// 왼쪽으로 회전하는 함수
Node *rotateLeft(Node *x) {
    Node *y = x->right; // 오른쪽 자식 노드
    Node *T2 = y->left; // 오른쪽 자식의 왼쪽 자식 노드

    y->left = x; // 오른쪽 자식의 왼쪽 자식으로 x 노드 설정
    x->right = T2; // x 노드의 오른쪽 자식으로 T2 노드 설정

    // 높이 재계산
    x->height = 1 + getHeight(x->left) > getHeight(x->right) 
                ? getHeight(x->left) : getHeight(x->right);
    y->height = 1 + getHeight(y->left) > getHeight(y->right) 
                ? getHeight(y->left) : getHeight(y->right);

    return y; // 회전된 노드 반환
}

// AVL 트리 삽입 함수
Node *insertAVL(Node *root, int key) {
    if (root == NULL) {
        return createNode(key); // 노드가 NULL인 경우 새로운 노드 생성
    }
    if (key < root->key) {
        root->left = insertAVL(root->left, key); // 키가 작으면 왼쪽 자식에 삽입
    } else if (key > root->key) {
        root->right = insertAVL(root->right, key); // 키가 크면 오른쪽 자식에 삽입
    }
    return root;
    // 노드의 높이 재계산
    root->height = 1 + getHeight(root->left) > getHeight(root->right) 
                   ? getHeight(root->left) : getHeight(root->right);

    // 균형 계산
    int balance = getBalance(root);

    // 균형 조정
    if (balance > 1 && key < root->left->key) {
        return rotateRight(root); // 오른쪽으로 회전
    }
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root); // 왼쪽으로 회전
    }
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left); // 왼쪽 자식 왼쪽으로 회전
        return rotateRight(root); // 오른쪽으로 회전
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right); // 오른쪽 자식 오른쪽으로 회전
        return rotateLeft(root); // 왼쪽으로 회전
    }
    return root;
}

// 트리 출력 함수
void printTree(Node *root) {
    if (root == NULL) {
        return; // 노드가 NULL인 경우 반환
    }
    printTree(root->left); // 왼쪽 자식 출력
    printf("%d ", root->key); // 노드의 키 출력
    printTree(root->right); // 오른쪽 자식 출력
}

// 트리에서 키를 검색하는 함수
Node* search(Node* root, int key) {
    if (root == NULL) return NULL; // 노드가 NULL인 경우 반환

    compareCount++; // 비교 횟수 증가
    if (key == root->key) return root; // 키가 일치하면 노드 반환
    
    compareCount++; // 비교 횟수 증가
    if (key < root->key)
        return search(root->left, key); // 키가 작으면 왼쪽 자식에서 검색
    return search(root->right, key); // 키가 크면 오른쪽 자식에서 검색
}

// 최소 키를 가진 노드 찾는 함수
Node* findMin(Node* node) {
    Node* current = node; // 현재 노드
    while (current->left != NULL)
        current = current->left; // 왼쪽 자식이 NULL이 될 때까지 이동
    return current; // 최소 키를 가진 노드 반환
}

// AVL 트리에서 키를 삭제하는 함수
Node* deleteAVL(Node* root, int key) {
    if (root == NULL) return root; // 노드가 NULL인 경우 반환

    if (key < root->key)
        root->left = deleteAVL(root->left, key); // 키가 작으면 왼쪽 자식에서 삭제
    else if (key > root->key)
        root->right = deleteAVL(root->right, key); // 키가 크면 오른쪽 자식에서 삭제
    else {
        if (root->left == NULL) {
            Node* temp = root->right; // 오른쪽 자식 노드
            free(root); // 노드 메모리 해제
            return temp; // 오른쪽 자식 노드 반환
        } else if (root->right == NULL) {
            Node* temp = root->left; // 왼쪽 자식 노드
            free(root); // 노드 메모리 해제
            return temp; // 왼쪽 자식 노드 반환
        }
        Node* temp = findMin(root->right); // 오른쪽 자식에서 최소 키를 가진 노드 찾기
        root->key = temp->key; // 노드의 키를 최소 키로 설정
        root->right = deleteAVL(root->right, temp->key); // 오른쪽 자식에서 최소 키를 가진 노드 삭제
    }

    // 노드의 높이 재계산
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) 
                    ? getHeight(root->left) : getHeight(root->right));

    // 균형 계산
    int balance = getBalance(root);

    // 균형 조정
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root); // 오른쪽으로 회전
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root); // 왼쪽으로 회전
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left); // 왼쪽 자식 왼쪽으로 회전
        return rotateRight(root); // 오른쪽으로 회전
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right); // 오른쪽 자식 오른쪽으로 회전
        return rotateLeft(root); // 왼쪽으로 회전
    }

    return root;
}

// 이진 트리에서 키를 삭제하는 함수
Node *deleteBinary(Node *root, int key) {
    if (root == NULL) return root; // 노드가 NULL인 경우 반환

    if (key < root->key)
        root->left = deleteBinary(root->left, key); // 키가 작으면 왼쪽 자식에서 삭제
    else if (key > root->key)
        root->right = deleteBinary(root->right, key); // 키가 크면 오른쪽 자식에서 삭제
    else {
        if (root->left == NULL) {
            Node* temp = root->right; // 오른쪽 자식 노드
            free(root); // 노드 메모리 해제
            return temp; // 오른쪽 자식 노드 반환
        } else if (root->right == NULL) {
            Node* temp = root->left; // 왼쪽 자식 노드
            free(root); // 노드 메모리 해제
            return temp; // 왼쪽 자식 노드 반환
        }
        Node* temp = findMin(root->right); // 오른쪽 자식에서 최소 키를 가진 노드 찾기
        root->key = temp->key; // 노드의 키를 최소 키로 설정
        root->right = deleteBinary(root->right, temp->key); // 오른쪽 자식에서 최소 키를 가진 노드 삭제
    }
    return root;
}

// 이진 트리 삽입 함수
Node *insertBinary(Node *root, int key) {
    if (root == NULL) return createNode(key); // 노드가 NULL인 경우 새로운 노드 생성
    if (key < root->key)
        root->left = insertBinary(root->left, key); // 키가 작으면 왼쪽 자식에 삽입
    else if (key > root->key)
        root->right = insertBinary(root->right, key); // 키가 크면 오른쪽 자식에 삽입
    return root;
}

// 트리 메모리 해제 함수
void freeTree(Node* root) {
    if (root == NULL) return; // 노드가 NULL인 경우 반환
    freeTree(root->left); // 왼쪽 자식 트리 메모리 해제
    freeTree(root->right); // 오른쪽 자식 트리 메모리 해제
    free(root); // 노드 메모리 해제
}

// AVL 트리 배치 함수
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // 0, 1, 2 중 하나의 값을 랜덤으로 선택
        int B = rand() % 1000; // 0부터 999까지의 랜덤 숫자 생성
        
        switch(A) {
            case 0:
                root = insertAVL(root, B); // AVL 트리에 삽입
                break;
            case 1:
                root = deleteAVL(root, B); // AVL 트리에서 삭제
                break;
            case 2:
                searchCount++; // 검색 횟수 증가
                search(root, B); // AVL 트리에서 검색
                break;
        }
    }
}

// 이진 트리 배치 함수
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // 0, 1, 2 중 하나의 값을 랜덤으로 선택
        int B = rand() % 1000; // 0부터 999까지의 랜덤 숫자 생성
        
        switch(A) {
            case 0:
                root = insertBinary(root, B); // 이진 트리에 삽입
                break;
            case 1:
                root = deleteBinary(root, B); // 이진 트리에서 삭제
                break;
            case 2:
                searchCount++; // 검색 횟수 증가
                search(root, B); // 이진 트리에서 검색
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    Node *root = NULL; // AVL 트리 및 이진 트리의 루트 노드
    srand(time(NULL)); // 랜덤 시드 설정
    float allCount = 0.0; // 평균 비교 횟수 저장

    doAVLBatch(root); // AVL 트리 배치 실행
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
    printf("average AVL compare count: %.2f\n", allCount); // 결과 출력
    
    freeTree(root); // AVL 트리 메모리 해제
    root = NULL; // 루트 노드 초기화
    compareCount = searchCount = allCount = 0; // 변수 초기화

    doBinaryBatch(root); // 이진 트리 배치 실행
    allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
    printf("average Bin compare count: %.2f\n", allCount); // 결과 출력
    freeTree(root); // 이진 트리 메모리 해제
    return 0;
}