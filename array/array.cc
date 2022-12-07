

#define MAXSIZE 10
#define LISTINCREMENT 10

struct Array {
    int *value;
    int size;
    int capacity;
    int listincrement;
};


void insert(Array *arr, int e)
{
    if(arr->size == arr->capacity) {
        // 申请内存
        arr->capacity += arr->listincrement;
    }

    arr->value = &e;
    ++arr->size;
}
