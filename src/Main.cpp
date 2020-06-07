// #define _TASK_1_MAIN_
// #define _TASK_2_MAIN_
#define _TASK_3_MAIN_

#ifdef _TASK_1_MAIN_

#include <cstdint>
#include <cctype>
#include <iostream>
#include <string>

#include "Task1.h"

template<typename T>
void PrintArray(T *array, int32_t arrayLength)
{
    for (int32_t i = 0; i < arrayLength; i++)
        std::cout << array[i] << (i < arrayLength - 1 ? ", " : "");
    std::cout << std::endl;
}

int32_t main()
{
    int32_t int32Array[5] = { 4, 1, 3, 5, 2 };
    BubbleSort<int32_t>(int32Array, 5, [](int left, int right) { return left - right; }); // sort in ascending order
    PrintArray(int32Array, 5);
    BubbleSort<int32_t>(int32Array, 5, [](int left, int right) { return right - left; }); // sort in descending order
    PrintArray(int32Array, 5);


    std::string stringArray[5] = { "CCC", "bbbb", "E", "dd", "AAAAA" };
    BubbleSort<std::string>(stringArray, 5, [](std::string *left, std::string *right) { return (int32_t)left->size() - (int32_t)right->size(); }); // compare by length
    PrintArray(stringArray, 5);
    BubbleSort<std::string>(stringArray, 5, [](std::string *left, std::string *right) { return left->compare(*right); }); // compare as usual
    PrintArray(stringArray, 5);
    BubbleSort<std::string>(stringArray, 5, [](std::string *left, std::string *right) { return std::tolower((*left)[0]) - std::tolower((*right)[0]); }); // compare by first symbols casted to lower register
    PrintArray(stringArray, 5);
}

#endif // _TASK_1_MAIN_

#ifdef _TASK_2_MAIN_

#include <algorithm>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

typedef std::unique_lock<std::mutex> unique_mutex_lock;

std::mutex mutex;
std::condition_variable conditionVariable;
bool threadFinished = false;
bool flag = false;

std::string ArrayToString(std::string *array, int32_t arrayLength)
{
    std::string result;
    for (int32_t i = 0; i < arrayLength; i++)
        result += array[i] + (i < arrayLength - 1 ? ", " : "");
    return result;
}

template<typename T>
void BubbleSort(T *array, int32_t arrayLength, int32_t(*comparsion)(T *left, T *right))
{
    for (int32_t j = 0; j < arrayLength; j++)
    {
        bool anySwaps = false;

        unique_mutex_lock lock(mutex);
        conditionVariable.wait(lock, []() { return !flag; });
        for (int32_t i = 0; i < arrayLength - j - 1; i++)
        {
            if (comparsion(array + i, array + i + 1) > 0)
                std::swap(array[i], array[i + 1]), anySwaps = true;
        }
        flag = true;
        lock.unlock();
        conditionVariable.notify_all();

        if (!anySwaps)
        {
            threadFinished = true;
            return;
        }
    }
};

int32_t main()
{
    std::string stringArray[5] = { "CCC", "bbbb", "E", "dd", "AAAAA" };

    std::cout << ArrayToString(stringArray, 5) << std::endl;

    std::mutex mutex;
    std::thread thread([](std::string *array, int32_t arrayLength, int32_t(*comparsion)(std::string *left, std::string *right)) { BubbleSort<std::string>(array, arrayLength, comparsion); },
        stringArray, 5, [](std::string *left, std::string *right) { return (int32_t)left->size() - (int32_t)right->size(); });

    conditionVariable.notify_all();
    while (!threadFinished)
    {
        unique_mutex_lock lock(mutex);
        conditionVariable.wait(lock, []() { return flag; });

        std::cout << ArrayToString(stringArray, 5) << std::endl;

        flag = false;
         lock.unlock();
        conditionVariable.notify_all();
    }

    thread.join();
}

#endif // _TASK_2_MAIN_

#ifdef _TASK_3_MAIN_

#include <algorithm>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "Task3.h"

typedef std::unique_lock<std::mutex> unique_mutex_lock;

std::mutex mutex;
std::condition_variable conditionVariable;
bool threadFinished = false;
bool flag = false;

std::string ArrayToString(std::string *array, int32_t arrayLength)
{
    std::string result;
    for (int32_t i = 0; i < arrayLength; i++)
        result += array[i] + (i < arrayLength - 1 ? ", " : "");
    return result;
}

template<typename T>
void BubbleSort(T *array, int32_t arrayLength, int32_t(*comparsion)(T *left, T *right))
{
    for (int32_t j = 0; j < arrayLength; j++)
    {
        bool anySwaps = false;

        unique_mutex_lock lock(mutex);
        conditionVariable.wait(lock, []() { return !flag; });
        for (int32_t i = 0; i < arrayLength - j - 1; i++)
        {
            if (comparsion(array + i, array + i + 1) > 0)
                std::swap(array[i], array[i + 1]), anySwaps = true;
        }
        flag = true;
        lock.unlock();
        conditionVariable.notify_all();

        if (!anySwaps)
        {
            threadFinished = true;
            return;
        }
    }
};

std::vector<int32_t> CreateProductList()
{
    std::vector<int32_t> products;
    int32_t productsCount = rand() % 32;
    for (int32_t i = 0; i < productsCount; i++)
        products.push_back(rand() % 16);
    return products;
}

int32_t main()
{
    std::mutex stdOutMutex;
    std::vector<CashDeskService *> services;

    for (int32_t i = 0; i < 10; i++)
    {
        for (int32_t j = 0; j < services.size(); j++)
        {
            if (services[j]->IsDisposed())
            {
                services[j]->Stop();
                delete services[j];
                services.erase(services.begin() + j);
                j--;

                unique_mutex_lock stdOutLock(stdOutMutex);
                std::cout << "Closed a cash desk service." << std::endl;
                stdOutLock.unlock();
            }
        }

        Customer *customer = new Customer(CreateProductList());

        bool customerAddedToAnyService = false;
        for (CashDeskService *service : services)
        {
            if (service->CanAddCustomer())
            {
                service->AddCustomer(customer);
                customerAddedToAnyService = true;

                unique_mutex_lock stdOutLock(stdOutMutex);
                std::cout << "Added a customer to an existing cash desk service." << std::endl;
                stdOutLock.unlock();

                break;
            }
        }
        if (!customerAddedToAnyService)
        {
            CashDeskService *service = new CashDeskService(&stdOutMutex);
            service->AddCustomer(customer);
            service->Start();
            services.push_back(service);

            unique_mutex_lock stdOutLock(stdOutMutex);
            std::cout << "Created a new cash desk service and added a customer to it." << std::endl;
            stdOutLock.unlock();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3000));
    }

    for (CashDeskService *service : services)
    {
        service->Stop();
        delete service;
    }
}

#endif // _TASK_3_MAIN_
