#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct trie_node_s trie_node_t;
typedef struct trie_node_s trie_tree_t;

struct trie_node_s {
    trie_node_t *next[26];
    bool exist;
};

static trie_node_t * create_trie_node();
int trie_insert(trie_tree_t *tree, const char *word);
int trie_search(trie_tree_t *tree, const char *word);
void destory_trie_tree(trie_tree_t *tree);


static trie_node_t * create_trie_node() {
    trie_node_t *n;

    n = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (n == NULL) {
        return NULL;
    }

    n->exist = false;
    memset(n->next, 0, sizeof(n->next));

    return n;
}

int trie_insert(trie_tree_t *t, const char *word) {
    unsigned index;
    trie_node_t *node;
    char *p;

    if (word == NULL) {
        return -1;
    }

    node = t;
    p = word;
    while (*p) {
        index = *p - 97;
        if (node->next[index] == NULL) {
            node->next[index] = create_trie_node();
        }

        node = node->next[index];
        p++;
    }
    node->exist = true;

    return 0;
}

int trie_search(trie_tree_t *tree, const char *word) {
    unsigned index;
    trie_node_t *node;
    char *p;

    if (word == NULL) {
        return -1;
    }

    node = tree;
    p = word;
    while (*p) {
        index = *p - 97;
        if (node->next[index] == NULL) {
            return -1;
        }
        p++;

        node = node->next[index];
    }

    if (node->exist == true) {
        return 0;
    }

    return -1;
}


int main() {
    trie_tree_t *t = create_trie_node();

    char str[12] ;
	bool flag = false;
	while(gets(str)) {
		if(flag)
			printf("%d\n",trie_search(t, str));
		else
		{
			if(strlen(str) != 0)
			{
				trie_insert(t, str);
			}
			else
				flag = true;
		}
	}

    return 0;
}