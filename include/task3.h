#pragma once
#include <stack>
#include <queue>
#include <thread>

using namespace std;

class Customer {
private:
	stack<int> purchases;
public:
	Customer();
	int checkOne();
};

class CashDeck {
private:
	queue<Customer*> line;
	int customersCounter;
	int num;
	thread* th;
public:
	CashDeck(Customer* first, int num);
	~CashDeck();
	bool putCustomer(Customer* customer);
	bool empty();
};