//
// Created by Ivan Razzhivin  on 21.06.2020.
//

#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <ctime>
#include <random>

using namespace std;
mutex mutex1;


void sclient(std::queue<std::vector<int>> customers)
{
    
    for (int i(1); !customers.empty(); i++)
    {
        
    
        mutex1.lock();
        std::cout << "Now on cashier person with " << customers.front().size() << " products in shopping basket" << " on " << std::this_thread::get_id() << " thread" << std::endl;
        mutex1.unlock();
        customers.pop();

    }

}


int main() 
{

    srand(time(NULL));
    std::vector<std::thread*> threads;
    std::queue<std::vector<int>> customers;
    std::vector<int> products;
    int const_customers = 1 + rand() % 5;
   

    std::cout << const_customers << " customers was in market today." << std::endl;


    for (int i(0); i < const_customers; i++)
    {
        int const_products = 1 + rand() % 15;
        for (int i(1); i <= const_products; ++i) // dlya dobalenyiya indeksa productov v ix vector
        {
            products.push_back(i); 
        }
        customers.push(products);
        products.clear();
        if ((customers.size() % 5 == 0) || (i == customers_amount - 1))
        {
            threads.push_back(new thread(sclient, customers));
            while (!customers.empty())
                customers.pop();
        }


    }

    for (auto& th : threads)
        th->join();


    return EXIT_SUCCESS;
}
