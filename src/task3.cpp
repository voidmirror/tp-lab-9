#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <algorithm>
using namespace std;

mutex mutex_name1;
mutex mutex_name2;
int CountOfPeople = 3;
int CountOfProduct = 5;

class Customer {
public:
	vector <int> products;
	Customer()
	{
		for (size_t i = 1; i <= CountOfProduct; i++)
			products.push_back(rand() % 10 + 1);
	}
};

vector<queue<Customer*>*> allQueues;
vector<thread*> allThreads;

void ClientService(Customer* customer, int NumberOfBox){
	for (int i = 0; i < customer->products.size(); i++) {
		{
			lock_guard<mutex> lock(mutex_name1);
			cout << "product number " << customer->products[i] << " on checkout " << NumberOfBox << "\n";
		}
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	{
		lock_guard<mutex> lg(mutex_name1);
		cout << "checkout number " << NumberOfBox << " has finished working" << std::endl;
	}
}

void QueueService(queue<Customer*>* customers, int NumberOfBox) {
	while (!customers->empty()) 
	{
		Customer* customer = customers->front();
		ClientService(customer, NumberOfBox);
		customers->pop();
		delete customer;
	}
	lock_guard<mutex> lg(mutex_name2);
	allQueues.erase(find(allQueues.begin(), allQueues.end(), customers));
	delete customers;
}

void addNewCustomer(int count)
{
	int NumberOfBox = 1;
	while (count !=0) {
		bool flag2 = false;
		lock_guard<mutex> lg(mutex_name2);
		for (queue<Customer*>* queue1 : allQueues)
			if (queue1->size() < CountOfPeople) {
				queue1->push(new Customer);
				flag2 = true;
			}
		if (!flag2)
		{
			queue<Customer*>* newQueue = new queue<Customer*>();
			allQueues.push_back(newQueue);
			newQueue->push(new Customer);
			thread* newTread = new thread(QueueService, newQueue, NumberOfBox++);
			allThreads.push_back(newTread);
		}
		count--;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	for (auto x : allThreads) {
		x->join();
	}
}

int main() {
	addNewCustomer(10);
}