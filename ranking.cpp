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
	list<Dados> lista_atual, lista_temp, lista_Dados;
	int primeiraExecucao = 1;
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
			leaf->right->filename = filename;
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
	int count = 0;
	if (leaf != NULL && count < 10)
	{
		inorder_print(leaf->left);
		cout << leaf->filename << "->" << leaf->value << endl;
		count++;
		inorder_print(leaf->right);
	}
}
list<Dados> btree::listaDadosNovos(list <Dados> g, list <Dados> h)
{
	list <Dados> ::iterator it;
	list <Dados> ::iterator it2;

	it = g.begin();
	it2 = h.begin();
	while (it2 != h.end()) {
		if ((*it).filename == (*it2).filename) {
			++it;
			++it2;
		}
		else {
			lista_Dados.push_back(*it2);
			++it2;
		}
	}
	return lista_Dados;
}
int btree::lerListaDiferente(list <Dados> g, list <Dados> h)
{
	list <Dados> ::iterator it;
	list <Dados> ::iterator it2;
	for (it = g.begin(), it2 = h.begin(); it != g.end() || it2 != h.end(); ++it, ++it2) {
		if ((*it).filename != (*it2).filename) {
			return 1;
		}
	}
	return 0;
}
list<Dados> btree::lerLista(list <Dados> g, list <Dados> h) {
	lista_Dados.clear();
	if (primeiraExecucao) {
		h = g;
		list<Dados> ::iterator temp;
		temp = lista_temp.begin();
		while (temp != lista_temp.end()) {
			lista_Dados.push_back(*temp);
			++temp;
		}
		return lista_Dados;
	}
	else if (lerListaDiferente(g, h)) {
		listaDadosNovos(lista_temp, lista_atual);
		lista_temp = lista_atual;
		return lista_Dados;
	}
	else return lista_Dados;
}
