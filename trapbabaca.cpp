#include <iostream>
#include <dirent.h>
#include <string>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include <time.h>

using namespace std;


struct Arquivo {
	string nomeArquivo;
	string data;
};


void showlist(list <Arquivo> g)
{
	list <Arquivo> ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << (*it).nomeArquivo << " - " << (*it).data << endl;
}

int listaDiferente(list <Arquivo> g, list <Arquivo> h)
{
	list <Arquivo> ::iterator it;
	list <Arquivo> ::iterator it2;
	for (it = g.begin(), it2 = h.begin(); it != g.end(), it2 != h.end(); ++it, ++it2) {
		if (((*it).nomeArquivo != (*it2).nomeArquivo)) {
			cout << (*it).nomeArquivo << " - " << (*it).data << endl;
			cout << (*it2).nomeArquivo << " - " << (*it2).data << endl;
			return 1;

			// || ((*it).data != (*it2).data)
		}
	}
	return 0;
}

list<Arquivo> lerDiretorio(char* diretorio) {

	int cont = 0;
	list<Arquivo> lista;
	struct dirent *ent;
	DIR *dir;

	if ((dir = opendir("teste")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (!(cont < 2)) {
				Arquivo arq;
				struct stat attr;
				stat(ent->d_name, &attr);
				arq.nomeArquivo = ent->d_name;
				arq.data = ctime(&attr.st_mtime);
				lista.push_back(arq);
			}
			else {
				cont++;
			}
		}
		closedir(dir);
	}
	else {
		perror("");
		return lista;
	}
	return lista;
}



int main()
{
	int primeiraExecucao = 1;
	list<Arquivo> lista_atual, lista_temp;
	while (1) {
		lista_atual = lerDiretorio("teste");

		if (primeiraExecucao) {
			lista_temp = lista_atual;
			showlist(lista_temp);
			primeiraExecucao = 0;
		}

		if ((!primeiraExecucao) && listaDiferente(lista_atual, lista_temp)) {
			cout << "Opa arquivo novo!" << endl;
			lista_temp = lista_atual;
			showlist(lista_temp);
		}
	}

	return 0;
}
