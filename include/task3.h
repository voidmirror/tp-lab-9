#ifndef CLAB9_TASK3_H
#define CLAB9_TASK3_H
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <deque>
#include <chrono>
#include <algorithm>
using namespace std;

class Customer{
    vector <int> cart;
public:
    explicit Customer(std::size_t max_cart_size)
    {
        for (auto i = 0; i < 1 + random() % max_cart_size; i++){
            cart.push_back(1);
        }
    }
    ~Customer(){
        cout << "покупатель обслужен" << endl;
        cart.clear();
    }
    bool serveProduct() {
        if (cart.empty()){
            return false;
        }
        cart.pop_back();
        return true;
    }

};
class Shop;
class Register {
private:
    mutex m;
    deque <Customer* > checkout_queue;

    static void serve(deque<Customer*>& checkout_queue, mutex& m){
        while (true){
            while (!checkout_queue.empty()) {
                while (checkout_queue.front() -> serveProduct()) {
                    this_thread::sleep_for(chrono::seconds(1));
                    cout << "товар пробит на кассе: " << this_thread::get_id() << endl;
                }
                m.lock();
                delete checkout_queue.front();
                checkout_queue.pop_front();
                m.unlock();
            }
            m.lock();
            if (checkout_queue.empty()){
                m.unlock();
                return;
            }
            m.unlock();
        }
    }

public:
    explicit Register(Customer* c){
        checkout_queue.push_back(c);
        thread t( serve, ref(checkout_queue), ref(m));
        t.detach();
    }

    ~Register(){
        cout << "касса закрыта" << endl;
        for ( auto x : checkout_queue){
            delete x;
        }
        checkout_queue.clear();
    }
    bool addNewCustomer(Customer* c){
        if (!isDone() && (checkout_queue.size() < 5) && m.try_lock()){
            checkout_queue.push_back(c);
            m.unlock();
            return true;
        }
        return false;
    }

    bool isDone () const {
        return checkout_queue.empty();
    }

};

class Shop{
private:
    vector< Register *> registers;
public:
    void NewCustomer(Customer* customer){
        bool endReached = false;
        for (auto it = registers.begin(); it != registers.end();){
            if ((*it)->isDone()){
                delete *it;
                it = registers.erase(it);
            } else if ((*it) -> addNewCustomer(customer)){
                endReached = true;
                break;
            }else{
                it++;
            }
        }
        if (!endReached){
            registers.push_back(new Register(customer));
        }
    }
};

void task3(){
    Shop shop;
    for (auto i = 0 ; i < 50; i++){
        shop.NewCustomer(new Customer(5));
    }
    getchar();
}

#endif //CLAB9_TASK3_H
