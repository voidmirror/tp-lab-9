//
// Created by Илья on 002 02.06.20.
//
#include "task3.h"
using std::endl;


int main() {
    srand(time(nullptr));
    Shop shop(10);
    mutex mut;
    int number_of_iters = 15;
    for (int i = 0; i < number_of_iters; i++) {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(rand() % 3000));
        shop.addCustomer(rand() % 5, mut);
        for (auto current_register : shop.get_cash_registers()) {
            std::cout << "Current cash register: number of customers = " <<
                          current_register.get_customers_queue()->size() << std::endl;
        }
        std::cout << endl << endl;
    }
    return 0;
}