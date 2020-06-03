#pragma once 

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <queue>
#include <chrono>

using namespace std;

const int max_len_queue = 5;
const int max_cnt_products = 15;
const int max_cnt_product = 5;
const int max_num_people = 20;
mutex mtx;

class Customer
{
private:
	vector<int> products;
	int id;

public:
	Customer(int id_)
	{
		id = id_;
		int cnt_products = rand() % max_cnt_products + 1;

		for (int i = 0; i < cnt_products; i++)
		{
			products.push_back(rand() % max_cnt_product + 1);
		}
	}

	vector<int> get_cust_products()
	{
		return products;
	}

	int get_cust_id()
	{
		return id;
	}
};

void service(queue<Customer*> customers, int num_thread)
{
	while (!customers.empty())
	{
		Customer* customer = customers.front();

		for (size_t i = 1; i <= customer->get_cust_products().size(); i++)
		{
			mtx.lock();
			cout << "Cashbox number: " << num_thread << "\tCustomer: " << customer->get_cust_id() << "\tProduct: #" << i << "\tCount: " <<
				customer->get_cust_products()[i - 1] << endl;
			mtx.unlock();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}

		mtx.lock();
		cout << "Cashbox number: " << num_thread << "\tserved customer: " << customer->get_cust_id() << endl;
		mtx.unlock();

		customers.pop();
		//delete customer;
	}
}

void shop()
{
	int num_of_cashbox = 1;
	vector<thread*> threads;
	queue<Customer*> customers;

	for (int i = 1; i <= max_num_people; i++)
	{
		Customer* customer = new Customer(i);
		if (customers.size() < max_len_queue - 1)
		{
			customers.push(customer);
		}
		else
		{
			customers.push(customer);
			threads.push_back(new thread(service, customers, num_of_cashbox++));
			while (!customers.empty())
			{
				customers.pop();
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	for (auto th : threads)
	{
		th->join();
	}
}
