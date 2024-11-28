#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define STACK_SIZE 1000

// 정렬 과정을 추적하기 위한 전역 변수들
int comparisonCount = 0;    // 비교 연산 횟수
int moveCount = 0;          // 이동 연산 횟수
int totalComparisons = 0;   // 전체 비교 횟수 합계
int totalMoveCount = 0;     // 전체 이동 횟수 합계
int isFirst = 0;           // 첫 번째 실행 여부 플래그
int rounds = 0;            // 정렬 라운드 카운터

// 스택 구조체 정의 (반복적 퀵정렬 구현을 위함)
struct Stack {
    int top;               // 스택의 top 위치
    int items[STACK_SIZE][2];  // 정렬 범위를 저장하는 2차원 배열 [left, right]
};

// 랜덤 배열 생성 함수
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;  // 0~999 사이의 랜덤 값 생성
    }
}

// 배열 출력 함수
void printArray(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 두 원소의 위치를 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    moveCount += 3;  // 교환 연산은 3번의 이동을 포함
}

// 퀵정렬의 파티션 함수
int partition(int list[], int left, int right) {
    // 피벗을 선택합니다.
    int pivot = list[left];
    // 초기 위치를 설정합니다.
    int low = left + 1;
    int high = right;
    
    // low와 high가 교차할 때까지 반복합니다.
    while(low <= high) {
        // low부터 시작하여 피벗보다 작은 원소를 찾습니다.
        while(low <= high && list[low] <= pivot) {
            comparisonCount++;
            low++;
        }
        
        // high부터 시작하여 피벗보다 큰 원소를 찾습니다.
        while(high >= low && list[high] > pivot) {
            comparisonCount++;
            high--;
        }
        
        // low와 high가 교차하지 않았다면, 원소를 교환합니다.
        if (low < high ) {
            swap(&list[low], &list[high]);
        }
    }
    
    // 피벗과 high 위치의 원소를 교환합니다.
    if (left < high) {
        swap(&list[left], &list[high]);
    }
    
    // 파티션의 위치를 반환합니다.
    return high;
}

// 반복적 방식의 퀵정렬 구현
void doQuickSort(int list[], int left, int right) {
    struct Stack stack;
    stack.top = -1;        // 스택 초기화
    
    // 초기 정렬 범위를 스택에 푸시
    stack.top++;
    stack.items[stack.top][0] = left;
    stack.items[stack.top][1] = right;
    
    while (stack.top >= 0) {  // 스택이 비어있지 않은 동안 반복
        // 스택에서 정렬 범위를 팝
        left = stack.items[stack.top][0];
        right = stack.items[stack.top][1];
        stack.top--;
        
        if (left >= right) continue;  // 정렬 범위가 1 이하면 건너뜀
        
        int pivot_pos = partition(list, left, right);  // 파티션 수행
        
        // 첫 번째 실행 시 10라운드마다 중간 과정 출력 (인덱스 40-59)
        if(rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", list[i]);
            printf("\n\n");
        }
        rounds++;
        
        // 왼쪽 부분 배열을 스택에 푸시
        if (pivot_pos - 1 > left) {
            stack.top++;
            stack.items[stack.top][0] = left;
            stack.items[stack.top][1] = pivot_pos - 1;
        }
        
        // 오른쪽 부분 배열을 스택에 푸시
        if (pivot_pos + 1 < right) {
            stack.top++;
            stack.items[stack.top][0] = pivot_pos + 1;
            stack.items[stack.top][1] = right;
        }
    }
}

// 메인 함수
int main(int argc, char *argv[]) {
    srand(time(NULL));     // 난수 생성기 초기화
    int array[SIZE];
    
    // 20회 반복 실행하여 평균 성능 측정
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;
        
        // 첫 번째 실행시에만 결과를 출력
        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        } else {
            doQuickSort(array, 0, SIZE - 1);
        }
        
        // 통계 누적
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }
    
    // 평균 성능 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}