#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum {
    SORT_BUBBLE,
    SORT_INSERTION,
    SORT_SELECTION,
    SORT_QUICKSORT
};

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

int getRandomNumber() {
    return (rand() % 200) - 100;
}

int *getRandomVector(int size) {
    int *vector = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        vector[i] = getRandomNumber();
    }
    return vector;
}

int *getAscendingVector(int size) {
    int *vector = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        vector[i] = i + 1;
    }
    return vector;
}

int *getDescendingVector(int size) {
    int *vector = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        vector[i] = size - i;
    }
    return vector;
}

double testSortMethod(int method, int *data, int n) {
    time_t timeStart, timeEnd;
    double delta;
    time(&timeStart);
    switch (method) {
        case SORT_BUBBLE:
            bubbleSort(data, n);
            break;
        case SORT_INSERTION:
            insertionSort(data, n);
            break;
        case SORT_SELECTION:
            selectionSort(data, n);
            break;
        case SORT_QUICKSORT:
            quickSort(data, 0, n - 1);
            break;
        default:
            printf("Unsported sort method");
    }
    time(&timeEnd);
    return difftime(timeEnd, timeStart);
}

void sortMethodsPerformanceTest(int method) {
    printf("Test %d sort method\n", method);
    char filename[100];
    sprintf(&filename, "%d_sort_results.csv", method);
    FILE *fp = fopen(filename, "w");
    int samplesSizes[] = {10000, 20000, 30000};
    int s = sizeof(samplesSizes) / sizeof(samplesSizes[0]);
    char *results = (char *) malloc(1000 * sizeof(char));
    double times[3] = {-1.0, -1.0, -1.0};
    char line[200];
    for (int i = 0; i < s; i++) {
        int N = samplesSizes[i];
        printf("Test for sample size %d\n", N);
        int *randomData = getRandomVector(N);
        int *ascData = getAscendingVector(N);
        int *descData = getDescendingVector(N);
        times[0] = testSortMethod(method, randomData, N);
        times[1] = testSortMethod(method, ascData, N);
        times[2] = testSortMethod(method, descData, N);
        sprintf(&line, "%d,%d,%f,%f,%f\n", method, N, times[0], times[1], times[2]);
        strcat(results, &line);
        free(randomData);
        free(ascData);
        free(descData);
    }
    fputs(results, fp);
    printf("Results were saved to file %s\n", filename);
    fclose(fp);
}

int main() {
    srand(4176199);
    sortMethodsPerformanceTest(SORT_BUBBLE);
    sortMethodsPerformanceTest(SORT_INSERTION);
    sortMethodsPerformanceTest(SORT_SELECTION);
    sortMethodsPerformanceTest(SORT_QUICKSORT);
    return 0;
}