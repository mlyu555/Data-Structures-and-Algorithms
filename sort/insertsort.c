#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// 从小到大
int InsertSort(int arr[], int length) {
    for (int i = 1; i < length; i++) {

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
    InsertSort(arr, 10);
    print(arr, 10);
}