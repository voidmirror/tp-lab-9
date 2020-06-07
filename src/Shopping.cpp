//
// Created by artem on 6/7/20.
//

#include <mutex>
#include <deque>
#include <chrono>
#include <algorithm>
#include <vector>
#include <iostream>
#include <thread>

class Client {
    std::vector<int> cart;
public:
    explicit Client(std::size_t max_cart_size) {
        for (auto i = 0; i < 1 + random() % max_cart_size; i++) {
            cart.push_back(1);
        }
    }
    ~Client() {
        std::cout << "Покупатель обслужен" << std::endl;
        cart.clear();
    }

    bool serveProduct() {
        if (cart.empty()) {
            return false;
        }
        cart.pop_back();
        return true;
    }

};

class Market;

class Register {
private:
    std::mutex simpleMutex;
    std::deque<Client *> checkoutQueue;

    static void serve(std::deque<Client *> &checkout_queue, std::mutex &mutex) {
        while (true) {
            while (!checkout_queue.empty()) {
                while (checkout_queue.front()->serveProduct()) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "Товар пробит на кассе ровно в: " << std::this_thread::get_id() << std::endl;
                }
                mutex.lock();
                delete checkout_queue.front();
                checkout_queue.pop_front();
                mutex.unlock();
            }
            mutex.lock();
            if (checkout_queue.empty()) {
                mutex.unlock();
                return;
            }
            mutex.unlock();
        }
    }

public:
    explicit Register(Client *client) {
        checkoutQueue.push_back(client);
        std::thread t(serve, ref(checkoutQueue), ref(simpleMutex));
        t.detach();
    }

    ~Register() {
        std::cout << "Касса закрыта" << std::endl;
        for (auto x : checkoutQueue) {
            delete x;
        }
        checkoutQueue.clear();
    }

    bool addNewCustomer(Client *client) {
        if (!isDone() && (checkoutQueue.size() < 5) && simpleMutex.try_lock()) {
            checkoutQueue.push_back(client);
            simpleMutex.unlock();
            return true;
        }
        return false;
    }

    bool isDone() const {
        return checkoutQueue.empty();
    }

};

class Market {
private:
    std::vector<Register *> registers;
public:
    void newClient(Client *client) {
        bool endReached = false;
        for (auto it = registers.begin(); it != registers.end();) {
            if ((*it)->isDone()) {
                delete *it;
                it = registers.erase(it);
            } else if ((*it)->addNewCustomer(client)) {
                endReached = true;
                break;
            } else {
                it++;
            }
        }
        if (!endReached) {
            registers.push_back(new Register(client));
        }
    }
};