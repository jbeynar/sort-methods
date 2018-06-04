#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int *array, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
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

void selectionSort(int *array, int n) {
    int minIndex;
    for (int i = 0; i < n; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        if (i != minIndex) {
            swap(&array[minIndex], &array[i]);
        }
    }
}

int partition(int *array, int left, int right) {
    int pivot = array[right];
    int i = (left - 1);
    int j = left;
    for (j = left; j <= right - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[right]);
    return (i + 1);
}

void quickSort(int *array, int left, int right) {
    if (left < right) {
        int pivot;
        pivot = partition(array, left, right);
        quickSort(array, left, pivot - 1);
        quickSort(array, pivot + 1, right);
    }
}

int main() {
    int data[] = {4, 1, 89, 45, 2, 8, 10, 41, 4, 9, 10};
    int n = sizeof(data) / sizeof(data[0]);
//    bubbleSort(data, n);
//    insertionSort(data, n);
//    selectionSort(data, n);
    quickSort(data, 0, n - 1);

    printf("\n\n");
    for (int i = 0; i < n; i++) {
        printf("%d, ", data[i]);
    }
    return 0;
}