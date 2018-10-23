#include <iostream>
#include <dirent.h>
#include <string>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include <time.h>
#include <chrono>
#include <thread>


using namespace std;


struct Arquivo {
	string nomeArquivo;
	string data;
};


class Despachante {

public:
	list <string> filenames;
	void showlistArquivo(list <Arquivo> g);
	void showlistString(list <string> g);
	int listaDiferente(list <Arquivo> g, list <Arquivo> h);
	list<string> listaArquivosNovos(list <Arquivo> g, list <Arquivo> h);
	list<Arquivo> lerDiretorio(string locacao);
	list<string> executarLeitura(string loc);


};

