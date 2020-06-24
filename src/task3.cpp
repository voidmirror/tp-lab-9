#include <task3.h>

#include <thread>
#include <iostream>
#include <queue>
#include <list>
#include <mutex>
#include <condition_variable>

using namespace std;

class Cashbox;

list<Cashbox* > cashboxes;

class Cashbox {
private:
    mutex lockPrint;
    queue<vector<int> > q;
    bool canAdd = false;
    void printMessage(int x) {
        lockPrint.lock();
        cout << "Now working cashbox #:" << t->get_id() << " with item:" << x << '\n';
        lockPrint.unlock();
    }
    void addCustomerService(vector<int> &a) {
        if (finish) {
            return;
        }
        if (q.size() >= 5) {
            return;
        }
        q.push(a);
        canAdd = true;

    }
public:
    thread* t;
    bool finish = false;
    Cashbox(queue<vector<int> > &_q) {
        q = _q;
        t = new thread(&Cashbox::workWithCustomer, this);
    }
    void addCustomer(vector<int> &a, bool &added) {
        auto* adder = new thread(&Cashbox::addCustomerService, this, ref(a));
        adder->join();
        added = canAdd;
        canAdd = false;
        delete adder;
    }
    void workWithCustomer() {
        while (!finish) {
            if (!q.empty()) {
                for (auto &x: q.front()) {
                    printMessage(x);
                    this_thread::sleep_for(chrono::milliseconds(x));
                }
                q.pop();
            }
            else{
                finish = true;
            }
        }
    }
};


void add(vector<int> &a) {
    for(auto* x: cashboxes) {
        if(x->finish) x->t->join();
    }
    cashboxes.remove_if([](Cashbox* x) { return x->finish;});
    int check = false;
    for (auto* x: cashboxes) {
        bool add;
        x->addCustomer(a, add);
        if(add) {
            check = true;
            break;
        }
    }
    if(!check) {
        queue<vector<int> > q;
        q.push(a);
        auto* newCashbox = new Cashbox(q);

        cashboxes.push_back(newCashbox);
    }
}

void task3() {
    srand(time(0));
    for(int i = 0; i < 25; i++) {
        vector<int> w;
        w.resize((rand() % 5) + 1);
        for (auto &x: w) {
            x = rand() % 200;
        }
        add(w);
    }
    for(auto* x: cashboxes) {
        x->t->join();
    }
}
