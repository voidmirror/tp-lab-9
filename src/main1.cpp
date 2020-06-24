// main1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void mySort(vector<string> &mas, bool func(string a, string b))
{
	for (int i = 0; i < mas.size();i++)
	{
		for (int j = i+1; j < mas.size(); j++)
		{
			if (func(mas[i], mas[j]))
				swap(mas[i], mas[j]);
		}

	}
}


int main()
{
	vector<string> mas = {"cat","dog","mouse","rabbit","horse"};
	
	mySort(mas, [](string a, string b) {return a < b; });

	for (int i = 0; i < mas.size(); i++)
		cout << mas[i] << ' ';
	cout << endl;

	mySort(mas, [](string a, string b) {return a > b; });

	for (int i = 0; i < mas.size(); i++)
		cout << mas[i] << ' ';
	cout << endl;

	mySort(mas, [](string a, string b) {return a[1] > b[1]; });

	for (int i = 0; i < mas.size(); i++)
		cout << mas[i] << ' ';
	cout << endl;

	mySort(mas, [](string a, string b) {return a[1] < b[1]; });

	for (int i = 0; i < mas.size(); i++)
		cout << mas[i] << ' ';
	cout << endl;

	mySort(mas, [](string a, string b) {return a.length() > b.length(); });

	for (int i = 0; i < mas.size(); i++)
		cout << mas[i] << ' ';
	cout << endl;

	mySort(mas, [](string a, string b) {return a.length() < b.length(); });
	for (int i = 0; i < mas.size(); i++)
		cout << mas[i] << ' ';

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
