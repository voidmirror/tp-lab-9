//
// Created by Илья Соловьёв on 23.05.2020.
//

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

std::mutex mutex;
std::condition_variable cv;
bool printed(false), sorted(true), is_finished(false);

void bubble_sort(std::vector<std::string> & arr, bool comparator(const std::string &, const std::string &))
{
    for (size_t i = 0; i < arr.size(); i ++){
        std::unique_lock <std::mutex> lock(mutex);
        cv.wait(lock, []{ return printed;});
        for (size_t j = 0; j < arr.size() - i - 1; j ++){
            if (comparator(arr[j], arr[j + 1])){
                std::swap (arr[j], arr[j + 1]);
            }
        }
        sorted = true;
        printed = false;
        lock.unlock();
        cv.notify_all();
    }
    is_finished = true;
}

int main(){
    std::vector <std::string> string_vector = {"test1", "test2", "test3", "test31", "test1111", "tes", "teeeeeest"};
    std::thread t = std::thread(bubble_sort,
                                std::ref(string_vector),
                                [](const std::string & a, const std::string & b){return a.size() > b.size();});
    while (!is_finished){
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, []{ return sorted;});
        sorted = false;
        for (const auto& i : string_vector){
            std::cout << i << " ";
        }
        std::cout << std::endl;
        printed = true;
        lock.unlock();
        cv.notify_all();
    }
    t.join();
    return 0;
}

