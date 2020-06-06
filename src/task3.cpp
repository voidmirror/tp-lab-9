#include <thread>
#include <iostream>
#include <ctime>
#include <queue>
#include <mutex>
#include <vector>
#include <random>

using namespace std;

mutex mut;

void Service(queue<vector<int>> buyers){
	for (int i = 1; !buyers.empty(); i++){
		mut.lock();
		cout << "Customer service with " << buyers.front().size() << " items in the basket " << this_thread::get_id() << endl;
		mut.unlock();
		for (int j = 0; j < buyers.front().size(); j++){
			this_thread::sleep_for(chrono::milliseconds(400));
		}
		buyers.pop();
	}
}

int main(){
	mt19937 gen(time(NULL));

	queue<vector<int>> buyers;
	vector<thread*> threads;
	vector <int> goods;

	int BuyersNumber = gen() % 16, GoodsNumber;

	cout << "Now we have " << BuyersNumber << " buyers " << endl;

	for (int i = 0; i < BuyersNumber; i++){
		GoodsNumber = 1 + gen() % 10;
		while (GoodsNumber--){
			int price = 1 + gen() % 500;
			goods.push_back(price);
		}
		buyers.push(goods);
		goods.clear();
		if ((buyers.size() % 5 == 0) || (i == BuyersNumber - 1)){
			threads.push_back(new thread(Service, buyers));
			while (!buyers.empty())
				buyers.pop();
		}
	}
	for (auto& th : threads)
		th->join();

	return 0;
}