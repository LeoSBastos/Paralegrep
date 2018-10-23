#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iterator>
#include <thread>
#include <unistd.h>
#include <chrono>
#include "ranking.cpp"
#include "despachante.h"
#include "ThreadsClass.h"

Dados d;
list<string> filenames;
list<string> ::iterator iteracito;
ThreadsClass tc;
btree *tree = new btree;

//void despachante() {
//	Despachante despacito;
//	while (1) {
//		list<string> listaArquivos = despacito.executarLeitura("./fileset");
//		if (!listaArquivos.empty()) {
//			filenames = listaArquivos;
//			iteracito = filenames.begin();
//			while (iteracito != filenames.end()) {
//				tc.executaThread(*iteracito);
//			}
//		}
//		else cout << "Nenhum arquivo novo" << endl;
//		std::this_thread::sleep_for(5s);
//	}
//}

void operaria(std::string file_name)
{
	std::string str;
	std::ifstream file;
	std::string path = "./fileset/";
	path += file_name;
	std::string word = "foda";
	int count = 0;

	try
	{
		file.open(path.c_str());

		while (file >> str)
		{
			if (str.find(word) != std::string::npos)
				++count;
		}

		file.close();
	}
	catch (std::ifstream::failure e)
	{
		//cout << "Excessão ocorrida" << e << '\n';
	}
	std::cout << "Occurrences of " << word << ": " << count << std::endl;
	d.filename = file_name;
	d.ocorrences = count;
	tree->lista_atual.push_back(d);
}

void ranking()
{
	while (true) {
		if (tree->listaDiferente(tree->lista_atual, tree->lista_temp)) {
			string filename = d.filename;
			int count = d.ocorrences;
			tree->insert(count, filename);
			tree->inorder_print();
		}
		std::this_thread::sleep_for(5s);
	}
}
//===============================================
int main()
{

	std::string file_name;
	file_name = "teste.txt";
	std::thread t1(operaria, file_name);
	t1.join();
	std::thread t2(ranking);
	t2.join();
	return 0;
}