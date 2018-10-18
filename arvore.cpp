#include <iostream>
#include <string>

using namespace std;

struct node
{
    int value;
    string filename;
    node *left;
    node *right;
};

struct Dados
{
    int ocorrences;
    string filename;
};

class btree
{
  public:
    btree();

    void insert(int key, string filename);
    void inorder_print();

  private:
    void insert(int key, string filename, node *leaf);
    void inorder_print(node *leaf);
    node *root;
};

btree::btree()
{
    root = NULL;
}

void btree::insert(int key, string filename, node *leaf)
{

    if (key > leaf->value)
    {
        if (leaf->left != NULL)
        {
            insert(key, filename, leaf->left);
        }
        else
        {
            leaf->left = new node;
            leaf->left->value = key;
            leaf->left->filename = filename;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }
    else if (key <= leaf->value)
    {
        if (leaf->right != NULL)
        {
            insert(key, filename, leaf->right);
        }
        else
        {
            leaf->right = new node;
            leaf->right->value = key;
            leaf->right->right = NULL;
            leaf->right->left = NULL;
        }
    }
}

void btree::insert(int key, string filename)
{
    if (root != NULL)
    {
        insert(key, filename, root);
    }
    else
    {
        root = new node;
        root->value = key;
        root->filename = filename;
        root->left = NULL;
        root->right = NULL;
    }
}

void btree::inorder_print()
{
    inorder_print(root);
    cout << "\n";
}

void btree::inorder_print(node *leaf)
{
    if (leaf != NULL)
    {
        inorder_print(leaf->left);
        cout << leaf->filename << "->" << leaf->value << endl;
        inorder_print(leaf->right);
    }
}
