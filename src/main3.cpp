#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <string>
#include <random>

std::mutex mtx;

void shop(std::queue<std::vector<int>> q)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Cash: " << std::this_thread::get_id() << std::endl;
    for (int i=1; !q.empty(); i++)
    {
        std::cout << "Shopper: " << i << std::endl;
        for (int j = 0; j < q.front().size(); j++)
            std::this_thread::sleep_for(std::chrono::milliseconds(q.front()[j]*20));
        q.pop();
    }
}

int main() {
    int nc, purchase, time;
    std::queue<std::vector<int>> c;
    std::vector<int> vec;
    std::vector<std::thread*> th;

    std::random_device rand;
    nc = 1 + rand() % 50;
    std::cout << "Customer: " << nc << std::endl;

    for (int i = 0; i < nc; i++)
    {
        purchase = 1 + rand() % 20;
        for (int j = 0; j < purchase; j++)
        {
            time = 1 + rand() % 20;
            vec.push_back(time);
        }
        c.push(vec);
        vec.clear();
        if ((i == nc - 1) || !(((i + 1) % 5)))
        {
            th.push_back(new std::thread(shop, c));
            while (!c.empty())
                c.pop();
        }
    }

    for (auto &t : th)
        t->join();

    std::cout << "done!" << std::endl;
}
