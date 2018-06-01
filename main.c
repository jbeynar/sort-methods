#include <stdio.h>


void bubbleSort(int *array, int n) {
    int tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                tmp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tmp;
            }
        }
    }
}

void insertionSort(int *array, int n) {
    int X;
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        X = array[i];
        while (j >= 0 && X < array[j]) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = X;
    }
}

int main() {
    int data[] = {4, 1, 89, 45, 2, 8, 10, 41, 4, 9, 10};
    int n = sizeof(data) / sizeof(data[0]);
//    bubbleSort(data, n);
    insertionSort(data, n);

    for (int i = 0; i < n; i++) {
        printf("%d, ", data[i]);
    }
    return 0;
}