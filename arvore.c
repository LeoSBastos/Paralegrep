#include <stdlib.h>
#include <stdio.h>

struct bin_tree
{
    int data;
    char *fileName;
    struct bin_tree *right, *left;
};
typedef struct bin_tree node;

struct data
{
    int data;
    char *filename;
};
typedef struct data Data;

Data criaDados(int val, char *filename)
{
    Data d;
    d.data = val;
    d.filename = filename;
    return d;
}

void insert(node **tree, Data d)
{
    node *temp = NULL;
    if (!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = d.data;
        temp->fileName = d.filename;
        *tree = temp;
        return;
    }

    if (d.data < (*tree)->data)
    {
        insert(&(*tree)->left, d);
    }
    else if (d.data > (*tree)->data)
    {
        insert(&(*tree)->right, d);
    }
}

void print_inorder(node *tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%s => %d\n", tree->fileName, tree->data);
        print_inorder(tree->right);
    }
}