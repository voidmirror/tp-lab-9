#ifndef _TASK_3_H_
#define _TASK_3_H_

#include <chrono>
#include <cstdint>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

typedef std::unique_lock<std::mutex> unique_mutex_lock;

class Customer
{
private:
    std::vector<int32_t> m_products;
    int32_t m_totalSum;

public:
    Customer(std::vector<int32_t> products)
    {
        m_products = products;
    }

    std::vector<int32_t> *GetProducts() { return &m_products; }

    std::int32_t GetTotalSum() { return m_totalSum; }
    

    void AddCost(int32_t cost)
    {
        m_totalSum += cost;
    }
};

class CashDeskService
{
private:
    std::mutex *m_stdOutMutex;
    std::queue<Customer *> m_customers;
    std::mutex m_mutex;
    std::thread m_thread;
    bool m_disposed;

    void Service()
    {
        while (true)
        {
            unique_mutex_lock lock(m_mutex);
            if (m_customers.size() > 0)
            {
                Customer *customer = m_customers.front();
                m_customers.pop();
                lock.unlock();

                for (int32_t product : *(customer->GetProducts()))
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    customer->AddCost(product);
                }

                unique_mutex_lock stdOutLock(*m_stdOutMutex);
                std::cout << "Checked out a customer for $" << customer->GetTotalSum() << " total" << std::endl;
                stdOutLock.unlock();

                delete customer;
            }
            else
            {
                lock.unlock();
                m_disposed = true;
                return;
            }
        }
    }

public:
    CashDeskService(std::mutex *stdOutMutex)
    {
        m_stdOutMutex = stdOutMutex;
    }

    bool IsDisposed() { return m_disposed; }

    bool CanAddCustomer()
    {
        unique_mutex_lock lock(m_mutex);
        int32_t size = m_customers.size();
        lock.unlock();
        return (size + 1) < 5;
    }

    void AddCustomer(Customer *customer)
    {
        unique_mutex_lock lock(m_mutex);
        m_customers.push(customer);
        lock.unlock();
    }

    void Start()
    {
        m_thread = std::thread(&CashDeskService::Service, this);
    }

    void Stop()
    {
        m_thread.join();
    }
};

#endif // _TASK_3_H_
