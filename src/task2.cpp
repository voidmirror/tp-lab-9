#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
bool flag = false;
bool canPrint = false;

template<typename S>
void bubleSort(vector<string> &vect, S cmpr)
{
	
	int sizeV = vect.size();
	for (int i = 0; i < sizeV - 1; i++)
	{
		mtx.lock();
		if (!canPrint) {
			for (int j = 0; j < sizeV - 1; j++)
			{
				if (cmpr(vect[j], vect[j + 1]))
					swap(vect[j], vect[j + 1]);
			}
			canPrint = true;
		}
		mtx.unlock();
	}
	flag = true;
	
}

void printArr(vector<string> &vect)
{
	for (auto elem : vect)
	{
		cout << elem << " ";
	}
	cout << endl;
}

int main()
{
	vector<string> test = { "qweq","FDSERe","test","Vectoraaa","aab","word" };
	thread th(bubleSort<bool(*)(const string&, const string&)>, ref(test), [](const string &a, const string &b) {
		return a > b;
	});
	while (!flag)
	{
		if (canPrint)
		{
			mtx.lock();
			printArr(test);
			canPrint=false;
			mtx.unlock();

		}
	}
	th.join();
	return 0;
}