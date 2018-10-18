#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <thread>

using namespace std;

void operaria(string file_name)
{
    string str;
    ifstream file;
    string path = "./fileset/";
    path += file_name;
    string word = "foda";
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
    catch (ifstream::failure e)
    {
        //cout << "Excessão ocorrida" << e << '\n';
    }
    cout << "Occurrences of " << word << ": " << count << endl;
}

//===============================================
int main()
{

    string file_name;
    file_name = "teste.txt";

    operaria(file_name);

    return 0;
}