typedef struct ListNode {
    int data;
    ListNode *next;
}SingleList, LoopList;

typedef struct ListNode {
    int data;
    ListNode *prev;
    ListNode *next;
}DoubleList;

namespace interview{

// 1. 删除单链表中指针p指向的结点
void delete_by_ptr(ListNode *head, ListNode *p);

// 2. 按值有序的单链表中插入结点
void insert_order(ListNode *head, int e);

// 3. 销毁一个单链表
void destory(ListNode *head);

// 4. 将两个有序的单链表进行归并(不能开辟额外内存空间)
void merge(ListNode *l1, ListNode *l2);

// 5. 单链表逆置反序
void reverse(ListNode *head);

// 6. 获取单链表倒数第k个元素
ListNode* findlast(ListNode *head, int k);

// 7. 创建循环链表


// 8. 约瑟夫环问题



};

