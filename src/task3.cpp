#include <random>
#include "../include/task3.h"
#include <string>
#include <iostream>

bool shopClosed = false;
condition_variable queueNotEmptyCond;

int getRandInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

/*---------consumer----------*/
void Consumer::takeOutProduct() {
    products.pop();
}

void Consumer::putProduct() {
    products.push(getRandInt(1, 100));
}

void Consumer::getInQueue() {
    CashBox * cashBox = shop->getCurrentCashbox();
    cashBox->pushInQueue(this);
}

void Consumer::fillCart() {
    int cartSize = getRandInt(1, 10);
    for (int i = 0; i < cartSize; ++i) {
        putProduct();
    }
}

bool Consumer::cartIsEmpty() {
    return products.empty();
}

Consumer::Consumer(Shop *shop) : shop(shop) {
    this->shop = shop;
}

/*---------------------------*/

/*----------cashbox----------*/

void CashBox::serve(Consumer * consumer) const {
    while (!consumer->cartIsEmpty()) {
        consumer->takeOutProduct();
        cout << "Product sold at the cashbox №" << id << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    delete consumer;
}

void CashBox::pushInQueue(Consumer * consumer) {
    if (!isFull()) {
        {
            lock_guard<mutex> lock(cashboxQueueMutex);
            queue.push_back(consumer);
        }
    }
    queueNotEmptyCond.notify_all();
}

bool CashBox::isFull() const {
    return queue.size() == queueLimit;
}

void CashBox::launch() {
    cout << "Cashbox №" << id << " has been opened" << endl;

    while (true) {
        if (isFull()) {
            toBeClosed = true;
        }

        Consumer *currentConsumer;
        {
            unique_lock<mutex> lock(cashboxQueueMutex);
            queueNotEmptyCond.wait(lock, [&]() { return !queue.empty() || shopClosed; });
            if (queue.empty()) {
                break;
            }
            currentConsumer = queue.front();
            queue.pop_front();
        }
        serve(currentConsumer);
        cout << "consumer served" << endl;

        if ((toBeClosed && queue.empty())) {
            break;
        }
    }

    cout << "Cashbox №" << id << " has been closed" << endl;
}

CashBox::CashBox(int id) {
    t = new std::thread(&CashBox::launch, this);
    this->id = id;
}

thread *CashBox::getThread() const {
    return t;
}

CashBox::~CashBox() {
    queue.clear();
}

/*---------------------------*/

/*-----------shop------------*/


CashBox * Shop::getCurrentCashbox() const {
    return currentCashbox;
}

void Shop::openShop() {
    cout << "Shop is working now" << endl;

    openNewCashbox(cashBoxCounter);

    for (int i = 0; i < 10; ++i) {
        auto * consumer = new Consumer(this);
        consumer->fillCart();
        if (currentCashbox->isFull()) {
            openNewCashbox(cashBoxCounter);
        }
        consumer->getInQueue();
        this_thread::sleep_for(chrono::milliseconds(getRandInt(1000, 3000)));
    }

    shopClosed = true;
    queueNotEmptyCond.notify_all();

    for (auto cashbox: cashboxes) {
        cashbox->getThread()->join();
    }
}

void Shop::openNewCashbox(int cashBoxId) {
    currentCashbox = new CashBox(cashBoxId);
    cashboxes.push_back(currentCashbox);
    cashBoxCounter += 1;
}

Shop::~Shop() {
    for(auto cashbox: cashboxes) {
        delete cashbox;
    }
    cashboxes.clear();
}

/*---------------------------*/