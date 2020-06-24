//
// Created by Илья on 002 02.06.20.
//

#ifndef TASK1_TASK2_H
#define TASK1_TASK2_H

#include <thread>
#include <vector>
#include <condition_variable>

using std::condition_variable;
using std::vector;
using std::string;
using std::mutex;

void bubble_sort(vector<string> &a, bool cmp(const string& a, const string& b), mutex& mut, condition_variable& cv,
                 bool& step, bool& printed, bool& sorted);


#endif //TASK1_TASK2_H
