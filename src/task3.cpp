#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <ctime>
#include <list>
#include <condition_variable>

using namespace std;

const size_t MAX_QUEUE = 5;
const size_t NUMBER_OF_CUSTOMERS = 20;

struct Customer {

	size_t customerNumber;
	vector<size_t> products;

	Customer(size_t _customerNumber) : customerNumber(_customerNumber) {
		size_t n = rand() % 20 + 1;
		for (size_t i = 1; i <= n; i++)
			products.push_back(rand() % 6 + 1);

	}
};

// ---------------- //

list<queue<Customer*>*> queues;
list<thread*> cashRegisters;

mutex mtx;
mutex newCustomerMtx;
condition_variable cv;

void serviceCustomers(queue<Customer*>* customers) {
	while (!customers->empty()) {
		Customer* customer = customers->front();
		for (size_t i = 0; i < customer->products.size(); i++) {
			{
				lock_guard<mutex> lg(mtx);
				cout << "Registered product for customer #" << customer->customerNumber << endl;
			}
			this_thread::sleep_for(chrono::milliseconds(customer->products[i] * 1000));
		}
		{
			lock_guard<mutex> lock(mtx);
			cout << "Served customer #" << customer->customerNumber << endl;
		}
		customers->pop();
		delete customer;
	}

	lock_guard<mutex> lock(newCustomerMtx);
	queues.erase(find(queues.begin(), queues.end(), customers));
	delete customers;
}

void addCustomers() {
	for (size_t i = 1; i <= NUMBER_OF_CUSTOMERS; i++) {
		{
			bool isAdded = false;
			lock_guard<mutex> lg(newCustomerMtx);
			for (queue<Customer*>* queue : queues)
				if (queue->size() < MAX_QUEUE) {
					queue->push(new Customer(i));
					isAdded = true;
				}
			if (!isAdded) {
				queue<Customer*>* newQueue = new queue<Customer*>();
				newQueue->push(new Customer(i));
				queues.push_back(newQueue);
				thread* t = new thread(serviceCustomers, newQueue);
				cashRegisters.push_back(t);
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));

	}
	for (auto cashRegister : cashRegisters)
		cashRegister->join();
}

int main() {
	srand(time(nullptr));
	addCustomers();
	return 0;
}