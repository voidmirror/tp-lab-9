//
//  task3.h
//  finalLab
//
//  Created by Олеся Мартынюк on 23.05.2020.
//  Copyright © 2020 Olesia Martinyuk. All rights reserved.
//

#ifndef task3_h
#define task3_h

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <chrono>

#define MAX_CUSTOMER_NUM 5
#define MAX_GOODS_NUM 10
#define SLEEP_TIME 10

using namespace std;

mutex mut;

class Customer {
private:
    vector<int> goods = {};
    int customerID;
public:
    Customer(int ID){
        this->customerID = ID;
        srand(static_cast<unsigned int>(time(nullptr)));
        int goodsAmount = rand() % MAX_GOODS_NUM + 1;
        for (int i = 0; i < MAX_GOODS_NUM; i++) {
            this->goods.push_back(rand() % goodsAmount);
        }
    }
    vector<int> getGoods(){
        return this->goods;
    }
    int getID(){
        return this->customerID;
    }
};

void checkout(queue<Customer*> customers, int threadNum) {
    while (!customers.empty()) {
        Customer* cust = customers.front();
        for (int i = 0; i < cust->getGoods().size(); i++) {
            mut.lock();
            std::thread::id this_id = std::this_thread::get_id();
            cout << "Thread: " << this_id << " (" << threadNum << ") | Customer: " << cust->getID() << " | Goods ID: " << cust->getGoods()[i] << endl;
            mut.unlock();
            this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
        }
        customers.pop();
    }
}


#endif /* task3_h */
