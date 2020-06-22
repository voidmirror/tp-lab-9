#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename S>
void bubleSort(vector<string> &vect, S cmpr)
{
	int sizeV = vect.size();
	for (int i = 0; i < sizeV - 1; i++)
	{
		for (int j = 0; j < sizeV - 1; j++)
		{
			if (cmpr(vect[j], vect[j + 1]))
				swap(vect[j], vect[j + 1]);
		}
	}
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
	setlocale(LC_ALL, "ru");
	vector<string> test = { "qweq","FDSERe","test","Vectoraaa","aab","word" };
	bubleSort(test, [](string &a, string &b) {
		return a > b;
	});
	cout << "Алфавитный порядок:" << endl;
	printArr(test);

	bubleSort(test, [](string &a, string &b) {
		return a < b;
	});
	cout << "Обратный порядок:" << endl;
	printArr(test);

	bubleSort(test, [](string &a, string &b) {
		return a.size() > b.size();
	});
	cout << "По длине - от меньшего к большему:" << endl;
	printArr(test);

	bubleSort(test, [](string &a, string &b) {
		return a.size() < b.size();
	});
	cout << "По длине - от большего к меньшему:" << endl;
	printArr(test);

	bubleSort(test, [](string &a, string &b) {
		return a[0] > b[0];
	});
	cout << "По первой букве:" << endl;
	printArr(test);

	return 0;
}