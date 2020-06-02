#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>

using namespace std;

mutex mx;

class Customer {
public:
	vector<int> goods;
	int number;
};

void serve(Customer& c) {
	for (int i : c.goods) {
		this_thread::sleep_for(chrono::milliseconds(i));
	}
}

void Cashbox(queue<Customer>* custs, int amount) {
	Customer* cst;
	mx.lock();
	cout << amount << " place was opened " << this_thread::get_id << endl;
	mx.unlock();
	while (true) {
		cst = &custs->front();
		serve(custs->front());

		mx.lock();
		cout << this_thread::get_id << "\t" << cst->number << " customer served" << endl;
		custs->pop();
		if (custs->empty()) {
			cout << amount << " place was closed " << this_thread::get_id << endl;
			mx.unlock();
			return;
		}
		mx.unlock();
	}
}

int main() {
	vector<queue<Customer>*> shop;
	vector<thread*> ts;
	vector<Customer*> to_delete;
	int size;
	int amount = 1;
	int number_cust = 1;
	Customer* cust;
	queue<Customer>* q;
	int number;
	bool solved;
	for (int i = 0; i < 100; i++) {

		this_thread::sleep_for(chrono::milliseconds((rand() % 51) * 10)); // time before new customer 0-0.5 seconds

		number = rand() % 10 + 1;
		cust = new Customer;
		for (int j = 0; j < number; j++) {
			cust->goods.push_back((rand() % 21 + 5) * 10); //0.05 - 0.25 second
		}
		cust->number = number_cust++;
		to_delete.push_back(cust);

		solved = false;

		if (shop.size() == 0) {
			q = new queue<Customer>;
			(*q).push(*cust);
			shop.push_back(q);
			ts.push_back(new thread(Cashbox, q, amount++));
		}
		else {
			mx.lock();

			//current 
			cout << "=================" << endl;
			for (auto i : shop) {
				cout << i->size() << " "; // shows current amount of places and number of people 
			}
			cout << endl << "=================" << endl;

			int i = 0;
			while (i < shop.size()) {
				size = shop[i]->size();
				if (size == 5) {
					i++;
					continue;
				}
				if (size == 0) {
					shop.erase(shop.begin() + i);
					continue;
				}
				shop[i]->push(*cust);
				solved = true;
				break;
			}
			if (!solved) {
				q = new queue<Customer>;
				(*q).push(*cust);
				shop.push_back(q);
				ts.push_back(new thread(Cashbox, q, amount++));
			}
			mx.unlock();
		}
	}

	for (thread* t : ts) {
		t->join();
	}

	for (auto i : to_delete) {
		delete i;
	}

	return 0;
}