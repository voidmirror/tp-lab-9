#define TASK 3

#if TASK == 1

#include "task1.h"
#include <iostream>

int main()
{
    // TASK_1 
    
    std::vector<std::string> var = {"aaa", "bbbb", "aa", "c", "a", "ddddd"};
    std::vector<std::string> res;
    
    res = sortByAscendingLength(var);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }
    
    res = sortByDescendingLength(var);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }
    
    res = sortByAscending(var);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }
    
    res = sortByDescending(var);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }
    
    res = sortByAscendingLastCharacters(var);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }
    
    res = sortByDescendingLastCharacters(var);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }
    
    return 0;
}

#elif TASK == 2

#include "task2.h"

int main()
{
    //TASK_2

    std::vector<std::string> var = {"aaa", "bbbb", "aa", "c", "a", "ddddd"};

    std::thread thread(sort, std::ref(var), [](const std::string a, const std::string b){ return a > b;});
    
    while (resume)
    {
        if (print)
        {
            mutex.lock();
            for (size_t i = 0; i < var.size();i++)
            {
                std::cout<<var[i]<< " ";
            }
            std::cout << std::endl;
            print = false;
            mutex.unlock();
        }
    }

    thread.join();

    return 0;
}

#elif TASK == 3

#include "task3.h"

int main()
{
    size_t customerNum = 13;
    size_t maxQueueLength = 5;
    size_t n = 0;
    std::vector<std::thread*> threads;
    std::queue<Customer*> customer_queue;
    
    for (size_t i = 0; i < customerNum; i++)
    {
        //std::cout<<i<<std::endl;
        customer_queue.push(new Customer());
        if (customer_queue.size() % maxQueueLength == 0 || i == customerNum - 1)
        {
            //std::cout<<i<< " "<< customer_queue.size()<< " " << threads.size()<<std::endl;
            n = threads.size();
            threads.push_back(new std::thread( service, std::ref(customer_queue), n ));
            //while (!customer_queue.empty())
            //{
            //   customer_queue.pop();
            //}
            
        }
    }

    std::cout<< threads.size()<<std::endl;
    
    for (auto &th : threads)
    {
       std::cout<<" <<====>> "<<std::endl;
        th->join();
    }

    return 0;
}

#endif