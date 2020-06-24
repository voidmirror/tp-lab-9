#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

bool printing = false, procced = true, finished = false;
mutex mx2;
condition_variable cvar;

void sortBuble2(vector<string>* v, function<bool(string, string)> f) {
    int vec_size = v->size();
    vector<string>& vec = *v;
    string tmp;
    for (int i = 0; i < vec_size; i++) {
        unique_lock<mutex> lk(mx2);
        cvar.wait(lk, [] {return (printing); });
        for (int j = 0; j < (vec_size - i - 1); j++) {
            if (f(vec[j], vec[j + 1])) {
                tmp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = tmp;
            }
        }
        procced = true;
        printing = false;
        cout << endl;
        lk.unlock();
        cvar.notify_all();
    }
    finished = true;
}


void print2(vector<string>& vec) {
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}


int main() {
    vector<string> v = { "Ivan", "Petya", "Koly", "Dima", "Misha" };
    thread t(sortBuble2, &v, [](string a, string b) {return (a.size() < b.size()); });
    while (true) {
        unique_lock<mutex> lk(mx2);
        cvar.wait(lk, [] {return (procced); });
        if (finished) {
            break;
        }
        procced = false;
        print2(v);
        printing = true;
        lk.unlock();
        cvar.notify_all();
    }
    t.join();
    return 0;
}