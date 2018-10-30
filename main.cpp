#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iterator>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <list>
#include "despachante.cpp"
#include "ThreadClass.cpp"
#include "RankingLista.cpp"

list<string> filenames;
list<string>::iterator iteracito;
Ranking r;
using namespace std;

void operaria(string file_name)
{
    string str;
    ifstream file;
    string path = "./fileset/";
    path += file_name;
    string word = "Bacon";
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
        //cout << "Excess�o ocorrida" << e << '\n';
    }
    cout << "Achei " << word << ": " << count << " ocorrencias no arquivo " << file_name << endl;
    r.inserir(file_name, count);
}

void despachante()
{
    Despachante dsp;
    while (true)
    {
        ThreadClass newThread;
        list<string> listaArquivos = dsp.executarLeitura("./fileset");
        if (!listaArquivos.empty())
        {
            list<string>::iterator it;
            for (it = listaArquivos.begin(); it != listaArquivos.end(); ++it)
            {
                while (newThread.numberOfThread > 9)
                {
                    cout << "Operarias Ocupadas" << endl;
                    this_thread::sleep_for(chrono::seconds(5));
                }
                newThread.executar(operaria, *it);
                cout << "OPERARIAS: " << newThread.numberOfThread << endl;
            }
        }
        else
            cout << "Nenhum arquivo novo" << endl;
        this_thread::sleep_for(chrono::seconds(5));
    }
}

void ranking()
{
    while (true)
    {
        r.ordenar();
        system("clear");
        r.exibir();
        this_thread::sleep_for(chrono::seconds(5));
    }
}

int main()
{

    vector<thread> threadsPrincipais;

    threadsPrincipais.push_back(thread(despachante));
    threadsPrincipais.push_back(thread(ranking));
    for (thread &t : threadsPrincipais)
    {
        t.join();
    }

    return 0;
}