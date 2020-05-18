#define TASK 2

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

#else if TASK == 2

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

#endif