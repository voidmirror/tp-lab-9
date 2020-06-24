#include "task3.h"
#include <mutex>
#include <iostream>

mutex console_mtx;

Customer::Customer() {
	int size = rand() % 10 + 1;
	for (int i = 0; i < size; i++) {
		purchases.push((rand() % 18 + 3) * 10 - 1);
	}
}

int Customer::checkOne() {
	if (purchases.empty()) {
		return -1;
	}
	int price = purchases.top();
	purchases.pop();
	return price;
}

CashDeck::CashDeck(Customer* first, int num) {
	line.push(first);
	customersCounter = 1;
	this->num = num;
	{
		lock_guard<mutex> lock(console_mtx);
		cout << "#" << num << " opened." << endl;
	}
	th = new thread([this]() -> void {
		int sum = 0;
		while (!line.empty()) {
			int price = line.front()->checkOne();
			if (price == -1) {
				delete line.front();
				line.pop();
				{
					lock_guard<mutex> lock(console_mtx);
					cout << "#" << this->num << ", customer " << customersCounter << " pays " << sum << " coins." << endl;
				}
				customersCounter++;
				sum = 0;
				// simulating payment for all products
				this_thread::sleep_for(chrono::milliseconds(800));
			}
			else {
				sum += price;
				lock_guard<mutex> lock(console_mtx);
				cout << "#" << this->num << ", customer " << customersCounter << " took an item for " << price << " coins." << endl;
			}
			// time gap between checking to products
			this_thread::sleep_for(chrono::milliseconds(300));
		}
		});
}

CashDeck::~CashDeck() {
	if (th != nullptr) {
		th->join();
		delete th;
	}
	{
		lock_guard<mutex> lock(console_mtx);
		cout << "#" << num << " closed." << endl;
	}
	while (!line.empty()) {
		delete line.front();
		line.pop();
	}
}

// false - line is full
bool CashDeck::putCustomer(Customer* customer) {
	if (line.size() > 5) {
		return false;
	}
	line.push(customer);
	return true;
}

bool CashDeck::empty() {
	return line.empty();
}