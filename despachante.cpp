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
//using namespace std::this_thread;
//using namespace std::chrono_literals;
//using std::chrono::system_clock;

struct Arquivo {
	string nomeArquivo;
	string data;
};


class Despachante {

public:
	list <string> filenames;
	list<Arquivo> lista_atual, lista_temp;
	int primeiraExecucao = 1;
	void showlistString(list <string> g)
	{
		list <string> ::iterator it;
		for (it = g.begin(); it != g.end(); ++it)
			cout << *it << endl;
	}
	int listaDiferente(list <Arquivo> g, list <Arquivo> h)
	{
		list <Arquivo> ::iterator it;
		list <Arquivo> ::iterator it2;
		for (it = g.begin(), it2 = h.begin(); it != g.end(), it2 != h.end(); ++it, ++it2) {
			if (((*it).nomeArquivo != (*it2).nomeArquivo)) {
				return 1;

				// || ((*it).data != (*it2).data)
			}
		}
		return 0;
	}
	list<string> listaArquivosNovos(list <Arquivo> g, list <Arquivo> h)
	{
		list <Arquivo> ::iterator it;
		list <Arquivo> ::iterator it2;

		it = g.begin();
		it2 = h.begin();
		while (it2 != h.end()) {
			if (((*it).nomeArquivo == (*it2).nomeArquivo)) {
				++it;
				++it2;
			}
			else {
				filenames.push_back((*it2).nomeArquivo);
				++it2;
			}
		}
		return filenames;
	}
	list<Arquivo> lerDiretorio(string locacao) {
		int cont = 0;
		list<Arquivo> lista;
		struct dirent *ent;
		const char* diretorio = locacao.c_str();
		DIR *dir;
		if ((dir = opendir(diretorio)) != NULL) {
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
	list<string> executarLeitura(string locacao) {
		filenames.clear();
		lista_atual = lerDiretorio(locacao);
		if (primeiraExecucao) {
			lista_temp = lista_atual;
			list<Arquivo> ::iterator temp;
			temp = lista_temp.begin();
			while (temp != lista_temp.end()) {
				filenames.push_back((*temp).nomeArquivo);
				++temp;
			}
			primeiraExecucao = 0;
			return filenames;
		}
		else if (listaDiferente(lista_atual, lista_temp)) {
			listaArquivosNovos(lista_temp, lista_atual);
			lista_temp = lista_atual;
			return filenames;
		}
		else {
			return filenames;
		}
	}

};

