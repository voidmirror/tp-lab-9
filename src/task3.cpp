#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <set>
#include <atomic>

using namespace std;

mutex mx;

struct SaleRegister;
void registerWork(SaleRegister* saleRegister);

struct SaleRegister {
	thread th;
	queue<vector<int>>* customers;
	atomic<bool> isWorking{};
	//bool isWorking;
	thread::id id;
	explicit SaleRegister(const vector<int>& person) {
		customers = new queue<vector<int>>();
		customers->push(person);
		isWorking = true;
		th = thread(registerWork, this);
	}
	~SaleRegister() {
		mx.lock();
		cout << "SaleRegister " << id << " stoped" << '\n';
        mx.unlock();
		delete customers;
		th.join();
		//cout << th.get_id() << '\n';
	}
};

void registerWork(SaleRegister* saleRegister) {
	saleRegister->id = this_thread::get_id();
	mx.lock();
	cout << "SaleRegister " << saleRegister->id << " started" << '\n';
	mx.unlock();
	while (!saleRegister->customers->empty()) {
		vector<int>purchases = saleRegister->customers->front();
		for (int t : purchases) {
			this_thread::sleep_for(chrono::milliseconds(t * 500));
		}
		mx.lock();
		cout << "Customer is served by " << this_thread::get_id() << '\n';
		saleRegister->customers->pop();
		mx.unlock();
	}
	saleRegister->isWorking = false;
}

struct Shop {
	set<SaleRegister*>saleRegisters;
	int customersCounter;
	explicit Shop(int customersCounter) {
		this->customersCounter = customersCounter;
	}

	void shopWork() {
		for (int i = 0; i < customersCounter; i++) {
			int purches = rand() % 5 + 1;
			vector<int>person;
			for (int item = 0; item < purches; item++) {
				int cnt = rand() % 5 + 1;
				person.push_back(cnt);
			}
			addCustomer(person);
			monitorSaleRegisters();
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
		while (monitorSaleRegisters());
	}
	void addCustomer(const vector<int>&person) {
		lock_guard<mutex> lk(mx);
		for (SaleRegister* saleRegister : saleRegisters) {
			if (saleRegister->isWorking && saleRegister->customers->size() < 5) {
				saleRegister->customers->push(person);
				cout << "Customer joined the queue at the SaleRegister " << saleRegister->id << '\n';
				return;
			}
		}
		SaleRegister* saleRegister = new SaleRegister(person);
		saleRegisters.insert(saleRegister);
		cout << "Customer joined the queue at the SaleRegister " << saleRegister->id << '\n';
	}

	bool monitorSaleRegisters() {
		vector<SaleRegister*>closed;
		for (SaleRegister* saleRegister : saleRegisters) {
			if (!saleRegister->isWorking) {
				closed.push_back(saleRegister);
			}
		}
		for (SaleRegister* saleRegister : closed) {
			saleRegisters.erase(saleRegister);
			delete saleRegister;
		}
		return !saleRegisters.empty();
	}
};

int main() {
	srand(time(0));
	Shop shop(20);
	shop.shopWork();
}