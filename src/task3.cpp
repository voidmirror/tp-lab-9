//
// Created by aklen on 23.05.2020.
//
#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>


using namespace std;

unsigned int MAX_PRODUCTS = 10;
unsigned int MAX_QUEUE_SIZE = 5;


class Customer{
private:
    vector <int> products;

public:
    Customer(){
        for(int i = 0; i < rand()%MAX_PRODUCTS + 1; i++){
            products.push_back(1);
        }
    }
    ~Customer(){
        cout<<"Customer with "<<products.size()<<" products was served by "<<this_thread::get_id()<<endl;
    }
    void serve() {
        for(int i = 0; i < products.size(); i++){
            cout<<"Product is done "<<this_thread::get_id()<<endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};


class Register{
private:
    mutex m;
    deque <Customer*> cust_queue;

    static void registerServe(deque<Customer*> &cust_queue, mutex &m){
        int products;
        while(true){
            while(!cust_queue.empty()){
                cust_queue.front()->serve();
                m.lock();
                delete cust_queue.front();
                cust_queue.pop_front();
                m.unlock();
            }
            m.lock();
            if(cust_queue.empty()){
                m.unlock();
                return;
            }
            m.unlock();
        }
    }

public:
    explicit Register(Customer* new_cust){
        cust_queue.push_back(new_cust);
        thread t(registerServe, ref(cust_queue), ref(m));
        t.detach();
    }

    ~Register(){
        cout<<"Checkout closing"<<endl;
        for(auto i: cust_queue){
            delete i;
        }
        cust_queue.clear();
    }

    bool addCustomer(Customer* new_cust){
        if((!Closed())&&(cust_queue.size() < MAX_QUEUE_SIZE)){
            m.lock();
            cust_queue.push_back(new_cust);
            m.unlock();
            return true;
        }
        return false;
    }

    bool Closed(){
        return cust_queue.empty();
    }
};


class Shop{
private:
    vector <Register*> registers;

public:
    void NewCustomer(Customer* new_cust){
        bool fl = false;
        for(int i = registers.size()-1; i >= 0; i--){
            if((registers[i])->Closed()){
                delete (registers[i]);
                registers.erase(registers.begin()+i);
            }
            else if ((registers[i])->addCustomer(new_cust)){
                fl = true;
                break;
            }
        }
        if(!fl){
            registers.push_back(new Register(new_cust));
        }
    }
};


int main(){
    Shop s;
    srand(time(nullptr));
    for(auto i = 0; i < 10000; i++){
        s.NewCustomer(new Customer());
        this_thread::sleep_for(chrono::seconds(rand() % 3));
    }
    return 0;
}