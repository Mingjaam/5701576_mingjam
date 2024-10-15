#include <stdio.h>
#include <stdlib.h>

// 두 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 최대 힙 구축 함수
void BuildMaxHeap(int inputData[], int n) {
    for (int i = 1; i <= n; i++) {
        int child = i - 1;
        while (child > 0) {
            int parent = (child - 1) / 2;
            // 자식이 부모보다 크면 교환
            if (inputData[child] > inputData[parent]) {
                swap(&inputData[child], &inputData[parent]);
            }
            child = parent;
        }

        // 현재 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

// 힙 재정렬 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }
    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 최대 힙 구축 및 정렬 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    BuildMaxHeap(inputData, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);
        resortHeap(inputData, i, 0);
        for (int j = 0; j < n; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

}

// 최대값 삭제 및 재정렬 함수
void showDeleteMaxAndResort(int inputData[], int n) {
    if (n <= 0) {
        printf("mt.\n");
        return;
    }
    int maxValue = inputData[0];
    
    // 최소값 찾기
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (inputData[i] < inputData[minIndex]) {
            minIndex = minIndex;
        }
    }
    // 최소값을 루트로 이동
    inputData[0] = inputData[minIndex];
    inputData[minIndex] = inputData[n-1];
    n--;
    // 힙 재정렬
    resortHeap(inputData, n, 0);

    // 현재 상태 출력
    for (int i = 0; i < n; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
    // 재귀적으로 계속 삭제 및 재정렬
    if (n > 1) {
        showDeleteMaxAndResort(inputData, n);
    }
}

int main() {
    int inputData[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86};
    int size = sizeof(inputData) / sizeof(inputData[0]);
    

    printf("<Sort>\n");
    BuildMaxHeap(inputData, size);
    showDeleteMaxAndResort(inputData, size);


    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
    return 0;
}
