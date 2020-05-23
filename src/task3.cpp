//
// Created by Илья Соловьёв on 23.05.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>


const int MAX_CUSTOMERS = 4;
const int MAX_PRODUCTS = 10;
std::mutex mutex;

struct cashRegister {
    std::queue<int> *queue;
    std::thread *thread;

    cashRegister() {
        queue = new std::queue<int>;
    }
};

void serveCustomer(int numOfProducts) {
    for (int i = 0; i < numOfProducts; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Product done " << std::this_thread::get_id() << std::endl;
    }
}

void work(std::queue<int> *queue) {
    while (!queue->empty()) {
        serveCustomer(queue->front());
        std::lock_guard<std::mutex> lock(mutex);
        queue->pop();
    }
}

struct Shop {
    std::vector<cashRegister> registers;

    Shop() {
        registers = {};
    }

    void updateRegisters() {
        if (!registers.empty()) {
            auto newEnd = std::remove_if(registers.begin(), registers.end(),
                                         [](cashRegister curr) {
                                             if (curr.queue->empty()) {
                                                 std::cout << "delete" << std::endl;
                                                 delete curr.queue;
                                                 delete curr.thread;
                                                 return true;
                                             }
                                             return false;
                                         });
            registers.erase(newEnd, registers.end());
        }
    }

    void addCustomer(int numOfProducts) {
        bool is_added = false;
        updateRegisters();
        for (cashRegister curr : registers) {
            if (curr.queue->size() < MAX_CUSTOMERS) {
                std::lock_guard<std::mutex> lock(mutex);
                curr.queue->push(numOfProducts);
                is_added = true;
                break;
            }
        }
        if (!is_added) {
            std::lock_guard<std::mutex> lock(mutex);
            cashRegister last;
            std::cout << "create" << std::endl;
            last.queue->push(numOfProducts);
            last.thread = new std::thread(work, last.queue);
            //last.thread->join();
            last.thread->detach();
            registers.push_back(last);
        }
    }
};

int main() {
    srand(time(nullptr));
    Shop shop;
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(rand() % 3000));
        shop.addCustomer(rand() % MAX_PRODUCTS);
        for (auto curr : shop.registers) {
            std::cout << curr.queue->size() << std::endl;
        }
        std::cout << "------------------------\n";
    }
    getchar();
    return 0;
}

