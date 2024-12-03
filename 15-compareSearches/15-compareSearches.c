#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0;

void printArray(int *array) {
    printf("Array Sorting Result:\n");
    for(int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for(int i = SIZE-20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// 랜덤 배열 생성 함수
void generateRandomArray(int *array) {
    for(int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0-999 사이의 랜덤 숫자
    }
}

// 순차 탐색 한 번 수행
int linearSearch(int *array, int target) {
    compareCount = 0;
    for(int i = 0; i < SIZE; i++) {
        compareCount++;
        if(array[i] == target)
            return i;
    }
    return -1;
}

// 순차 탐색 100회 수행 및 평균 비교횟수 반환
float getAverageLinearSearchCompareCount(int *array) {
    int totalCompares = 0;
    for(int i = 0; i < 100; i++) {
        int key = rand() % 1000;
        int target = array[key];
        linearSearch(array, target);
        totalCompares += compareCount;
    }
    return (float)totalCompares / 100;
}

// 퀵소트 파티션 함수
int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
        compareCount++;
        if(array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

// 퀵소트 구현
void quickSort(int *array, int low, int high) {
    if(low < high) {
        int pivotIndex = partition(array, low, high);
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

// 퀵소트 비교횟수 반환
int getQuickSortCompareCount(int *array) {
    compareCount = 0;
    quickSort(array, 0, SIZE-1);
    return compareCount;
}

// 이진 탐색 구현
int binarySearch(int *array, int target) {
    compareCount = 0;
    int left = 0;
    int right = SIZE - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        compareCount++;
        
        if(array[mid] == target)
            return mid;
        
        if(array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 이진 탐색 100회 수행 및 평균 비교횟수 반환
float getAverageBinarySearchCompareCount(int *array) {
    int totalCompares = 0;
    for(int i = 0; i < 100; i++) {
        int key = rand() % 1000;
        int target = array[key];
        binarySearch(array, target);
        totalCompares += compareCount;
    }
    return (float)totalCompares / 100;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    // 평균값을 반환받기 위한 조치
    printf("Average Linear Search Compare Count: %.2f\n",
    getAverageLinearSearchCompareCount(array));
    //compareCount 가 global variable이므로 , 다음과 같이 구현
    //array에 대해서 직접 정렬하면 된다.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    // 정렬된 Array에 대해서 Binary Search 100 회 수행 및 평균 비교횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
    getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}