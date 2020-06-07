// #define _TASK_1_MAIN_
#define _TASK_2_MAIN_

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
