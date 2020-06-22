#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <queue>

using namespace std;
mutex mtx;

void workingCashDesk(queue<vector<int>> q)
{
	mtx.lock();
	srand(time(NULL));
	while (!q.empty())
	{	
		int checkAmount = 0;
		this_thread::sleep_for(chrono::milliseconds(500));
		for (auto product : q.front())
		{
			checkAmount += rand() % 1000;
		}
		cout << checkAmount << " rub from you" << endl;
		q.pop();
	}
	mtx.unlock();
}

int main()
{
	srand(time(NULL));
	queue<vector<int>> consumers;
	vector<int> products;
	vector<thread*> threads;

	int totalConsumers = 1+ rand() % 15;
	cout << "Total consumers: " << totalConsumers << endl;

	for (int i = 0; i < totalConsumers; i++)
	{
		int amountOfProds = 1 + rand() % 20;
		while (amountOfProds != 0)
		{
			products.push_back(1);
			amountOfProds--;
		}
		consumers.push(products);
		products.clear();
		if ((consumers.size() % 5 == 0) || (i == totalConsumers - 1))
		{
			threads.push_back(new thread(workingCashDesk, consumers));
			while (!consumers.empty())
			{
				this_thread::sleep_for(chrono::milliseconds(50));
				consumers.pop();
			}
		}
	}
	for (auto thread : threads) thread->join();
	return 0;
}