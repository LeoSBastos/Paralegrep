#include <iostream>
#include <string>

using namespace std;

int main()
{
    string md5string = "md5sum ./fileset/beicu.txt";
    auto buscaSystem = system(md5string.c_str());
    cout << buscaSystem << endl;
    return 0;
}