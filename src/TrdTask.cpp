#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <time.h>
#include <chrono>
#include <list>


struct Buyer {
	Buyer(std::vector<int> acquiring) {
		this->acquiring = acquiring;
	}
	std::vector<int> acquiring;
};

class Walmart {
public:
	Walmart(int maximumProducts, int maximumBuyers,
		int maximumPrice, int qLenght) :
		maximumProducts(maximumProducts), maximumBuyers(maximumBuyers),
		maximumPrice(maximumPrice), qLenght(qLenght) {}
	Buyer create()
	{
		int products = rand() % maximumProducts + 1;
		std::vector<int> acquiring(products);

		for (int j = 0; j < products; ++j)
		{
			acquiring[j] = rand() % maximumPrice + 1;
		}
		return Buyer(acquiring);
	}
	void serve(Buyer buyer, int num)
	{
		for (std::size_t i = 0; i < buyer.acquiring.size(); i++)
		{
			int time = rand() % 3000;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
			std::unique_lock<std::mutex> lk(mx);
			std::cout << "id" << std::this_thread::get_id() << ", buyer " << num << " acquiring " << i + 1 << '\n';
			lk.unlock();
		}
	}
	void runCashing(std::queue <Buyer>* buyers) {
		int count_buyers = 1;
		while (!buyers->empty()) {
			auto buyer = buyers->front();
			buyers->pop();
			serve(buyer, count_buyers);
			count_buyers++;
		}
		delete buyers;
	}
	void serve_all() {
		for (int i = 0; i < maximumBuyers; ++i) {
			bool find_queue = false;
			auto it = queues.begin()
				;
			while (it != queues.end())
			{
				int time = rand() % 500;
				std::this_thread::sleep_for(std::chrono::milliseconds(time));

				if ((*it) == nullptr) {
					auto new_it = it;
					new_it++;
					queues.erase(it);
					it = new_it;
					continue;
				}
				if ((*it)->size() < qLenght)
				{
					(*it)->push(create());
					find_queue = true;
					break;
				}
				++it;
			}
			if (!find_queue) {
				auto que = new std::queue<Buyer>;
				que->push(create());
				queues.push_back(que);
				threads.push_back(new std::thread(&Walmart::runCashing, this, que));
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
	std::list<std::queue<Buyer>*> queues;
	int maximumProducts;
	int maximumBuyers;
	int maximumPrice;
	int qLenght;
	std::mutex mx;
};


int main() {
	srand(time(nullptr));
	Walmart walmart(15, 48, 200 50);
	walmart.run();
	return 0;
}