//
// Created by Илья on 002 02.06.20.
//

#ifndef TASK1_TASK3_H
#define TASK1_TASK3_H
#include "../include/task3.h"
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>

using std::queue;
using std::vector;
using std::mutex;
using std::thread;
using std::cout;
using std::endl;
using std::lock_guard;


class cashRegister{
private:
    queue<int>* customers_queue;
    thread* cash_thread;
public:
    cashRegister(): customers_queue(new queue<int>){};
    queue<int>* get_customers_queue(){ return customers_queue; }
    thread* get_cash_thread() { return cash_thread; }
    void set_cash_thread(thread* new_thread) { cash_thread = new_thread; };
};

class Shop{
private:
    vector<cashRegister> cash_registers;
    size_t max_customers;
public:
    Shop(int);
    void updateRegisters();
    void addCustomer(int, mutex&);
    vector<cashRegister>& get_cash_registers();
    static void work(queue<int> *queue, mutex&);
};
#endif //TASK1_TASK3_H
