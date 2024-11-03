#ifndef CODE_
#define CODE_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define bits_na_chave 5

typedef struct node {
    int bit;
    unsigned key;
    struct node *left;
    struct node *right;
} NODE;

void start(NODE **root);
unsigned bit(unsigned chave, int k);

void case1(NODE *tree, NODE *dad);
void case2(NODE *tree);
NODE *search_dad(NODE *tree, NODE *child);
NODE *search_special_child(NODE *tree, NODE *dad);
NODE *adoptChild(NODE *newParent, NODE *oldParent, NODE *child);
void freeTree(NODE *tree);

NODE *search_rec(NODE *tree, unsigned key, int level);
NODE *insert_rec(NODE *tree, unsigned key, int level, NODE *dad);
void print_node(NODE *tree, int size);

NODE *search(NODE *tree, unsigned key);
void insert(NODE **root, unsigned key);
void delete(NODE **root, unsigned key);
void print(NODE *tree, int size);

#endif