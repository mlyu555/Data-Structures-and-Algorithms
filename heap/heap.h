#ifndef HEAP_H
#define HEAP_H

static void shiftup(minheap *heap, int i);
static void shiftup_rc(minheap *heap, int i);

struct minheap {
    int capacity;
    int size;
    int *data;
};

static swap(int *arr, int x, int y) {
    int tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
}


static void shiftup(minheap *heap, int i) {
    int parent = (i - 1) / 2;

    while (parent >= 0 ) {
        if ( heap->data[i] < heap->data[parent]) {
            swap(heap->data, i, parent);
        }
        i = parent;
    }
}


#endif //HEAP_H