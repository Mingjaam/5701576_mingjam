#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BuildMaxHeap(int inputData[], int n) {
    for (int i = 1; i <= n; i++) {
        int child = i - 1;
        while (child > 0) {
            int parent = (child - 1) / 2;
            if (inputData[child] > inputData[parent]) {
                swap(&inputData[child], &inputData[parent]);
            }
            child = parent;
        }

        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");

    }
}

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

void showDeleteMaxAndResort(int inputData[], int n) {
    if (n <= 0) {
        printf("mt.\n");
        return;
    }
    int maxValue = inputData[0];
    
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (inputData[i] < inputData[minIndex]) {
            minIndex = minIndex;
        }
    }
    inputData[0] = inputData[minIndex];
    inputData[minIndex] = inputData[n-1];
    n--;
    resortHeap(inputData, n, 0);

    for (int i = 0; i < n; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
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
