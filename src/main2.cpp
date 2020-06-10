#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>

std::condition_variable conditionVariable;
bool needToStop = false;
bool needToPrint = true;
std::mutex mutex;

template <typename C>
void bubbleSort(std::string* array, int size, C comp) {
    std::unique_lock<std::mutex> lock(mutex);
    while (size > 1) {
        conditionVariable.wait(lock, [] {
            return !needToPrint;
        });
        for (int i = 0; i < size - 1; i++) {
            if (comp(array[i], array[i + 1]) > 0) {
                std::swap(array[i], array[i + 1]);
            }
        }
        size--;
        needToPrint = true;
        conditionVariable.notify_all();
    }
    needToStop = true;
}

void printText(std::string* array, int size) {
    while (!needToStop) {
        std::unique_lock<std::mutex> lock(mutex);
        conditionVariable.wait(lock, [] {
            return needToPrint;
        });
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << "  ";
        }
        std::cout << "\n";

        needToPrint = false;
        conditionVariable.notify_all();
    }
}

int main() {

    std::string first = "First";
    std::string second = "second";
    std::string third = "third";
    std::string array[3] = { first, second, third };
    std::thread thread([&array]() {bubbleSort(array, 3, [](const std::string& first, const std::string& second) ->
    int { return first.compare(second); }); });

    printText(array, 3);
    thread.join();
}
