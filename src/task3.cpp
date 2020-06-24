#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <time.h>
#include <chrono>
#include <list>


struct Customer {
	Customer(std::vector<int> purchases) {
		this->purchases = purchases;
	}
	std::vector<int> purchases;
};

class Shop {
public:
	Shop(int max_products, int max_customers, int max_price, int queue_len) :
		max_products(max_products), max_customers(max_customers), max_price(max_price), queue_len(queue_len) {}
	Customer create_customer() {
		int products = rand() % max_products + 1;
		std::vector<int> purchases(products);
		for (int j = 0; j < products; ++j) {
			purchases[j] = rand() % max_price + 1;
		}
		return Customer(purchases);
	}
	void serve(Customer customer, int num) {
		for (std::size_t i = 0; i < customer.purchases.size(); i++) {
			int time = rand() % 1000;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
			std::unique_lock<std::mutex> lk(mx);
			std::cout << "Cash desk id " << std::this_thread::get_id() << ", customer " << num << " with purchase " << i + 1 << '\n';
			lk.unlock();
		}
	}
	void run_cash_desk(std::queue <Customer> * customers) {
		int count_customers = 1;
		while (!customers->empty()) {
			auto customer = customers->front();
			customers->pop();
			serve(customer, count_customers);
			count_customers++;
		}
		delete customers;
	}
	void serve_all() {
		for (int i = 0; i < max_customers; ++i) {
			bool find_queue = false;
			auto it = queues.begin();
			while (it != queues.end()) {
				int time = rand() % 500;
				std::this_thread::sleep_for(std::chrono::milliseconds(time));
				if ((*it) == nullptr) {
					auto new_it = it;
					new_it++;
					queues.erase(it);
					it = new_it;
					continue;
				}
				if ((*it)->size() < queue_len) {
					(*it)->push(create_customer());
					find_queue = true;
					break;
				}
				++it;
			}
			if (!find_queue) {
				auto it_q = new std::queue<Customer>;
				it_q->push(create_customer());
				queues.push_back(it_q);
				threads.push_back(new std::thread(&Shop::run_cash_desk, this, it_q));
			}
		}
		
	}

	void run() {
		serve_all();
		for (auto cur_queue : threads) {
			cur_queue->join();
		}
	}

private:
	std::vector<std::thread*> threads;
	std::list<std::queue<Customer>*> queues;
	int max_products;
	int max_customers;
	int max_price;
	int queue_len;
	std::mutex mx;
};


int main() {
	srand(time(nullptr));
	Shop shop(10, 50, 20, 5);
	shop.run();
	return 0;
}