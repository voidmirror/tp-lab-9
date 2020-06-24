#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>

std::mutex simpleMutex;
std::condition_variable simpleConditionVariable;

bool switcher = true;
bool finishFlag = false;

void threadBubbleSort(std::vector<std::string> &vector, bool comparator(std::string a, std::string b)) {
    for (int i = 0; i < vector.size() - 1; i++) {
        for (int j = 0; j < vector.size() - 1 - i; j++) {

            std::unique_lock<std::mutex> lock(simpleMutex);
            simpleConditionVariable.wait(lock, []() { return !switcher; });

            if (!comparator(vector[j], vector[j + 1])) {
                auto temp = vector[j + 1];
                vector[j + 1] = vector[j];
                vector[j] = temp;
                switcher = true;
                simpleConditionVariable.notify_all();
            }
        }
    }
    std::lock_guard<std::mutex> lk(simpleMutex);
    finishFlag = true;
    switcher = true;
    simpleConditionVariable.notify_all();
}

template<class T>
std::ostream &operator<<(std::ostream &out, std::vector<T> vector) {
    for (const T &elem : vector) {
        out << elem << " ";
    }
    out << "\n";
    return out;
}

void task2Tests() {
    std::vector<std::string> stringVector = {"g", "f", "d", "e", "c", "b", "a"};
    std::thread sortThread(
            threadBubbleSort,
            ref(stringVector),
            [](const std::string a, const std::string b) { return a < b; });
    while (true) {

        std::unique_lock<std::mutex> lock(simpleMutex);
        simpleConditionVariable.wait(lock, []() {return switcher;});

        std::cout << stringVector;
        switcher = false;

        if (finishFlag) {
            break;
        }

        simpleConditionVariable.notify_one();
    }
    sortThread.join();
}