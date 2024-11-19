#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 100

void generateRandomData(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

void print_list(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n\n");
}

void doSelectionSort(int list[]) {
    int i, j, min, temp;
    int step = 0;
    for (i = 0; i < SIZE - 1; i++) {
        min = i;
        for (j = i + 1; j < SIZE; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
        }
        SWAP(list[i], list[min], temp);
        step++;
        if (step % 10 == 0) {
            printf("Step %d: ", step);
            print_list(list);
        }
        if (step == 99) {
            printf("Step %d: ", step);
            print_list(list);
        }
    }
    printf("Selection Sort: ");
    print_list(list);
}


int insertion_average(){
    srand(time(NULL));
    int totalCompare = 0;
    for (int k = 0; k < 20; k++) {
        int compare = 0;
        int list[SIZE];
        generateRandomData(list);
        int i, j, key;
        for (i = 1; i < SIZE; i++) {
            key = list[i];
            for (j = i - 1; j >= 0 && list[j] > key; j--) {
                list[j + 1] = list[j];
                compare++;
            }
            list[j + 1] = key;
        }
        totalCompare += compare;
    }
    return (totalCompare / 20);
}

void doInsertionSort(int list[]) {
    int i, j, key;
    for (i = 1; i < SIZE; i++) {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
    }
    printf("Insertion Sort Compare Average: %d\n", insertion_average());
    printf("Insertion Sort: ");
    print_list(list);
}

int bubble_average(){
    srand(time(NULL));
    int totalMove = 0;
    for (int k = 0; k < 20; k++) {
        int move = 0;
        int list[SIZE];
        generateRandomData(list);
        int i, j, temp;
        for (i = SIZE - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (list[j] > list[j + 1]) {
                    SWAP(list[j], list[j + 1], temp);
                    move += 3;
                }
            }
        }
        totalMove += move;
    }
    return (totalMove / 20);
}

void doBubbleSort(int list[]) {
    int i, j, temp;
    for (i = SIZE - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
            }
        }
    }
    printf("Bubble Sort Move Average: %d\n", bubble_average());
    printf("Bubble Sort: ");
    print_list(list);
}

int main() {
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);
return 0;
}