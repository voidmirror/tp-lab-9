// main2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <functional>

using namespace std;

bool endProgram = false;
bool sortAccess=false;
bool mainAccess=true;
mutex mu;
condition_variable cv;



void mySort(vector<string>& mas, bool func(string a, string b))
{
	for (int i = 0; i < mas.size(); i++)
	{
		unique_lock<mutex> lk(mu);
		cv.wait(lk, [] {return (sortAccess); });

		for (int j = i + 1; j < mas.size(); j++)
		{
			if (func(mas[i], mas[j]))
				swap(mas[i], mas[j]);
		}
		sortAccess = false;
		mainAccess = true;

		lk.unlock();
		cv.notify_all();
	}

	endProgram = true;
}


int main()
{
	vector<string> mas = { "cat","dog","mouse","rabbit","horse" };

	thread func(mySort, ref(mas), [](string a, string b) { return a < b; });

	while(1)
	{
		unique_lock<mutex> lk(mu);
		cv.wait(lk, [] {return (mainAccess); });
		if (endProgram)
		{
			break;
		}
		
		mainAccess = false;

		for (int i = 0; i < mas.size(); i++)
			cout << mas[i] << ' ';
		cout << endl;

		sortAccess = true;
		lk.unlock();
		cv.notify_all();

	}

	func.join();
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
