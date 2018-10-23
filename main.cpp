#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iterator>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <list>
#include "ranking.cpp"
#include "despachante.cpp"
#include "ThreadClass.cpp"

Dados d;
list<string> filenames;
list<string> ::iterator iteracito;
btree tree;


using namespace std;


void operaria(string file_name)
{
	string str;
	ifstream file;
	string path = "./fileset/";
	path += file_name;
	string word = "teste";
	int count = 0;

	try
	{
		file.open(path.c_str());

		while (file >> str)
		{
			if (str.find(word) != string::npos)
				++count;
		}

		file.close();
	}
	catch (ifstream::failure e)
	{
		//cout << "Excessão ocorrida" << e << '\n';
	}
	cout << "Achei " << word << ": " << count << " ocorrencias no arquivo " << file_name << endl;
	d.filename = file_name;
	d.ocorrences = count;
	tree.lista_atual.push_back(d);
}

void despachante() {
	Despachante dsp;
	while (true) {
		int numberOfThreads = 0;

		list<string> listaArquivos = dsp.executarLeitura("./fileset");
		if (!listaArquivos.empty()) {

			//dsp.showlistString(listaArquivos);
			list <string> ::iterator it;
			for (it = listaArquivos.begin(); it != listaArquivos.end(); ++it) {
				while (numberOfThreads > 9) {
					cout << "Operarias Ocupadas" << endl;
					std::this_thread::sleep_for(std::chrono::seconds(5));
				}
				ThreadClass newThread;
				numberOfThreads++;
				numberOfThreads -= newThread.executar(operaria, *it);
				cout << "OPERARIAS: " << numberOfThreads << endl;
			}
		}
		else cout << "Nenhum arquivo novo" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

}

void ranking()
{
	while (true) {
		if (tree.lerListaDiferente(tree.lista_atual, tree.lista_temp)) {
			string filename = d.filename;
			int count = d.ocorrences;
			tree.insert(count, filename);
			tree.inorder_print();
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}
//===============================================
int main()
{

	/*string file_name;
	file_name = "arq.txt";
	thread t1(operaria, file_name);
	t1.join();
	thread t2(ranking);
	t2.join();*/


	thread despacha(despachante);
	despacha.join();

	return 0;
}