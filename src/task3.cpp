#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <ctime>
#include <list>

const std::size_t queueMaxLen = 5;
const std::size_t countOfCustomers = 11;

std::mutex mtx;
std::condition_variable cv;

struct Customer {

	Customer(std::size_t _numOfCustomer) : numOfCustomer(_numOfCustomer) {
		std::size_t n = rand() % 20 + 1;
		for (std::size_t i = 1; i <= n; i++)
			products.push_back(rand() % 6 + 1);
		
	}
	std::size_t numOfCustomer;
	std::vector<std::size_t> products;
};

std::list<std::queue<Customer*>*> allQueues;

std::list<std::thread*> allThreads;

void serviceCustomers(std::queue<Customer*>*, int);

void addNewCustomers() {
	std::size_t numOfCashier = 1;
	for (std::size_t i = 1; i <= countOfCustomers; i++) {
		bool added = false;
		for (std::queue<Customer*>* x : allQueues)
			if (x->size() < queueMaxLen) {
				x->push(new Customer(i));
				added = true;
			}
		if (!added) {
			std::queue<Customer*>* newQueue = new std::queue<Customer*>();
			newQueue->push(new Customer(i));
			allQueues.push_back(newQueue);
			std::thread* t = new std::thread(serviceCustomers, newQueue, numOfCashier++);
			allThreads.push_back(t);
		}
	}
	for (auto x : allThreads)
		x->join();
}

void serviceCustomers(std::queue<Customer*>* customers, int numOfCashier) {
	while (!customers->empty()) {
		Customer* customer = customers->front();
		customers->pop();
		for (std::size_t i = 0; i < customer->products.size(); i++) {
			{
				std::lock_guard<std::mutex> lg(mtx);
				std::cout << "Cashier #" << numOfCashier << " registered product #" << i + 1 <<
					"(count : " << customer->products[i] << ") for customer #" << customer->numOfCustomer << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(customer->products[i] * 1000));
		}
		{
			std::lock_guard<std::mutex> lg(mtx);
			std::cout << "Cashier #" << numOfCashier << " served customer #" << customer->numOfCustomer << std::endl;
		}
	}
}

int main() {
	srand(time(nullptr));

	addNewCustomers();

	return 0;
}