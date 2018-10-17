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

Data criaDados(int val, char *filename);
void insert(node **tree, Data d);
void print_inorder(node *tree);