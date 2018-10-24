#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class ThreadClass
{
public:
	int numberOfThread = 0;
	void executar(void(*f)(string), string nomeArquivo)
	{
		thr.push_back(thread(&ThreadClass::thrExec, this, f, nomeArquivo));
		this->numberOfThread++;
		this->thrExecuteThreads();
	}

private:
	void thrExec(void(*f)(string), string nomeArquivo) {
		f(nomeArquivo);
	}
	void thrExecuteThreads(){
		for (thread &t : thr) {
			if(t.joinable()){
				t.join();
				this->numberOfThread--;
			}
		};
	}
	vector<thread> thr;
};


