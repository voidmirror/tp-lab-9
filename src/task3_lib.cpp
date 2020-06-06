#include "task3_lib.h"

mutex mtx;

customer::customer()
{
	srand(time(NULL));
	this->product_num = rand() % this->max_num;
}

int customer::getProducts()
{
	return this->product_num;
}

void customer::perform()
{
	sleep(this->product_num);
}

void kassa(queue<customer*> qCustomers, int index)
{
	while (!qCustomers.empty())
	{
		qCustomers.front()->perform();
		cout << "Kassa nomer: " << index << endl << "Customers remained : " << qCustomers.size() << endl;
		qCustomers.pop();
	}

}