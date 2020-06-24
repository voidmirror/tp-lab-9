#include <iostream>
#include <string>
#include <windows.h>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <set>

#define TIME_TO_PEEP_ONE_PRODUCT 500
#define MAX_PRODUCT_AMOUNT 5
#define MAX_TIME_TO_SLEEP_BETWEEN_CUSTOMERS 2000
#define MIN_TIME_TO_SLEEP_BETWEEN_CUSTOMERS 100

using namespace std;

struct Cashbox;
int cashbox_work(Cashbox* ths);

struct Cashbox
{
	mutex m;
	thread *t;
	queue<vector<int>*> q; // customers queue
	Cashbox(vector<int>* customer)
	{
		q.push(customer);
	}

	int get_size()
	{
		return this->q.size();
	}

	void add_customer(vector<int>* customer)
	{
		this->q.push(customer);
	}

	mutex* get_mutex()
	{
		mutex* ptr = &m;
		return ptr;
	}

	string draw_queue()
	{
		string res = "";
		for (int i = 0; i < q.size(); i++)
		{
			vector<int> *ptr = q.front();
			q.pop();
			q.push(ptr);
			res += " " + to_string(ptr->size());
		}
		return res;
	}
};

class Shop
{
	int customers_amount;
	set<Cashbox*> cashboxes;

public:
	Shop(int customers_amount)
	{
		this->customers_amount = customers_amount;
	}

	void work()
	{
		for (int i = 0; i < customers_amount; i++)
		{
			queue<Cashbox*> delete_queue;
			for (auto i : cashboxes) // delete empty cashboxes
			{
				mutex *mutex_ptr = i->get_mutex();
				mutex_ptr->lock();
				if (i->get_size() == 0)
				{
					delete_queue.push(i);
				}
				else
				{
					mutex_ptr->unlock();
				}
			}
			while (!delete_queue.empty())
			{
				cashboxes.erase(delete_queue.front());
				delete_queue.pop();
			}

			vector<int> *new_customer = new vector<int>(rand() % MAX_PRODUCT_AMOUNT + 1, rand() % 10); // create new customer
			bool need_for_new_cashbox = true; 
			for (auto i : cashboxes) // search for cashbox
			{
				mutex *mutex_ptr = i->get_mutex();
				mutex_ptr->lock();
				if (i->get_size() < 5)
				{
					i->add_customer(new_customer);
					need_for_new_cashbox = false;
				}
				mutex_ptr->unlock();
				if (!need_for_new_cashbox) // cashbox found
				{
					break;
				}
			}

			if (need_for_new_cashbox) // create new cashbox
			{
				Cashbox *cashbox = new Cashbox(new_customer);
				cashboxes.insert(cashbox);
				thread *t = new thread(cashbox_work, cashbox);
				cashbox->t = t;
			}

			for (auto i : cashboxes) // print state
			{
				i->get_mutex()->lock();
				cout << "Cashbox " << i << ":" << i->draw_queue() << "\n";
				i->get_mutex()->unlock();
			}
			cout << "------------------------------------------\n";

			// sleep before next customer
			Sleep(rand() % (MAX_TIME_TO_SLEEP_BETWEEN_CUSTOMERS - MIN_TIME_TO_SLEEP_BETWEEN_CUSTOMERS) + MIN_TIME_TO_SLEEP_BETWEEN_CUSTOMERS); 
		}

		for (auto i : cashboxes)
		{
			if (i->t != nullptr)
			{
				i->t->join();
			}
		}

		cout << "Shop closed\n";
	}
};

int cashbox_work(Cashbox* ths)
{
	while (!ths->q.empty())
	{
		Sleep(TIME_TO_PEEP_ONE_PRODUCT * ths->q.front()->size());
		ths->m.lock();
		vector<int> *ptr = ths->q.front();
		vector<int>().swap(*ptr);
		ths->q.pop();
		ths->m.unlock();
	}
	return 0;
}

int main3()
{
	srand(time(NULL));
	Shop *sh = new Shop(20);
	sh->work();
	return 0;
}

int main()
{
	main3();
}