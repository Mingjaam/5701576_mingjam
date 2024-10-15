#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    int frequency;
    struct Node *left, *right;
} Node;

// 새로운 노드 생성 함수
Node* newNode(char data, int frequency) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->frequency = frequency;
    return temp;
}

// 우선순위 큐 구현을 위한 함수들
void swapNodes(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(Node* nodeArr[], int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && nodeArr[left]->frequency < nodeArr[smallest]->frequency)
        smallest = left;

    if (right < size && nodeArr[right]->frequency < nodeArr[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&nodeArr[idx], &nodeArr[smallest]);
        minHeapify(nodeArr, size, smallest);
    }
}

Node* extractMin(Node* nodeArr[], int* size) {
    Node* temp = nodeArr[0];
    nodeArr[0] = nodeArr[*size - 1];
    --*size;
    minHeapify(nodeArr, *size, 0);
    return temp;
}

void insertMinHeap(Node* nodeArr[], int* size, Node* node) {
    ++*size;
    int i = *size - 1;
    while (i && node->frequency < nodeArr[(i - 1) / 2]->frequency) {
        nodeArr[i] = nodeArr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    nodeArr[i] = node;
}

// 현재 힙의 상태를 출력하는 함수
void printHeap(Node* nodeArr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", nodeArr[i]->frequency);
    }
    printf("\n");
}

// 허프만 트리 구축 함수 (수정됨)
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* nodeArr[size];
    int heapSize = 0;
    
    for (int i = 0; i < size; ++i) {
        nodeArr[i] = newNode(characters[i], frequencies[i]);
        insertMinHeap(nodeArr, &heapSize, nodeArr[i]);
        printHeap(nodeArr, heapSize);  // 각 원소 추가 후 힙 상태 출력
    }

    while (heapSize > 1) {
        Node* left = extractMin(nodeArr, &heapSize);
        Node* right = extractMin(nodeArr, &heapSize);
        Node* top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(nodeArr, &heapSize, top);

        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);
        printHeap(nodeArr, heapSize);
    }

    return extractMin(nodeArr, &heapSize);
}

// 허프만 코드 출력 함수
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[size], top = 0;
    printCodes(root, arr, top);
}


int main() {
    char characters[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};
    int frequencies[] = {10, 15, 12, 3, 4, 13, 1};
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
