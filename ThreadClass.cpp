#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class ThreadClass
{
public:
	int executar(void(*f)(string), string nomeArquivo)
	{
		thr.push_back(thread(&ThreadClass::thrExec, this, f, nomeArquivo));
		for (thread &t : thr) {
			t.join();
		};

		return 1;
	}

private:
	void thrExec(void(*f)(string), string nomeArquivo) {
		f(nomeArquivo);
	}
	vector<thread> thr;
};


