#include "Shop.h"
Buyer::Buyer(){
    bool enough = false;
    while(!enough){
        cart.push_back(rand() % 1000);
        if(rand() % 6 == 1 || cart.size() > 100){
            enough = true;
        }
    }
}
Shop::Shop()
{
    queues = *(new std::vector<std::queue<Buyer>*>());
    servants = *(new std::vector<std::thread*>());
}

Shop::~Shop()
{
    //dtor
}

void checkout(std::queue<Buyer>& queue){
    //std::queue<Buyer> curQueue = queue;
    Buyer cur;
    while(&queue != nullptr){
        if(!queue.empty()){
            cur = queue.front();
            queue.pop();
            sleep(cur.cart.size());
        }
    }
}

void Shop::createServant(int queueNum){
    std::thread servant(checkout, std::ref(*(queues.at(queueNum))));
    servants.push_back(&servant);
    servant.detach();
}

void Shop::openDoors(){
    int idleCount = 0;
    while(idleCount < 10){
        if(rand()%2 == 1 && idleCount < 10){
            if(queues.size() == 0 || queues.back()->size() >= 5){
                queues.push_back(new std::queue<Buyer>);
                queues.back()->push(*(new Buyer()));
                createServant(queues.size() - 1);
            }else{
                queues.back()->push(*(new Buyer()));
            }
        }else{
            idleCount++;
        }
        std::cout << queues.size() << std::endl;
        for(int i = 0; i < queues.size(); i++){
            std::cout << queues.at(i)->size() << " ";
        }
        std::cout << std::endl;
        sleep(1);
    }
    while(queues.size() > 0){
        for(int i = 0; i < queues.size(); i++){        
            if(queues.at(i)->size() == 0){
                queues.erase(queues.begin() + i);
            }
            std::cout << queues.size() << std::endl;
            for(int i = 0; i < queues.size(); i++){
                std::cout << queues.at(i)->size() << " ";
            }
            std::cout << std::endl;
            sleep(1);
        }
    }
}
