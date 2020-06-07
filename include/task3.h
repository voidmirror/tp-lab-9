#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <thread>
#include <time.h>
using namespace std;

const int max_products = 15;
const int max_queue = 6;


mutex mutex_2;

class customer {
private:
	int id;
	vector<int> products;
public:
	customer(int id) {
		srand(time(nullptr));
		this->id = id;
		for (int i = 0; i < rand()%max_products + 1; i++)
			products.push_back(rand()%max_products);
	}
	int get_id() {
		return id;
	}
	int get_products() {
		return products.size();
	}
};



void serve(queue<customer*> customers, int thread) {
	while (!customers.empty()) {
		customer* item = customers.front();
		for (int i = 0; i < item->get_products(); i++) {
			mutex_2.lock();
			cout << item->get_id() << ". Product " << i << ". " << thread << "\n";
			mutex_2.unlock();
			this_thread::sleep_for(1s);
		}
		customers.pop();
	}
}