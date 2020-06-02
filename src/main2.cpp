//
// Created by Илья on 002 02.06.20.
//

#include <iostream>
#include <mutex>
#include <condition_variable>
#include "task2.h"
#include <thread>

using std::thread;
using std::cout;
using std::unique_lock;
using std::ref;
using std::ostream;
using std::endl;

int main(){
    mutex mut;
    condition_variable cv;
    bool step = false;
    bool printed = true;
    bool sorted = false;
    auto cmp = [](const string &a, const string &b) -> bool { return a < b; };
    vector<string> to_sort = {"aaa", "aab", "aa", "abbb", "bbbb", "cccb", "acb", "abc"};
    thread sorting(bubble_sort, ref(to_sort), cmp,
                   ref(mut), ref(cv), ref(step), ref(printed), ref(sorted));
    cv.notify_all();
    while(!sorted) {
        unique_lock<mutex> lk(mut);
        cv.wait(lk, [&step](){ return step; });
        step = false;
        for (auto& i : to_sort){
            cout << i << " ";
        }
        cout << endl;
        printed = true;
        lk.unlock();
        cv.notify_all();
    }
    sorted = false;
    sorting.join();
    return 0;
}