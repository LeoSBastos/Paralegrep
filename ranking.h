#include <iostream>
#include <string>
#include <list>

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
	list<Dados> lista_atual, lista_temp;
	btree();
	void insert(int key, string filename);
	void inorder_print();
	list<Dados> listaDadosNovos(list <Dados> g, list <Dados> h);
	list<Dados> lerLista(list <Dados> g, list <Dados> h);
	int lerListaDiferente(list <Dados> g, list <Dados> h);

private:
	void insert(int key, string filename, node *leaf);
	void inorder_print(node *leaf);
	node *root;
};