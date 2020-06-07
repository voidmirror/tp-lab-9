#include "task3.h"

void cash(std::queue<Customer*> queue, uint num)
{
	while (!queue.empty())
	{
		queue.front()->exec();
		std::cout << "Number of CASH " << num << std::endl << std::endl;
		std::cout << "WAITING " << queue.size() << std::endl << std::endl;
		queue.pop();
	}
}

int main()
{
	std::vector<std::thread*> thread;
	std::queue<Customer*> customers;
	srand(time(NULL));
	int customersNumber = rand() % 40;
	int queueLimit = 8;
	int cashNumber = 0;

	while (customersNumber)
	{
		customers.push(new Customer());
		if (customers.size() % queueLimit == 0)
		{
			cashNumber = thread.size();
			thread.push_back(new std::thread(cash, customers, cashNumber));
			while (customers.size()) customers.pop();
		}
		customersNumber--;
	}

	for (auto &join : thread)
	{
		join->join();
	}

	getchar();
	return 0;
}