#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class ThreadsClass
{
public:
	void executaThread(string a)
	{
		thr.push_back(thread(&ThreadsClass::teste, this, texto));
		for (thread &t : thr) t.join();
	}

private:
	void teste(string a) {
		cout << a << endl;
	}
	vector<thread> thr;
};


