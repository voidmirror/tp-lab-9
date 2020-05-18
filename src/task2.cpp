#include "task2.h"

void sort(std::vector<std::string> &var,  bool comp(const std::string a, const std::string b))
{
    for (size_t i = 0; i < var.size()-1; i++)
    {
        for (size_t j = 0; j < var.size()-i-1; j++)
        {
            mutex.lock();
            if (comp(var[j], var[j+1]))
            {
                std::swap(var[j], var[j+1]);
                print = true;
            }
            mutex.unlock();
        }
    }
    resume = false;
}

