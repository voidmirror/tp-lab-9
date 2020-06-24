#include "task3.h"


std::mutex shopMutex;


Customer::Customer(int ID) {
	setCustomerID(ID);
	addGoodsToCustomer();
}

void Customer::addGoodsToCustomer() {
	int goodsAmount = rand() % MAX_GOODS + 1;
	for (int i = 0; i < MAX_GOODS; i++)	{
		this->goods.push_back(rand() % goodsAmount);
	}
}

std::vector<int> Customer::getGoodsOfCustomer() {
	return this->goods;
}

void Customer::setCustomerID(int ID) {
	this->customerID = ID;
}

int Customer::getCustomerID() {
	return this->customerID;
}

void payingForGoods(std::queue<Customer*> customers, int threadNumber) {
	while (!customers.empty()) {
		Customer* customer = customers.front();
		for (int i = 0; i < customer->getGoodsOfCustomer().size(); i++)	{
			shopMutex.lock();
			std::cout << "Thread number: " << threadNumber << " | Customer: " << customer->getCustomerID() << " | Good: " << customer->getGoodsOfCustomer()[i] << std::endl;
			shopMutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		}

		customers.pop();
	}
}

void startTask3() {
	std::cout << "-------------------------\nTask number 3:" << std::endl;
	std::vector<std::thread*> threads;
	std::queue<Customer*> customers;

	for (int i = 0; i < CUSTOMERS_AMOUNT; i++) {
		auto* customer = new Customer(i);
		customers.push(customer);

		if (customers.size() >= MAX_CUSTOMERS) {
			threads.push_back(new std::thread(payingForGoods, customers, threads.size()));
			while (!customers.empty()) {
				customers.pop();
			}
		}
	}

	for (auto &tempThread : threads) {
		tempThread->join();
	}
}