#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int SelectSort(int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (min != i) {
            swap(arr, min, i);
        }
    }

    return 0;
}

void print(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}


int main() {
    int arr[] = {10, 2, 8, 29, 57, 19, 88, 58, 63, 77};
    print(arr, 10);
    SelectSort(arr, 10);
    print(arr, 10);
}