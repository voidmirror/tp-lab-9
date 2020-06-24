#ifndef LAB9_TASK3_H
#define LAB9_TASK3_H

#include <vector>
#include <queue>
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>

#define MAX_CUSTOMERS 5
#define CUSTOMERS_AMOUNT 20
#define MAX_GOODS 10
#define DELAY 10


class Customer{
private:
    std::vector<int> goods;
    int customerID;
public:
    explicit Customer(int ID);

    void addGoodsToCustomer();
    std::vector<int> getGoodsOfCustomer();
    void setCustomerID(int ID);
    int getCustomerID();
};

void payingForGoods(std::queue<Customer*> customers, int threadNumber);
void shopService();

#endif //LAB9_TASK3_H
