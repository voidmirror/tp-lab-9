#ifndef CLAB9_TASK2_H
#define CLAB9_TASK2_H
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex readMutex;
mutex iterateMutex;
void TASK2BubleSort(vector<string> & vec, bool comparator(const string& a, const string& b), bool & stop) {
    int len = vec.size();
    for (int i = 0; i < len; i++) {
        iterateMutex.lock();
        for (int j = 0; j < len - i - 1; j++)
            if (!comparator(vec[j], vec[j + 1])) {
                swap(vec[j], vec[j + 1]);
            }
        readMutex.unlock();
    }
    stop = true;
}

void task2(){
    vector <string> stringvec = { "123456", "12345", "1234", "123", "12", "1" };
    auto comparator = [](const string& a, const string& b) -> bool {return a.size() < b.size(); };

    bool stop = false;

    thread t(TASK2BubleSort, ref(stringvec), comparator, ref(stop));
    readMutex.lock();
    while(!stop){

        for (const string& s: stringvec){
            cout << s << " ";
        }
        cout << endl;

        readMutex.lock();

        iterateMutex.unlock();
    }
    t.join();
}

#endif //CLAB9_TASK2_H
