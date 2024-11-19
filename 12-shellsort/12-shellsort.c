#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 랜덤 배열 생성 함수
void generateRandomNumbers(int array1[], int array2[], int array3[]) {
    srand(time(NULL));  // 한 번만 시드 설정
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int randNum = rand() % 1000;  // 랜덤 값 한 번만 생성
        array1[i] = randNum;
        array2[i] = randNum;
        array3[i] = randNum;
    }
}

// 쉘 정렬 함수
void doShellSort(int arr[], int divisor, int* compCount, int* moveCount) {
    *compCount = 0;
    *moveCount = 0;
    int n = ARRAY_SIZE;
    
    for (int gap = n/divisor; gap > 0; gap /= divisor) {
        printf("gap = %d: ", gap);
        
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            (*moveCount)++;
            
            int j;
            for (j = i; j >= gap; j -= gap) {
                (*compCount)++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    (*moveCount)++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
            (*moveCount)++;
        }
        
        // 현재 gap에서의 배열 상태 출력 (20개까지만)
        for (int i = 0; i < 20 && i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("...\n");
    }
    
    // gap이 1이 된 후 최종 정렬된 배열 출력
    printf("Sorted Array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 삽입 정렬 함수
void doInsertionSort(int arr[], int* compCount, int* moveCount) {
    *compCount = 0;
    *moveCount = 0;
    int n = ARRAY_SIZE;
    
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        (*moveCount)++;
        
        int j;
        for (j = i; j > 0; j--) {
            (*compCount)++;
            if (arr[j - 1] > temp) {
                arr[j] = arr[j - 1];
                (*moveCount)++;
            } else {
                break;
            }
        }
        arr[j] = temp;
        (*moveCount)++;
    }
    
    // 정렬된 배열 출력
    printf("Sorted Array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int array1[ARRAY_SIZE];  // Shell Sort (n/2)용
    int array2[ARRAY_SIZE];  // Shell Sort (n/3)용
    int array3[ARRAY_SIZE];  // Insertion Sort용
    int comparisonCount, moveCount;
    
    generateRandomNumbers(array1, array2, array3);
    
    // Shell Sort (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array1, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);
    
    // Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array2, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);
    
    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array3, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);
    
    return 0;
}