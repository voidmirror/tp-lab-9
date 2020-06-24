//
// Created by artem on 6/7/20.
//

#ifndef CLAB9_TASK3_H
#define CLAB9_TASK3_H
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <deque>
#include <chrono>
#include <algorithm>
#include "Shopping.cpp"

void task3Tests(){
    Market market;

    for (auto i = 0 ; i < 25; i++){
        market.newClient(new Client(5));
        std::this_thread::sleep_for(std::chrono::milliseconds(random() % 3000));
    }

    getchar();
}

int main() {
    task3Tests();
}

#endif //CLAB9_TASK3_H