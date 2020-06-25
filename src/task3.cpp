#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <chrono>
#include <mutex>

class Customer
{
private:
	int maxProductsNum = 5;
	int serviceTime = 1; // milliseconds
	int products = 0;
public:
	Customer();

	int getProducts();
	void serve();
};

std::mutex mutex;

Customer::Customer() {
	this->products = rand() % this->maxProductsNum + 1;
}

int Customer::getProducts() {
	return this->products;
}

void Customer::serve() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500 * getProducts()));
}

void service(std::queue<Customer*> q, int index) {
	//mutex.lock();
	while (!q.empty()) {
		q.front()->serve();
		std::cout << "Cashbox# " << index << " | Products: " << q.front()->getProducts() << " | CustomerNum: " << q.size() << std::endl;
		q.pop();
	}
	//mutex.unlock();
}

int main() {
	int customerNum = 23;
	int maxQueueLength = 5;
	int n = 10;
	std::vector<std::thread*> threads;
	std::queue<Customer*> queue;

	for (int i = 0; i < customerNum; i++) {
		queue.push(new Customer());
		if (queue.size() % maxQueueLength == 0 || i == customerNum - 1) {
			n = threads.size();
			threads.push_back(new std::thread(service, queue, n));
			while (!queue.empty()) {
				queue.pop();
			}
		}
	}

	std::cout << "Cashboxes: " << threads.size() << std::endl;
	
	for (auto &th : threads) {
		th->join();
	}
}