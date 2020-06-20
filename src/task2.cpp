#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <random>


using namespace std;
vector<thread*> threads;
bool finished = false;

mutex mtx;
condition_variable cv;
queue<int> q;
random_device rd;
mt19937 mersenne(rd());



class Client {
private:
	vector<int> products;
	int id;
public:
	Client(int id, int products_limit) : id(id) {
		int number_of_products = mersenne() % products_limit + 1;
		for (int i = 0; i < number_of_products; ++i) {
			products.push_back(i);
		}
	}

	vector<int> get_products(){
		return products;
	}

	int get_id() {
		return id;
	}

	void serve(int cash_reg_id, int delay_serving_limit) {
		int rand_delay = mersenne() % delay_serving_limit;
		this_thread::sleep_for(chrono::milliseconds(rand_delay));
		{
			lock_guard<mutex> lock(mtx);
			cout << "Клиент "<< id << " совершил покупку на кассе номер " << cash_reg_id <<".\n";
		}
		
	}
};


void cash_registry(queue<Client*>* q, int thread_id, int delay_serving_limit) {
	
	while (true) {
		Client* current_client = q->front();
		q->pop();
		mtx.lock();
		cout << "Клиент " << current_client->get_id() << " обслуживается. Количество покупок " << current_client->get_products().size() << ". Номер кассы "
			<< thread_id << ".\n";
		mtx.unlock();
		current_client->serve(thread_id, delay_serving_limit);
		if (q->empty()) {
			this_thread::sleep_for(chrono::milliseconds(10000));
			if (q->empty()) {
				break;
			}
		}
	}
	delete q;
}


void shop(int products_limit, int queue_limit, int delay, int delay_serving_limit, int clients_number) {
	
	deque<queue<Client*>*> queues;
	queues.push_back(new queue<Client*>);
	int thread_id = 0;
	for (int i = 0; i < clients_number; ++i) {
		this_thread::sleep_for(chrono::milliseconds(delay));
		Client *new_client = new Client(i, products_limit);
		bool freeCashRegFound = false;
		int j = 0;
		while(true)
		{
			if (!freeCashRegFound && (queues[j]->size() < queue_limit)  && thread_id > 0) {
				queues[j]->push(new_client);
				break;
			}
			else{
				queue<Client*>* new_queue = new queue<Client*>;
				new_queue->push(new_client);
				queues.push_front(new_queue);
				threads.push_back(new thread(&cash_registry, new_queue, ++thread_id, delay_serving_limit));
				break;
			}
		}
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	shop(10, 4, 200, 800, 50 );
	for (thread* th : threads) {
		th->join();
	}
	system("pause");
	return 0;
}