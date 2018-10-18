#include <iostream>
#include <dirent.h>
#include <string>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include <time.h>

using namespace std;

struct Arquivo
{
    string nomeArquivo;
    string data;
};

void showlist(list<Arquivo> g)
{
    list<Arquivo>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout << (*it).nomeArquivo << " - " << (*it).data << endl;
}

int main()
{
    int cont = 0;
    DIR *dir;
    list<Arquivo> lista_atual, lista_temp;
    struct dirent *ent;
    if ((dir = opendir("tst")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (!(cont < 2))
            {
                Arquivo arq;
                struct stat attr;
                stat(ent->d_name, &attr);

                arq.nomeArquivo = ent->d_name;
                arq.data = ctime(&attr.st_mtime);
                lista_atual.push_back(arq);
            }
            else
            {
                cont++;
            }
        }
        closedir(dir);
    }
    else
    {
        perror("");
        return EXIT_FAILURE;
    }

    showlist(lista_atual);
    return 0;
}