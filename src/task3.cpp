#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<queue>
#include<chrono>
#include<random>
#include<algorithm>

#define QueueSize 5
#define NumbOfConsumers 20
#define MaxGoods 5

using namespace std;

mutex mtx1;
mutex mtx2;

class Consumer {
private:
	vector<int> goods;
public:
	Consumer() {
		for (size_t i = 1; i <= MaxGoods; i++) {
			goods.push_back(rand() % 10 + 1);
		}
	}
	vector<int> getGoods() {
		return goods;
	}
};

vector<queue<Consumer*>*> Queues;
vector<thread*> Threads;

void ServeConsumer(Consumer* consumer) {
	vector<int> goods = consumer->getGoods();
	lock_guard<mutex> lock(mtx2);
	for (size_t i = 0; i < MaxGoods; i++)
	{
		cout << goods[i] << " ";
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	cout << endl << "consumer is served" << endl;
}

void ServeQueue(queue<Consumer*>* consumers) {
	while (!consumers->empty())
	{
		Consumer* consumer = consumers->front();
		ServeConsumer(consumer);
		consumers->pop();
	}
	lock_guard<mutex> lock(mtx1);
	cout << "queue is served" << endl;
	Queues.erase(find(Queues.begin(), Queues.end(), consumers));
}

int main() {
	srand(time(0));
	for (size_t i = 0; i < NumbOfConsumers; i++) {
		for (auto q : Queues) {
			if (q->size() < QueueSize)
			{
				lock_guard<mutex> lock(mtx1);
				q->push(new Consumer);
			}
			else
			{
				lock_guard<mutex> lock(mtx1);
				auto newQueue = new queue<Consumer*>();
				newQueue->push(new Consumer);
				Queues.push_back(newQueue);
				thread* newThread = new thread(ServeQueue, newQueue);
				Threads.push_back(newThread);
			}
		}
		if (Queues.size() == 0)
		{
			lock_guard<mutex> lock(mtx1);
			auto newQueue = new queue<Consumer*>();
			newQueue->push(new Consumer);
			Queues.push_back(newQueue);
			thread* newThread = new thread(ServeQueue, newQueue);
			Threads.push_back(newThread);
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	for (auto t : Threads) {
		t->join();
	}
	return 0;
}