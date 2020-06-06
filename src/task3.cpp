#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include <chrono>
#include<queue>
#include<ctime>
#include<random>

using namespace std;

mutex mx3;

class Customer {
public:
	vector<int> products;
	int id;
	bool served;
	Customer(int id);
};


Customer::Customer(int id) {
	random_device rand;
	this->id = id;
	this->served = false;
	int num = rand() % 10 + 1;

	for (int i = 0; i < num; i++) {
		products.push_back(rand() % 20);
	}
}


void serve(Customer* cust) {
	for (int i = 0; i < cust->products.size(); i++) {
		this_thread::sleep_for(chrono::seconds(1));
	}

	{
		lock_guard<mutex> lock(mx3);
		int idthread = hash<thread::id>{}(this_thread::get_id());
		cout << "Thread " << idthread << " " << "served " << cust->id << endl;
	}
}


void cashbox(queue<Customer*> q) {
	while (!q.empty()) {
		Customer* cust = q.front();
		serve(cust);
		q.pop();
	}
}


bool AllServed(vector<Customer*>& customers) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->served == false) {
			return false;
		}
	}
	return true;
}


int main() {
	int tid = hash<thread::id>{}(this_thread::get_id());
	vector<Customer*> customers;
	vector<thread*> ts;

	cout << "Main " << tid << endl;

	for (int i = 0; i < 20; i++) {
		customers.push_back(new Customer(i));
	}

	random_device rand;
	queue<Customer*> q;
	while (1) {
		int moment = rand() % 100 + 1;
		int num = rand() % 10;
		for (int i = 0; i < num; i++) {
			int j = rand() % customers.size();
			this_thread::sleep_for(chrono::milliseconds(moment));
			if (customers[j]->served == false && q.size() < 5) {
				lock_guard<mutex> lock(mx3);
				q.push(customers[j]);
				customers[j]->served = true;
				cout << "New customer number " << j << endl;
			}
		}

		if (q.size() == 5) {
			ts.push_back(new thread(&cashbox, q));
			queue<Customer*> empty;
			swap(q, empty);
		}

		if (!q.empty()) {
			Customer* cust = q.front();
			serve(cust);
			q.pop();
		}
		if (AllServed(customers))
			break;
	}

	for (auto& th : ts)
		th->join();
	return 0;
}