#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class ThreadsClass
{
public:
	void executaThread(int texto)
	{
		thr.push_back(thread(&ThreadsClass::teste, this, texto));
		for (thread &t : thr) t.join();
	}

private:
	void teste(int a) {
		cout << a << endl;
	}
	vector<thread> thr;
};


int main()
{
	ThreadsClass tes[10];

	for (int i = 0; i < 10; i++) {
		tes[i].executaThread(i + 1);
	}


	return 0;
}
