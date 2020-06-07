// main3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <ctime>
#include<chrono>

using namespace std;

mutex mu;
void customer(queue<vector<int>> mas)
{
	lock_guard<mutex> lockGuard(mu);
	int count = 0;
	while (!mas.empty())
	{
		for(int i=0;i<mas.front().size();i++)
		this_thread::sleep_for(chrono::milliseconds(100));
		mas.pop();
		count++;
	}
	cout << "number of customers in the queue  " << count << endl;
}

int main()
{
	vector <int> products;	
	vector <thread*> processes;	
	queue <vector<int>> clients;

	srand(time(0));

	int clients_size = 16;
	int products_size;
	for (int i = 0; i < clients_size; i++)
	{
		products_size = 1 + rand() % 5;

		for (int j = 0; j < products_size; j++)
		{
			products.push_back(j);
		}

		clients.push(products);
		products.clear();
		if (((i+1) % 5 == 0)|| i+1== clients_size)
		{
			processes.push_back(new thread(customer, clients));
			while (!clients.empty())
				clients.pop();
		}
	}
	for (auto& k : processes) 
		k->join();
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
