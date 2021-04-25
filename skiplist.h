#ifndef SKIP_LIST_H
#define SKIP_LIST_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SKIPLIST_P          0.25
#define SKIPLIST_MAX_LEVEL  32
typedef int sl_key_t;
typedef int sl_value_t;
#define SKIPLIST_NIL_NODE   NULL

// typedef struct skiplist_node_s {
//     int key;
//     void * value;
//     skiplist_node_t *backward;
//     struct skiplist_level {
//         struct skiplist_level *fordward;
//     } level[];
//     // int maxlevel;    // 当前节点最大层数
//         /*柔性数组,根据该节点层数的不同指向大小不同的数组
// 14
//      *next[0]表示该节点的第一层下一节点的索引地址
// 15
//      *next[1]表示该节点的第二层下一节点的索引地址
// 16
//      *next[n]表示该节点的第n层下一节点的索引地址
// 17
//      */
//     // struct  skiplist_node_s *next[];
// }skiplist_node_t;


// typedef struct skiplist_s {
//     skiplist_node_t *head;
//     skiplist_node_t *tail;
//     int length;
//     int level;
// } skiplist_t;

// 给n层的节点分配内存
// skiplist_node_t内存 + n个指针skiplist_node_t*
#define MALLOC_SKIPLIST_NODE(n) (skiplist_node_t*)malloc(sizeof(skiplist_node_t) + n * sizeof(skiplist_node_t *))


typedef struct skiplist_node_s {
    sl_key_t key;                  
    sl_value_t value;
    struct skiplist_node_s *next[1];       // 柔性数组，实现结构体变长
}skiplist_node_t;


typedef struct skiplist_s{
    int maxlevel;                   // 最大层数
    skiplist_node_t *head;          // 指向头节点
}skiplist_t;



static skiplist_node_t *skiplist_create_node(int level, sl_key_t key, sl_value_t value) {
    skiplist_node_t *node;
    node = MALLOC_SKIPLIST_NODE(level);
    if (!node) {
        return NULL;
    }

    node->key = key;
    node->value = value;

    // ??? node->next = ？？？
    return node;
}

static int randomlevel() {
    srand(time(0));             // 设置随机数种子
    int level = 1;
    while (rand() % 2) {        // 根据奇偶性仅0.5
        level++;
    }
    return level < SKIPLIST_MAX_LEVEL? level : SKIPLIST_MAX_LEVEL;
}

extern skiplist_t * skiplist_create(void) {
    skiplist_t *sl;
    sl = (skiplist_t *)malloc(sizeof(skiplist_t));
    if (sl == NULL) {
        return NULL;
    }

    sl->maxlevel = 0;          // 初始化值为0层，数组从0开始
    skiplist_node_t *head = skiplist_create_node(SKIPLIST_MAX_LEVEL-1, 0, 0);
    if (head == NULL) {
        free(sl);
        return NULL;
    }

    sl->head = head;
    int i = 0;
    for(; i < SKIPLIST_MAX_LEVEL; i++) {
        head->next[i] = SKIPLIST_NIL_NODE;
    }

    return sl;
}


/* 插入步骤
1. 确定待插入位置即查询操作
2. 每层更新update数组
3. 随机产生层数
4. 从上到下插入，即链表插入
*/
extern int skiplist_insert(skiplist_t *sl, sl_key_t key, sl_value_t value) {
    if (sl == NULL) {
        return -1;              // 跳表不存在
    }

    skiplist_node_t *update[SKIPLIST_MAX_LEVEL];            // 待更新的节点的指针
    skiplist_node_t *move;
    skiplist_node_t *curr = sl->head;
    skiplist_node_t *new_node;


    int i = sl->maxlevel - 1;
    for (; i >= 0; i--) {
        move = curr->next[i];
        while ( move && move->key < key) {
            curr = move;
            move = curr->next[i];
        }
        update[i] = curr;
    }

    if (move && move->key == key) {
        move->value = value;
        return 1;
    }

    int level = randomlevel();
    if (level > sl->maxlevel) {
        for (i = sl->maxlevel; i < level; i++) {
            update[i] = sl->head;
        }
        sl->maxlevel = level;
    }

    new_node = skiplist_create_node(level, key, value);
    if (curr == NULL) {
        return -2;
    }

    for(i = level - 1; i >= 0; i--) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }

    return 0;
}


/* 删除步骤
1. 确定待删除位置即查询操作
2. 每层更新update数组
3. 随机产生层数
4. 从上到下插入，即链表插入
*/
extern int skiplist_delete(skiplist_t *sl, sl_key_t key) {
    skiplist_node_t *update[SKIPLIST_MAX_LEVEL];
    skiplist_node_t *move;
    skiplist_node_t *prev = sl->head;
    int i;

    for (i = sl->maxlevel - 1; i >= 0; i++) {
        move = prev->next[i];
        while (move && move->key < key) {
            move = prev->next[i];
            move = prev;
        }
        update[i] = prev;
    }

    if (!move || (move && move->key != key)) {
        return -1;
    }

    for (i = sl->maxlevel - 1; i >= 0; --i) {
        if (update[i]->next[i] == move) {
            update[i]->next[i] = move->next[i];
            if (sl->head->next[i] == NULL) {
                sl->maxlevel--;
            }
        }
    }

    free(move);
    move = NULL;

    return 0;
}

extern int skiplist_modify(skiplist_t *sl, sl_key_t key, sl_value_t value) {
    return 0;
    
}

extern int skiplist_search(skiplist_t *sl, sl_key_t key, sl_value_t *value) {
    skiplist_node_t *node;
    skiplist_node_t *L0 = sl->head;
    int i;
    for (i = sl->maxlevel - 1; i >=0 ; i++) {
        node = L0->next[i];
        while (node && node->key < key) {
            L0 = node;
            node = L0->next[i];
        }
        if (node && node->key == key) {
            value = &node->value;
            return 0;
        }
    }

    return -1;
}


extern int skiplist_destory(skiplist_t *sl){
    if (sl == NULL) {
        return 0;
    }

    skiplist_node_t *L0 = sl->head;
    skiplist_node_t *m;
    if (L0 != NULL) {
        m = m->next[0];
        free(L0);
        L0 = m;
    }

    free(sl);
    return 0;
}


void print_sl(skiplist_t *sl)
{
    skiplist_node_t *q;
    int i = sl->maxlevel-1;
    for(; i>=0; --i)
    {
        q=sl->head->next[i];
        printf("level %d:\n", i+1);
		while(q)
        {
            printf("key:%d val:%d\t", q->key, q->value);
            q=q->next[i];
        }
        printf("\n");
    }
}

void test() {
    skiplist_t *sl=skiplist_create();
	int i=1;
	for(;i<11111; ++i)
	{
		skiplist_insert(sl, i, i);
	}
	for(i=11; i<11111; ++i)
	{
		if(skiplist_delete(sl, i) != 0){
            printf("No!\n");
        }
	}
	print_sl(sl);
    int *p;
	skiplist_search(sl, 10, p);
	if(p){
        printf("value of key 10 is %d\n", *p);
    }

	skiplist_destory(sl);
}

#endif  //SKIP_LIST_H