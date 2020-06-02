//
// Created by Илья on 002 02.06.20.
//

#include "../include/task3.h"
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>


void Shop::work(queue<int> *queue, mutex& mut) {
    while (!queue->empty()) {
        // serve customer
        for (int i = 0; i < queue->front(); i++) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "Product was paid" << endl;
        }
        lock_guard<mutex> lock(mut);
        queue->pop();
    }
}


Shop::Shop(int max_customers) {
    this->max_customers = max_customers;
    cash_registers = {};
}

vector<cashRegister>& Shop::get_cash_registers(){
    return cash_registers;
}

void Shop::updateRegisters() {
    if (!cash_registers.empty()) {
        auto newEnd = remove_if(cash_registers.begin(), cash_registers.end(),
                                [](cashRegister curr) {
                                         if (curr.get_customers_queue()->empty()) {
                                             cout << "empty cash register -> close it (delete)" << endl;
                                             delete curr.get_customers_queue();
                                             delete curr.get_cash_thread();
                                             return true;
                                         }
                                         return false;
                                     });
        cash_registers.erase(newEnd, cash_registers.end());
    }
}


void Shop::addCustomer(int product_number, mutex& mut) {
    bool is_added = false;
    updateRegisters();
    for (cashRegister curr : cash_registers) {
        if (curr.get_customers_queue()->size() < max_customers) {
            lock_guard<mutex> lock(mut);
            curr.get_customers_queue()->push(product_number);
            is_added = true;
            break;
        }
    }
    if (!is_added) {
        lock_guard<mutex> lock(mut);
        cashRegister last;
        cout << "too many customers -> open new cash register (create)" << endl;
        last.get_customers_queue()->push(product_number);
        last.set_cash_thread(new thread(work, last.get_customers_queue(), ref(mut)));
        last.get_cash_thread()->detach();
        cash_registers.push_back(last);
    }
}