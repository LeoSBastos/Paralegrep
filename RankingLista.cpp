#include <iostream>
#include <string>
#include <list>
using namespace std;


struct Celula{
    string nomeArquivo;
    int ocorrencias;
};


class Ranking{
    
    
    public:
    list<Celula> listaRanking;
    void inserir(string nomeArquivo,int ocorrencias){
        Celula tempCell;
        tempCell.nomeArquivo = nomeArquivo;
        tempCell.ocorrencias = ocorrencias;
        listaRanking.push_back(tempCell);
    }
    void exibir(){
        int cont = 0;
        for(Celula c: listaRanking){
            if(cont < 3){
                cout << c.nomeArquivo << " - " << c.ocorrencias << endl;
                cont++;  
            }
        }
    }
    static bool comparar(const Celula &a,const Celula &b)
    {
        return a.ocorrencias > b.ocorrencias;
    }
    void ordenar(){
        listaRanking.sort(comparar);
    }
};
