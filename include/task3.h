#ifndef TASK_3_H
#define TASK_3_H

#include <thread>
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <mutex>

extern std::mutex mutex;

class Customer
{
private:
    unsigned int maxProductsNum = 5;
    double timeOfServe = 1;
    unsigned int products = 0;
public:
    Customer();
    ~Customer();
    unsigned int getProducts();
    void serve();
};

void service(std::queue<Customer*> var, size_t index);

#endif