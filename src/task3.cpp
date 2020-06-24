#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
unsigned int MAX_PROD = 10;
unsigned int MAX_QUEUE = 5;

class Customer {
private:
    vector <int> products;
public:
    Customer() {
        for (int i = 0; i < rand() % MAX_PROD + 1; i++) {
            products.push_back(1);
        }
    }
    ~Customer() {
        cout << "Customer was served by thread " << this_thread::get_id() << endl;
    }
    void serve() {
        for (int i = 0; i < products.size(); i++) {
            cout << "Product was sold in thread " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
};

class Register {
private:
    mutex mut;
    deque <Customer*> customers;

    static void registerServe(deque<Customer*>& customers, mutex& m) {
        int products;
        while (true) {
            while (!customers.empty()) {
                customers.front()->serve();
                m.lock();
                delete customers.front();
                customers.pop_front();
                m.unlock();
            }
            m.lock();
            if (customers.empty()) {
                m.unlock();
                return;
            }
            m.unlock();
        }
    }

public:
    explicit Register(Customer* newcust) {
        customers.push_back(newcust);
        thread t(registerServe, ref(customers), ref(mut));
        t.detach();
    }

    ~Register() {
        cout << "Closed" << endl;
        for (auto i : customers) {
            delete i;
        }
        customers.clear();
    }

    bool addCustomer(Customer* newcust) {
        if ((!Closed()) && (customers.size() < MAX_QUEUE)) {
            mut.lock();
            customers.push_back(newcust);
            mut.unlock();
            return true;
        }
        return false;
    }

    bool Closed() {
        return customers.empty();
    }
};

class Shop {
private:
    vector <Register*> registers;

public:
    void NewCustomer(Customer* newcust) {
        bool fl = false;
        for (int i = registers.size() - 1; i >= 0; i--) {
            if ((registers[i])->Closed()) {
                delete (registers[i]);
                registers.erase(registers.begin() + i);
            }
            else if ((registers[i])->addCustomer(newcust)) {
                fl = true;
                break;
            }
        }
        if (!fl) {
            registers.push_back(new Register(newcust));
        }
    }
};

int main() {
    Shop newShop;
    srand(time(nullptr));
    for (auto i = 0; i < 10000; i++) {
        newShop.NewCustomer(new Customer());
        this_thread::sleep_for(chrono::seconds(rand() % 3+1));
    }
    return 0;
}