#ifndef SHOP_H
#define SHOP_H
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <unistd.h>

class Buyer{
    public:
        Buyer();
        std::vector<int> cart;
};
class Shop
{
    public:
        Shop();
        virtual ~Shop();
        void openDoors();
    protected:

    private:
        std::vector<std::queue<Buyer>*>queues;
        std::vector<std::thread*> servants;
        void createServant(int queueNum);
};

#endif // SHOP_H
