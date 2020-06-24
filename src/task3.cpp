//
// Created by Anton Korkunov on 03/06/2020.
//
#define NN 100
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
//#include <zconf.h>
#include <queue>
#include <mutex>

using namespace std;

mutex mu;
bool visited=false;
bool EndofDay=false;

class Customer{
    vector<int> CostsOfGoods;
public:
    Customer()= default;
    void LetsBuySomething(){
        int n = rand() % 15;// number of goods
        for(int i=0; i<n; i++){
            CostsOfGoods.push_back( rand() % 2000);// prices
        }
    };
    int getCost(int k){
        return CostsOfGoods[k];
    }
    int getSize(){
        return CostsOfGoods.size();
    }
};

class Cash{
    queue<Customer*> QueueOfCustomers;
    bool isActive=false;
    size_t num;
public:
    Cash(int _num){
        isActive=false;
        num = _num;
    };
    void switchActive(){
        isActive=!isActive;
    }
    void AddCustomer(Customer* cus){
        QueueOfCustomers.push(cus);
    }
    int getsize(){
        return QueueOfCustomers.size();
    }
    void Service(){
        while(!EndofDay){//work until the end of day
            while(!QueueOfCustomers.empty()) {
                Customer *tmp = QueueOfCustomers.front();
                for (int i = 0; i < tmp->getSize(); i++) {
                    this_thread::sleep_for(chrono::milliseconds(rand() % 700));//cahsbox service delay
                    mu.lock();
                    cout << "this is cash num " << num << " |" << tmp->getCost(i) << " is done" << "\n";
                    mu.unlock();
                }
                QueueOfCustomers.pop();
            }
        }
    }

    bool Status(){
        return isActive;
    }
};

class Shop{
    vector<Cash*> cashmachines;
    vector<thread*> procs;
    int ccs=1;
public:
    Shop(){
        cashmachines.push_back(new Cash(1));
    }
    void LetTheFunBegin(){
        for(int n=0;n<NN;n++){
            visited = false;
            this_thread::sleep_for(chrono::milliseconds(rand() % 450));// customers entrance delay
            auto *tmpC = new Customer();
            tmpC->LetsBuySomething();
            for(int i=0; i<cashmachines.size(); i++){
                if(cashmachines[i]->getsize()<=5){
                    cashmachines[i]->AddCustomer(tmpC);
                    visited=true;
                    if(!cashmachines[i]->Status()){// dont make more threads
                        cashmachines[i]->switchActive();
                        procs.push_back(new thread(&Cash::Service,cashmachines[i]));
                    }
                    break;
                }
            }
            if(!visited){//new cash
                ccs++;
                auto* Cashtmp = new Cash(ccs);
                cashmachines.push_back(Cashtmp);
                Cashtmp->AddCustomer(tmpC);
                Cashtmp->switchActive();
                procs.push_back(new thread(&Cash::Service,Cashtmp));
            }
        }
        EndofDay=true;
        for (auto& t : procs) t->join();
    };
};

int main() {
    srand(time(0));
    Shop Walmart;
    Walmart.LetTheFunBegin();
    return 0;
}
