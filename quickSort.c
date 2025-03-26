#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void test_quicksort() {
    int sizes[] = {100, 1000, 5000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int *arr = (int *)malloc(size * sizeof(int));

        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 10000;
        }

        clock_t start = clock();
        quicksort(arr, 0, size - 1);
        clock_t end = clock();

        printf("Tamanho: %d - Tempo: %f segundos\n", size, ((double)(end - start)) / CLOCKS_PER_SEC);

        free(arr);
    }
}

int main() {
    srand(time(NULL));
    test_quicksort();
    return 0;
}
