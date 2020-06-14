#include <iostream>
#include <vector>
#include <queue>
#include <random>

#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

#define MAX_GOODS 8
#define MAX_GOOD_ID 255
#define MAX_QUEUE_SIZE 5
mutex mtx;

class Customer {
private:
    int id;
    vector<int> goods;
public:
    explicit Customer(int new_id) : id{new_id}
    {
        random_device rdev{};
        default_random_engine generator{rdev()};
        uniform_int_distribution<int> goods_dist(1, MAX_GOODS - 1);
        uniform_int_distribution<int> id_dist(1, MAX_GOOD_ID - 1);

        size_t goods_amount = goods_dist(generator);
        goods.resize(goods_amount);
        for(auto &good : goods)
        {
            good = id_dist(generator);
        }
    }

    friend void serve(queue<Customer>* line);
};

void serve(queue<Customer>* line) {
    while (!line->empty()) {
        const auto &customer = line->front();
        for (const auto &good : customer.goods)
        {
            mtx.lock();

            cout << "customer " << customer.id << " is being served by" << this_thread::get_id() << endl;

            mtx.unlock();
            this_thread::sleep_for(chrono::seconds(1));
        }
        line->pop();
    }
}

int main() {

    size_t customers = 100;
    vector<queue<Customer>*> queues;
    vector<thread*> threads;

    for (size_t id = 0; id < customers; id++) {
        this_thread::sleep_for(chrono::seconds(1));

        ssize_t queue_number{-1};
        for (const auto& queue : queues)
        {
            if (queue->size() != MAX_QUEUE_SIZE)
            {
                queue->emplace(id);
            }
            ++queue_number;
        }
        if (queue_number == queues.size() || queue_number == -1)
        {
            auto* new_queue = new queue<Customer>;
            new_queue->emplace(id);
            queues.push_back(new_queue);

            auto* new_thread = new thread(serve, queues[0]);
            threads.push_back(new_thread);
            continue;
        }
    }

    for (auto th : threads) {
        th->join();
    }

    return 0;
}