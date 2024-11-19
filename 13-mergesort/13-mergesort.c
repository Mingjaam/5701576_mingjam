    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    #define SIZE 100
    int comparisonCount = 0;
    int moveCount = 0;
    int totalComparisons = 0;
    int totalMoves = 0;
    int isFirst = 0;
    int sortedArray[SIZE];
    int rounds = 0;


    // 랜덤 배열 생성 함수
    void generateRandomArray(int array[]) {
        srand(time(NULL));
        for (int i = 0; i < SIZE; i++) {
            array[i] = rand() % 1000;
        }
    }

    // 배열 출력 함수
    void printArray(int array[], int size) {
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    // 병합 하는 함수
    void merge(int array[], int left, int mid, int right) {
        int i = left, j = mid + 1, k = left;

        
        while (i <= mid && j <= right) {
            comparisonCount++;
            if (array[i] <= array[j]) {
                sortedArray[k++] = array[i++];
            } else {
                sortedArray[k++] = array[j++];
            }
            moveCount++;
        }

        while (i <= mid) {
            sortedArray[k++] = array[i++];
            moveCount++;
        }
        
        while (j <= right) {
            sortedArray[k++] = array[j++];
            moveCount++;
        }

        for (i = left; i <= right; i++) {
            array[i] = sortedArray[i];
            moveCount++;
        }

        rounds++;

        // 10번에 한번씩 정렬 과정 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            // 처음 10개 출력
            for (int i = 0; i < 10; i++) {
                printf("%3d ", array[i]);
            }
            printf("| ");
            // 중앙 주변 출력
            for (int i = SIZE/2 - 1; i < SIZE/2 + 10; i++) {
                printf("%3d ", array[i]);
            }
            printf("\n\n");
        }
    }
    // 재귀적인 방식의 병합 정렬 함수
    void doMergeSort(int array[], int left, int right) {
        // 왼쪽 인덱스가 오른쪽 인덱스보다 작을 때
        if (left < right) {
            int mid = (left + right) / 2;
            // 왼쪽 배열 정렬
            doMergeSort(array, left, mid);
            // 오른쪽 배열 정렬
            doMergeSort(array, mid + 1, right);
            // 병합
            merge(array, left, mid, right);
        }
    }

    // 반복적인 방식의 병합 정렬 함수
    void doMergeSort_iterative(int array[], int left, int right) {
        // 너비 초기화
        int width = 1;
        // 너비가 배열 크기보다 작을 때
        while (width < right - left + 1) {
            int leftPos = left;
            while (leftPos < right) {
                comparisonCount++;
                // 중앙 인덱스 초기화
                int mid = leftPos + width - 1;
                // 오른쪽 인덱스 초기화
                int rightPos = mid + width;
                // 오른쪽 인덱스가 배열 크기보다 크면 배열 크기로 설정
                if (rightPos > right) rightPos = right;
                // 비교 횟수 증가
                comparisonCount++;
                // 이동 횟수 증가
                moveCount++;
                // 병합
                merge(array, leftPos, mid, rightPos);
                // 왼쪽 인덱스 초기화
                leftPos = rightPos + 1;
            }
            // 너비 2배 증가
            width *= 2;
        }
        // 라운드 증가
        rounds++;
    }

    int main() {
        int array[SIZE];

        // 재귀적인 방식의 병합 정렬 실행 --------------------------------
        for (int i = 0; i < 20; i++) {
            generateRandomArray(array);
            comparisonCount = 0;
            moveCount = 0;

            if (i == 0) {
                printf("Recursive Merge Sort Run\n");
                doMergeSort(array, 0, SIZE - 1);

                printf("Result\n");
                printArray(array, SIZE);
                isFirst++;
            } else {
                doMergeSort(array, 0, SIZE - 1);
            }

            totalComparisons += comparisonCount;
            totalMoves += moveCount;
        }

        printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
        printf("Average Moves: %.2f\n", totalMoves / 20.0);

        totalComparisons = 0;
        totalMoves = 0;
        isFirst = 0;
        rounds = 0;


        // 반복적인 방식의 병합 정렬 실행 --------------------------------
        printf("\n\n");
        for (int i = 0; i < 20; i++) {
            generateRandomArray(array);
            comparisonCount = 0;
            moveCount = 0;

            if (i == 0) {
                printf("Iterative Merge Sort Run\n");
                doMergeSort_iterative(array, 0, SIZE - 1);

                printf("Result\n");
                printArray(array, SIZE);
                isFirst++;
            } else {
                doMergeSort_iterative(array, 0, SIZE - 1);
            }

            totalComparisons += comparisonCount;
            totalMoves += moveCount;
        }

        printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
        printf("Average Moves: %.2f\n", totalMoves / 20.0);

        return 0;
    }