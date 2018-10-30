#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Celula
{
    string nomeArquivo;
    int ocorrencias;
};

class Ranking
{
  public:
    list<Celula> listaRanking;

    void inserir(string nomeArquivo, int ocorrencias)
    {
        bool alterado = false;
        list<Celula>::iterator it;
        it = listaRanking.begin();
        while (it != listaRanking.end())
        {
            if ((*it).nomeArquivo != nomeArquivo)
            {
                ++it;
            }
            else
            {
                (*it).ocorrencias = ocorrencias;
                ++it;
                alterado = true;
            }
        }
        if (!alterado)
        {
            Celula tempCell;
            tempCell.nomeArquivo = nomeArquivo;
            tempCell.ocorrencias = ocorrencias;
            listaRanking.push_back(tempCell);
        }
    }
    void modificar(string filename, int ocorre)
    {
        for (Celula c : listaRanking)
        {
            if (c.nomeArquivo == filename)
            {
                c.ocorrencias = ocorre;
            }
        }
    }
    void exibir()
    {
        int cont = 0;
        for (Celula c : listaRanking)
        {
            if (cont < 10)
            {
                cout << c.nomeArquivo << " - " << c.ocorrencias << endl;
                cont++;
            }
            else
            {
                return;
            }
        }
    }
    static bool comparar(const Celula &a, const Celula &b)
    {
        return a.ocorrencias > b.ocorrencias;
    }
    void ordenar()
    {
        listaRanking.sort(comparar);
    }
};