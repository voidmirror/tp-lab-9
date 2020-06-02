//
// Created by Илья on 002 02.06.20.
//

#include <iostream>
#include "task2.h"
#include <mutex>
#include <condition_variable>


void bubble_sort(vector<string> &a, bool cmp(const string& a, const string& b), mutex& mut, condition_variable& cv,
        bool& step, bool& printed, bool& sorted) {
    size_t n = a.size();
    for (size_t i = 0; i < n; i++) {
        std::unique_lock<mutex> lk(mut);
        cv.wait(lk, [&printed](){ return printed; });
        for (size_t j = 0; j < n - 1; j++) {
            if (!cmp(a[j], a[j + 1])) {
                std::swap(a[j], a[j + 1]);
            }
        }
        step = true;
        printed = false;
        lk.unlock();
        cv.notify_all();
    }
    sorted = true;

}