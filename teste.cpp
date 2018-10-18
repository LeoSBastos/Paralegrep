#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <thread>
#include "arvore.h"
#include <unistd.h>

Dados d;

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
    std::cout << d.filename < << d.ocorrences << std::endl;
}

void ranking()
{
    int count;
    std::string filename;
    btree *tree = new btree;
    for (int i = 0; i < 10; i++)
    {
        filename = "fodase";
        cout << "Digite um numero: ";
        std::cin >> count;
        tree->insert(count, filename);
    }
    tree->inorder_print();
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