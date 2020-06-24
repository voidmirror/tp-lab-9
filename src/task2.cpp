//
// Created by Оксана on 03.06.2020.
//
#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>

using namespace std;

mutex mtx;
condition_variable cv;
bool printed = false, sorted = true, ended = false;

void printArray(vector<string>& a)
{
    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
}


void bubble_sort(vector<string> & arr, bool cmp(const string &, const string &))
{
    for (size_t i = 0; i < arr.size(); i ++){
        unique_lock <mutex> lock(mtx);
        cv.wait(lock, []{ return printed;});
        for (size_t j = 0; j < arr.size() - i - 1; j ++){
            if (cmp(arr[j], arr[j + 1])){
                swap (arr[j], arr[j + 1]);
            }
        }
        sorted = true;
        printed = false;
        lock.unlock();
        cv.notify_all();
    }
    ended = true;
}

int main(){
    vector<string> mas = {"one", "two", "free", "four", "five", "six", "seven"};
    thread t = thread(bubble_sort, ref(mas), [](const string & a, const string & b){return a.size() > b.size();});
    while (!ended){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return sorted;});
        sorted = false;
        printArray(mas);
        printed = true;
        lock.unlock();
        cv.notify_all();
    }
    t.join();
    return 0;
}
