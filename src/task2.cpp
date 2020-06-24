
#include "../include/task2.h"
#include <mutex>
#include <condition_variable>
#include <iostream>

mutex mx;
condition_variable stepFinishedCondition;
condition_variable printingFinishedCondition;

int step = 0;
bool stepFinished = false;
bool sortingFinished = false;
bool printed = false;

void sorted(vector<string> & strings, const function<bool(string, string)>& comparator) {
    cout << "sorting..." << endl;
    unique_lock<mutex> lock(mx);
    for (int i = 0; i < strings.size() - 1; ++i) {
        for (int j = 0; j < strings.size() - 1; ++j) {
            if (comparator(strings[j], strings[j + 1])) {
                swap(strings[j], strings[j + 1]);
            }
        }
        step += 1;
        cout << step << endl;
        stepFinished = true;
        printed = false;
        stepFinishedCondition.notify_one();
        printingFinishedCondition.wait(lock, [](){return printed;});
    }
    stepFinished = true;
    sortingFinished = true;

    stepFinishedCondition.notify_one();
}

void logProcess(const vector<string>& strings) {
    unique_lock<mutex> lock(mx);
    while (true) {
        stepFinishedCondition.wait(lock, [](){return stepFinished;});
        if (sortingFinished) {
            break;
        }
        for (const string& str : strings) {
            cout << str << " ";
        }
        cout << endl;

        stepFinished = false;
        printed = true;

        printingFinishedCondition.notify_one();
    }
}