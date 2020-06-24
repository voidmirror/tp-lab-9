#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>

using namespace std;

const int max_goods_amount = 10; 
const int max_customers_amount = 15;
const int max_queue_size = 5;
mutex mx;

class customer {
private:
	vector<int> goods; // тут хранятся цены товаров
	int goods_amount = 0;
	int id; 
public:
	customer(int id) {
		this->id = id;
		goods_amount = 1 + rand() % (max_goods_amount - 1); // у покупателя всегда есть хотя бы один товар
		for (int i = 0; i < goods_amount; i++) {
			goods.push_back(50*(rand() % 10)); // случайная цена в пределах от 50 до 500
		}
	}

	vector<int>& getGoods() {
		return goods;
	}

	int getId() {
		return id;
	}
};

void serve_line(queue<customer>* line) {
	while (!line->empty()) { // обслуживаем, пока очередь не пуста 
		customer current_customer = line->front();
		int sum = 0; 
		for (int i = 0; i < current_customer.getGoods().size(); i++) {
			sum += current_customer.getGoods()[i];
			mx.lock(); // для нормального вывода 
			cout << '\a' << "BLEEP! from the cash register " << this_thread::get_id() << " serving a customer with id " << current_customer.getId();
			cout << " - current total: " << sum << endl;
			mx.unlock();
			this_thread::sleep_for(chrono::milliseconds(500)); // тратим какое-то время на то, чтобы пробить товар
		}
		line->pop();
	}
}

int main() {
	srand(time(nullptr));
	cout << "MAIN: " << this_thread::get_id() << endl;
	
	int customers_amount = rand() % max_customers_amount;
	vector<queue<customer>*> queues; // вектор очередей
	vector<thread*> threads; // вектор потоков (касс)
	int id = 0;
	
	for (int i = 0; i < customers_amount; i++) {
		this_thread::sleep_for(chrono::milliseconds(600 + (rand()% 4)*100)); // покупатели появляются со случайными интервалами
		customer new_customer(id);
		id++;

		if (queues.size() == 0) { // если посетитель "приходит", и очередей нет
			queue<customer>* temp_q = new queue<customer>; // новая очередь
			temp_q->push(new_customer); // добавляем в нее покупателя
			queues.push_back(temp_q); // добавляем очередь в вектор очередей
			threads.push_back(new thread(serve_line, queues[0])); // "открываем" кассу
		}
		else {
			int full_q_count = 0;
			for (int j = 0; j < queues.size(); j++) { // покупатель "ищет" очередь, где меньше 5 других покупателей
				if (queues[j]->size() == max_queue_size) {
					full_q_count++; // считаем количество заполненных очередей
					continue;
				}
				else {
					queues[j]->push(new_customer); // если в очереди меньше 5 покупателей, добавляем туда нового покупателя
				}
			}
			if (full_q_count == queues.size()) { // если все очереди заняты
				queue<customer>* temp_q = new queue<customer>; // новая очередь
				temp_q->push(new_customer); // добавляем в нее покупателя
				queues.push_back(temp_q); // добавляем очередь в вектор очередей
				threads.push_back(new thread(serve_line, queues.back())); // "открываем" кассу 
			}
		}
	}

	for (auto th : threads) {
		th->join();
	}

	return 0;
}