#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>

using namespace std;

#define count_cust 18
#define que_len 5

mutex mtx;

class Customer
{
private:
	vector<int> products;
public:
	Customer()
	{
		int size_prod = rand() % 10 + 5;
		for (int i = 0; i < size_prod; i++)
		{
			products.push_back(rand() % 20 + 20);
		}
	}
	vector<int> getProds()
	{
		return products;
	}

};

class Checkout
{
private:
	//int max_customers = 5;
	int size = 0;
	queue<Customer*> customers;
public:
	Checkout() {};

	void addCust(Customer* cust)
	{
		customers.push(cust);
		size++;
	}
	
	int getsize()
	{
		return size;
	}

	void serveCust()
	{
		int num = 1;
		int cnt;
		while (!customers.empty())
		{	
			cnt = 0;
			Customer* cust = customers.front();
			for (auto prod : cust->getProds())
			{
				cnt += prod;
				this_thread::sleep_for(chrono::milliseconds(prod * 25));
			}
			mtx.lock();
			cout << "Checkout #" << this_thread::get_id() << ", customer #" << num++ << " spent " << cnt << endl;
			mtx.unlock();
			delete customers.front();
			customers.pop();
		}
	}
};

class Shop
{
private:
	vector<thread*> threads;
	vector<Checkout*> checks;
public:
	Shop()
	{
		checks.push_back(new Checkout);
		for (size_t i = 0; i < count_cust; i++)
		{
			Customer* cust = new Customer;
			if (checks.back()->getsize() < que_len)
				checks.back()->addCust(cust);
			else
			{
				threads.push_back(new thread(&Checkout::serveCust, *(checks.back())));
				checks.push_back(new Checkout);
				checks.back()->addCust(cust);
			}
		}
		threads.push_back(new thread(&Checkout::serveCust, *(checks.back())));
		for (auto t : threads)
			t->join();
	}

	~Shop()
	{
		for (auto t : threads)
			delete t;
		for (auto ch : checks)
			delete ch;
	}
};

int main()
{
	Shop* magaz = new Shop();
	magaz->~Shop();
	getchar();
	return 0;
}
