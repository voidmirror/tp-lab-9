#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <ctime>

using namespace std;

mutex mutObj;


void serveBuyers(queue<vector<int>> queue)
{
	lock_guard<mutex> lockGuard(mutObj);

	cout << queue.size() << " buyers at the cashbox ¹" << this_thread::get_id() << endl;

	short int cnt = 1;
	int cashBoxSum = 0;
	while (queue.empty() == false) 
	{
		cout << cnt << " customer has " << queue.front().size() << " products, ";

		int sum = 0;
		for (int i = 0; i < queue.front().size(); i++)
		{
			sum += queue.front()[i]; 
		}
		cout << "total: " << sum << " rub)" << endl;
		for (int j = 0; j < queue.front().size(); j++) 
		{
			this_thread::sleep_for(chrono::milliseconds(40));
		}
		cashBoxSum += sum;
		queue.pop(); 
		cnt++; 
	}
	cout << "Total sum in cashbox: " << cashBoxSum << " rub \n" << endl;
}

int main()
{
	vector <int> products;	
	vector <thread*> threads;
	queue <vector<int>> buyers;	

	
	int buyersNum = rand() % 25; 

	cout << "Buyers at the market: " << buyersNum << endl;

	int productsNum; 
	for (int i = 0; i < buyersNum; i++) 
	{
		productsNum = 1 + rand() % 10;

		
		while (productsNum--)
		{
			int price = 1 + rand() % 350;
			products.push_back(price); 
		}

		buyers.push(products); 
		products.clear();

		if ((i == buyersNum - 1) || (buyers.size() % 5 == 0)) 
		{
			threads.push_back(new thread(serveBuyers, buyers)); 
			while (buyers.empty() == false) buyers.pop(); 
		}
	}
	for (auto& thread : threads) thread->join(); 

	return 0;
}