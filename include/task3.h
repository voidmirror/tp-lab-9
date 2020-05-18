
#ifndef FUNCS_THREADS_TASK3_H
#define FUNCS_THREADS_TASK3_H

#include <vector>
#include <string>
#include <thread>
#include <deque>
#include <stack>
#include <mutex>
#include <condition_variable>


using namespace std;

class Shop;
class Consumer {
private:
    stack<int> products;
    Shop * shop;
private:
    void putProduct();
public:
    explicit Consumer(Shop *shop);
public:
    void takeOutProduct();
    void getInQueue();
    void fillCart();

    bool cartIsEmpty();
};


class CashBox {
private:
    int id;
    thread * t;
private:
    mutex cashboxQueueMutex;
    int queueLimit = 5;
    deque<Consumer *> queue;
    bool toBeClosed = false;
public:
    explicit CashBox(int id);

    virtual ~CashBox();

    void launch();

public:
    void pushInQueue(Consumer *);
    void serve(Consumer * consumer) const;
    bool isFull() const;
    thread *getThread() const;
};


class Shop {
private:
    vector<CashBox *> cashboxes;
    CashBox * currentCashbox;
    int cashBoxCounter = 1;
private:
    void openNewCashbox(int cashBoxId);
public:
    virtual ~Shop();
public:
    CashBox * getCurrentCashbox() const;
    void openShop();
};


int getRandInt(int min, int max);


#endif //FUNCS_THREADS_TASK3_H
