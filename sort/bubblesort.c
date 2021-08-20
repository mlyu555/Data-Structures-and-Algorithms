#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int BubbleSort(int arr[], int length) {
    for(int i = length - 1; i > 0; i--) {
        for(int j = 0; j < i; j++) {
            if ( arr[j] < arr[j+1]) {
                swap(arr, j, j+1);
            }
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
    BubbleSort(arr, 10);
    print(arr, 10);
}