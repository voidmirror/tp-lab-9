//
// Created by Оксана on 03.06.2020.
//
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>

using namespace std;

#define MAX_CLIENTS 20
#define MAX_QUEUE 5

mutex mtx;

class Client
{
private:
    vector<int> goods;
public:
    Client()
    {
        int numGoods = rand() % 10 + 3;
        for (int i = 0; i < numGoods; i++)
        {
            goods.push_back(rand() % 40 + 10);
        }
    }
    vector<int> getGoods()
    {
        return goods;
    }

};

class Queue
{
private:
    //int max_customers = 5;
    int size = 0;
    queue<Client*> clients;
public:
    Queue() {};

    void addClient(Client* cl)
    {
        clients.push(cl);
        size++;
    }

    int getsize()
    {
        return size;
    }

    void serveClient()
    {

        while (!clients.empty())
        {
            Client* cl = clients.front();
            for (auto prod : cl->getGoods())
            {
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            mtx.lock();
            cout << "Customer service with " << cl->getGoods().size() << " items in the cashbox " << this_thread::get_id() << endl;
            mtx.unlock();
            delete clients.front();
            clients.pop();
        }
    }
};

class Shop
{
private:
    vector<thread*> threads;
    vector<Queue*> queues;
public:
    Shop()
    {
        queues.push_back(new Queue);
        for (size_t i = 0; i < MAX_CLIENTS; i++)
        {
            Client* cl = new Client;
            if (queues.back()->getsize() < MAX_QUEUE)
                queues.back()->addClient(cl);
            else
            {
                threads.push_back(new thread(&Queue::serveClient, *(queues.back())));
                queues.push_back(new Queue);
                queues.back()->addClient(cl);
            }
        }
        threads.push_back(new thread(&Queue::serveClient, *(queues.back())));
        for (auto t : threads)
            t->join();
    }

    ~Shop()
    {
        for (auto t : threads)
            delete t;
        for (auto ch : queues)
            delete ch;
    }
};

int main()
{
    Shop* my_shop = new Shop();
    my_shop->~Shop();
    return 0;
}