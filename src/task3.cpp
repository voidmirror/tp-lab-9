#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

void serve(queue<vector<int>> cash_desk) {
	lock_guard<mutex> lockGuard(mtx);
	cout << "\nThere are " << cash_desk.size() << " customers at the cash desk " << this_thread::get_id() << "\n";
	int counter = 1;
	while (!cash_desk.empty()) {
		cout << "\tServing customer " << counter << " with " << cash_desk.front().size() << " products. ";
		int customer_check = 0;
		for (size_t i = 0; i < cash_desk.front().size(); i++) {
			customer_check += cash_desk.front()[i];
		}
		cout << "Total amount: " << customer_check << " rubles\n";
		for (size_t j = 0; j < cash_desk.front().size(); j++) {
			this_thread::sleep_for(chrono::milliseconds(10 * rand() % 200));
		}
		cash_desk.pop();
		counter++;
	}
}

int main() {
	srand(time(0));
	vector<int> products;
	vector<thread*> threads;
	queue<vector<int>> customers;
	int customers_num = rand() % 30;
	int products_num, price;

	cout << "Hello! There are " << customers_num << " customers in Pyaterochka.";
	for (int i = 0; i < customers_num; i++) {
		products_num = 1 + rand() % 10;
		while (products_num--) {
			price = 1 + rand() % 150;
			products.push_back(price);
		}
		customers.push(products);
		products.clear();

		if ((i == customers_num - 1) || (customers.size() % 5 == 0)) {
			threads.push_back(new thread(serve, customers));
			while (!customers.empty()) {
				customers.pop();
			}
		}
	}
	for (auto & thread : threads) {
		thread->join();
	}
}