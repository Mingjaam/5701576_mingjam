#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define numRange 10000
#define arrSize 1000

// 배열의 처음과 끝 일부를 출력하는 함수
void printArray(int *array) {
    printf("Array Sorting Result:\n");
    for(int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for(int i = arrSize-20; i < arrSize; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
} 

// 배열에 랜덤한 값을 생성하여 채우는 함수
void generateRandomArray(int *array) {
    for(int i = 0; i < arrSize; i++) {
        array[i] = rand() % numRange; 
    }
}

// 두 정수의 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 퀵소트의 파티션을 수행하는 함수
int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
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

// 퀵소트를 구현하는 함수
void QuickSort(int *array, int low, int high) {
    if(low < high) {
        int pivtIndex = partition(array, low, high);
        QuickSort(array, low, pivtIndex - 1);
        QuickSort(array, pivtIndex + 1, high);
    }
}

// 이진 탐색을 수행하여 비교 횟수를 반환하는 함수
int binarySearch(int *array, int target) {
    int left = 0, right = arrSize - 1;
    int compareCount = 0;
    
    while(left <= right) {
        compareCount++;
        int mid = (left + right) / 2;
        if(array[mid] == target) return compareCount;
        if(array[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return compareCount;
}

// 보간 탐색을 수행하여 비교 횟수를 반환하는 함수
int interpolationSearch(int *array, int target) {
    int low = 0, high = arrSize - 1;
    int compareCount = 0;
    
    while(low <= high && target >= array[low] && target <= array[high]) {
        //compareCount++;
        int pos = low + ((target - array[low]) * (high - low)) / 
                       (array[high] - array[low]); 

        compareCount++;
        if(array[pos] == target) return compareCount;
        

        compareCount++;
        if(array[pos] < target) low = pos + 1;


        else high = pos - 1;
    }
    return compareCount;
}

// 이진 탐색의 평균 비교 횟수를 계산하는 함수
float getAverageBinarySearchCompareCount(int *array) {
    int totalCompares = 0;
    for(int i = 0; i < arrSize; i++) {
        int target = array[rand() % arrSize];
        totalCompares += binarySearch(array, target);
    }
    return (float)totalCompares / arrSize;
}

// 보간 탐색의 평균 비교 횟수를 계산하는 함수
float getAverageInterpolationSearchCompareCount(int *array) {
    int totalCompares = 0;
    for(int i = 0; i < arrSize; i++) {
        int target = array[rand() % arrSize];
        totalCompares += interpolationSearch(array, target);
    }
    return (float)totalCompares / arrSize;
}



int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[arrSize];
    generateRandomArray(array);


    QuickSort(array, 0, arrSize-1);
    printArray(array);

    printf("Average Compare Count of Binary Search: %.2f\n",
    getAverageBinarySearchCompareCount(array));

    printf("Average Compare Count of Interpolation Search: %.2f\n",
    getAverageInterpolationSearchCompareCount(array));
    return 0;
}