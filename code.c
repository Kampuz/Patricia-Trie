#include "code.h"
#include <string.h>
#include <stdlib.h>

void start(NODE **root)
{
    *root = (NODE *)malloc(sizeof(NODE));
    (*root)->key = UINT_MAX;
    (*root)->left = *root;
    (*root)->right = *root;
    (*root)->bit = -1;
}

unsigned bit(unsigned chave, int k)
{
    return chave >> (bits_na_chave - 1 - k) & 1;
}

NODE *search_rec(NODE *tree, unsigned key, int level)
{
    if (tree->bit <= level)
    {
        return tree;
    }
    if (bit(key, tree->bit) == 0)
    {
        return search_rec(tree->left, key, tree->bit);
    }
    else
    {
        return search_rec(tree->right, key, tree->bit);
    }
}

NODE *search(NODE *tree, unsigned key)
{
    NODE *aux = search_rec(tree->left, key, -1);
    return aux->key == key ? aux : NULL;
}

NODE *insert_rec(NODE *tree, unsigned key, int level, NODE *dad)
{
    NODE *new;
    if ((tree->bit >= level) || (tree->bit <= dad->bit))
    {
        new = (NODE *)malloc(sizeof(NODE));
        new->key = key;
        new->bit = level;
        if (bit(key, new->bit) == 1)
        {
            new->left = tree;
            new->right = new;
        }
        else
        {
            new->left = new;
            new->right = tree;
        }
        return new;
    }

    if (bit(key, tree->bit) == 0)
    {
        tree->left = insert_rec(tree->left, key, level, tree);
    }
    else
    {
        tree->right = insert_rec(tree->right, key, level, tree);
    }

    return tree;
}

void insert(NODE **root, unsigned key)
{
    int i;

    NODE *aux = search_rec((*root)->left, key, -1);
    if (key == aux->key)
    {
        return;
    }

    for (i = 0; bit(key, i) == bit(aux->key, i); i++)
        ;
    (*root)->left = insert_rec((*root)->left, key, i, *root);
}

void delete(NODE **root, unsigned key)
{
    int i;

    NODE *target = search((*root)->left, key);

    if (target == NULL)
    {
        return;
    }

    if (key == target->key)
    {
        NODE *dad = search_dad((*root)->left, target);

        if ((target->left == target) || (target->right == target))
        {
            case1(target, dad);
        }
        else
        {
        }
    }
}

void case1(NODE *node, NODE *dad)
{
    if (node->left == node)
    {
        adoptChild(dad, node, node->right);
    }
    else if (node->right == node)
    {

        adoptChild(dad, node, node->left);
    }
}

void case2(NODE *tree)
{
    NODE *specialChild = search_special_child(tree, tree);
    NODE *specialGrandchild = search_special_child(specialChild, specialChild);

    tree->key = specialChild->key;

    if (specialGrandchild->left == specialChild)
    {
        specialGrandchild->left = tree;
    }
    else if (specialGrandchild->right == specialChild)
    {
        specialGrandchild->right = tree;
    }

    if (tree->left == specialChild)
    {
        if (specialChild->left == tree)
        {
            tree->left = specialChild->right;
        }
        else if (specialChild->right == tree)
        {
            tree->left = specialChild->left;
        }
    }
    else if (tree->right == specialChild)
    {
        if (specialChild->left == tree)
        {
            tree->right = specialChild->right;
        }
        else if (specialChild->right == tree)
        {
            tree->right = specialChild->left;
        }
    }
    free(specialChild);
}

NODE *search_dad(NODE *tree, NODE *child)
{
    if ((tree->left == child) || (tree->right == child))
    {
        return tree;
    }

    if (bit(child->key, tree->bit) == 0)
    {
        return search_dad(tree->left, child);
    }
    else
    {
        return search_dad(tree->right, child);
    }
}

NODE *search_special_child(NODE *tree, NODE *key)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if ((tree->left == key) || (tree->right == key))
    {
        return tree;
    }

    NODE *leftChild = search_special_child(tree->left, key);

    if (leftChild != NULL)
    {
        return leftChild;
    }

    NODE *rightChild = search_special_child(tree->right, key);

    if (rightChild != NULL)
    {
        return rightChild;
    }
}

NODE *adoptChild(NODE *newParent, NODE *oldParent, NODE *child)
{
    if (newParent->left == oldParent)
    {
        newParent->left = child;
    }
    else if (newParent->right == oldParent)
    {
        newParent->right = child;
    }

    free(oldParent);
    return;
}

void print_node(NODE *tree, int size)
{

    printf(" \n");
    if (tree->bit != -1)
    {
        for (int i = 0; i <= tree->bit; i++)
        {
            printf("     ");
        }
    }

    char buffer[size];
    itoa(tree->key, buffer, 2);

    char string[size];
    strcpy(string, "");

    int count = size;
    int modfier = strlen(buffer);
    while (count - modfier > 0)
    {
        strcat(string, '0');
        modfier++;
    }

    strcat(string, buffer);

    if (tree->bit == -1)
    {
        printf("Apple");
    }
    else
    {
        printf("Chave: %s | Bit: %d", string, tree->bit);
    }
}

void print(NODE *tree, int size)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->right->bit > tree->bit)
    {
        for (int i = 0; i <= tree->bit; i++)
        {
            printf("       ");
        }
        print(tree->right, size);
    }
    else
    {
        printf("\n");
    }

    print_node(tree, size);

    if (tree->left->bit > tree->bit)
    {
        for (int j = 0; j <= tree->bit; j++)
        {
            printf("        ");
        }
        print(tree->left, size);
    }
    else
    {
        printf("\n");
    }
}

void freeTree(NODE *tree)
{
    if (tree == NULL)
    {
        return;
    }

    if ((tree->left != tree) && (tree->left->bit > tree->bit))
    {
        freeTree(tree->left);
    }

    if ((tree->right != tree) && (tree->right->bit > tree->bit))
    {
        freeTree(tree->right);
    }

    free(tree);
}