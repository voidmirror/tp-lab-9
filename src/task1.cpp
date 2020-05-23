//
// Created by Илья Соловьёв on 23.05.2020.
//

#include <iostream>
#include <vector>
#include <functional>
#include <string>

template<class T, class F>
void bubble_sort(std::vector<T> &arr, F comparator) {
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (comparator(arr[j], arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    std::vector<int> int_vector = {2, 10, 1, 1234, 33, 3, 7, 123, 45, 65, -10};
    std::vector<double> double_vector = {13.5, 193.2, -39.4, 4.2, 4.22, 4.19, 0, -8.9, 6.6, 2.3};
    std::vector<std::string> string_vector = {"test1", "test2", "test3", "test31", "test1111", "tes", "teeeeeest"};

    bubble_sort(int_vector, [](int a, int b) { return a > b; });
    std::cout << "#1" << std::endl;
    for (auto i : int_vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(double_vector, [](double a, double b) { return a > b; });
    std::cout << "#2" << std::endl;
    for (auto i : double_vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(string_vector, [](const std::string &a, const std::string &b) { return a.size() > b.size(); });
    std::cout << "#3" << std::endl;
    for (const auto& i : string_vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(string_vector, [](const std::string &a, const std::string &b) { return b.compare(a); });
    std::cout << "#4" << std::endl;
    for (const auto& i : string_vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(int_vector, [](int a, int b) { return a < b; });
    std::cout << "#5" << std::endl;
    for (auto i : int_vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}

