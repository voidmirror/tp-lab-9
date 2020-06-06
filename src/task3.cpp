#include "task3_lib.h"

int main()
{
	srand(time(NULL));
	int customer_number = rand() % 30;
	int max_queue = 5;
	int kassa_index = 0;
	vector<thread*> threads;
	queue<customer*> customer_queue;

	for (size_t i = 0; i < customer_number; i++)
	{
		customer_queue.push(new customer());
		if (customer_queue.size() % max_queue == 0 || i == customer_number - 1)
		{
			kassa_index = threads.size();
			threads.push_back(new std::thread(kassa, customer_queue, kassa_index));
			while (!customer_queue.empty())	customer_queue.pop();
		}
	}

	for (auto& thread_to_join : threads)
	{
		thread_to_join->join();
	}
	return 0;
}