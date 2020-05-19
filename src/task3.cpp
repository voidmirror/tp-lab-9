#include "task3.h"

std::mutex mutex;

Customer::Customer()
{
    this->products = rand() % this->maxProductsNum ;
}

Customer::~Customer()
{
}

unsigned int Customer::getProducts()
{
    return this->products;
}

void Customer::serve()
{
    sleep( this->products );
}

void service(std::queue<Customer*> var, size_t index)
{
    
    while (!var.empty())
    {
        var.front()->serve();
        std::cout << "Place: " << index 
            << " | Products: " << var.front()->getProducts() 
            << " | Cust: " << var.size() << std::endl;
        var.pop();
    }
    
}