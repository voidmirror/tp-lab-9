#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

unsigned int QUEUE_SIZE = 5;
unsigned int PRODUCTS = 10;

class Customer {
private:
    vector<int> products;
public:
    Customer() {
        for (int i = 0; i < rand() % PRODUCTS + 1; i++) {
            products.push_back(1);
        }
    }

    ~Customer() {
        cout << "Customer bought " << products.size() << " products in line number " << this_thread::get_id() << endl;
    }

    void serve() {
        for (int i = 0; i < products.size(); i++) {
            cout << "Product " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};


class Register {
private:
    mutex mutex1;
    deque<Customer *> customer_queue;

    static void registerServe(deque<Customer *> &customer_queue, mutex &mutex1) {
        int products;
        while (true) {
            while (!customer_queue.empty()) {
                customer_queue.front()->serve();
                mutex1.lock();
                delete customer_queue.front();
                customer_queue.pop_front();
                mutex1.unlock();
            }
            mutex1.lock();
            if (customer_queue.empty()) {
                mutex1.unlock();
                return;
            }
            mutex1.unlock();
        }
    }

public:
    explicit Register(Customer *new_cust) {
        customer_queue.push_back(new_cust);
        thread t(registerServe, ref(customer_queue), ref(mutex1));
        t.detach();
    }

    ~Register() {
        cout << "Checkout closing" << endl;
        for (auto i: customer_queue) {
            delete i;
        }
        customer_queue.clear();
    }

    bool addCustomer(Customer *new_cust) {
        if ((!Closed()) && (customer_queue.size() < QUEUE_SIZE)) {
            mutex1.lock();
            customer_queue.push_back(new_cust);
            mutex1.unlock();
            return true;
        }
        return false;
    }

    bool Closed() {
        return customer_queue.empty();
    }
};


class Shop {
private:
    vector<Register *> registers;

public:
    void NewCustomer(Customer *new_customer) {
        bool fl = false;
        for (int i = registers.size() - 1; i >= 0; i--) {
            if ((registers[i])->Closed()) {
                delete (registers[i]);
                registers.erase(registers.begin() + i);
            } else if ((registers[i])->addCustomer(new_customer)) {
                fl = true;
                break;
            }
        }
        if (!fl) {
            registers.push_back(new Register(new_customer));
        }
    }
};


int main() {
    Shop shop;
    srand(time(nullptr));
    for (auto i = 0; i < 10000; i++) {
        shop.NewCustomer(new Customer());
        this_thread::sleep_for(chrono::seconds(rand() % 2));
    }
    return 0;
}