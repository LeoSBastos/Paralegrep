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

btree::btree();

void btree::insert(int key, string filename, node *leaf);

void btree::insert(int key, string filename);

void btree::inorder_print();

void btree::inorder_print(node *leaf);