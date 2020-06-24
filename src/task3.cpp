#include "task.h"

mutex cart_mutex;
mutex queues_mutex;

const size_t countOfCustomers = 9;
const size_t maxQueueSize = 5;

struct Customer
{
    Customer()
    {
        CreateShoppingCart();
    }

    void CreateShoppingCart();

    size_t sizeOfCart;
    vector<int> cart;
};


void Customer::CreateShoppingCart()
{
    mt19937 gen(time(0));
    uniform_int_distribution<int> dist(1, 10);

    sizeOfCart = dist(gen);
    for (int i = 0; i < sizeOfCart; i++)
    {
        cart.push_back(dist(gen));
    }
}

vector<queue<Customer*>*> allQueues;
vector<thread*> allThreads;

void ServeSingleCustomer(Customer* customer)
{
    vector<int> cart = customer->cart;
    cout << "Serving..." << endl;
    lock_guard<mutex> lock(cart_mutex);
    for (int i = 0; i < customer->sizeOfCart; i++)
    {
        cout << cart[i] << " ";
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl << "Served!" << endl;
}


void ServeQueue(queue<Customer*>* customers)
{
    while (!customers->empty())
    {
        Customer* currCustomer = customers->front();
        ServeSingleCustomer(currCustomer);
        delete currCustomer;
        customers->pop();
    }

    lock_guard<mutex> lock(queues_mutex);
    cout << "All queue is served!" << endl;
    allQueues.erase(find(allQueues.begin(), allQueues.end(), customers));
    delete customers;
}

void CreateNewQueue()
{
    lock_guard<mutex> locker(queues_mutex);
    auto newQueue = new queue<Customer*>();
    newQueue->push(new Customer);
    allQueues.push_back(newQueue);

    thread* newThread = new thread(ServeQueue, newQueue);
    allThreads.push_back(newThread);
}

void Run()
{
    mt19937 gen(time(0));
    uniform_int_distribution<int> dist(5, 15);

    for (size_t i = 1; i < countOfCustomers; i++)
    {
        for (auto q : allQueues)
        {
            if (q->size() < maxQueueSize)
            {
                lock_guard<mutex> locker(queues_mutex);
                q->push(new Customer);
            }
            else
            {
                CreateNewQueue();
            }
        }

        if (allQueues.size() == 0)
        {
            CreateNewQueue();
        }

        this_thread::sleep_for(chrono::milliseconds(15 * dist(gen)));
    }

    for (auto t : allThreads)
        t->join();
}


int main()
{
    srand(time(0));
    Run();
}