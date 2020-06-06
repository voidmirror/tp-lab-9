#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>

bool NeedToOpenNew = true;
int CountCashboxes = 0;

void Signal(std::queue<std::vector<int>>& buyers)
{
	srand(time(NULL));
	while (true)
	{
		if (buyers.size() == 5)
		{
			NeedToOpenNew = true;
			return;
		}
		std::vector<int> purchases;
		int NumberOfPurchases = rand() % 10 + 1;
		for (int i = 0; i < NumberOfPurchases; i++)
		{
			purchases.push_back(rand() % 100 + 1);
		}
		buyers.push(purchases);

		int TimeToNext = rand() % 3 + 1;
		std::this_thread::sleep_for(std::chrono::seconds(TimeToNext));
	}
}

void Cashboxes()
{
	
	std::queue<std::vector<int>> buyers;

	std::cout << "Cashboxe #" << std::this_thread::get_id() << " start work." << std::endl;

	std::thread thread(Signal, std::ref(buyers));
	thread.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	while (buyers.size() != 0)
	{
		std::cout << "Start new person: ";
		for (int i = 0; i < buyers.front().size(); i++)
		{
			std::cout << buyers.front()[i] << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		std::cout << std::endl;
		buyers.pop();
	}
	std::cout << "Cashboxe #" << std::this_thread::get_id() << " stop work." << std::endl;
	CountCashboxes--;
}


int main()
{
	do
	{
		if (NeedToOpenNew == true)
		{
			std::thread thread(Cashboxes);
			NeedToOpenNew = false;
			thread.detach();
			CountCashboxes++;
		}
	} while (CountCashboxes > 0);
}