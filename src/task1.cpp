#include <iostream>
#include <vector>
#include <functional>
#include <string>

template <class T, class F>
void bubble_sort(std::vector<T> & arr, F comparator)
{
    for (size_t i = 0; i < arr.size(); i ++){
        for (size_t j = 0; j < arr.size() - i - 1; j ++){
            if (comparator(arr[j], arr[j + 1])){
                std::swap (arr[j], arr[j + 1]);
            }
        }
    }
}

int main(){
    std::vector <int> int_vector = {7, 5, 9, 7, 0,4, 3, 8, 1, 6, 2};
    std::vector <double> double_vector = {7.9, 5.4, 9.2, 7.2, 0.2,-4.1, 3.0, -8.9, 1.2, 6.6, 2.3};
    std::vector <std::string> string_vector = {"qwe", "uiop", "ssaa", "uuiiyy", "a", "lol", "kek"};

    bubble_sort(int_vector, [](int a, int b){return a > b;});
    std::cout << "#1" << std::endl;
    for (auto i : int_vector){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(double_vector, [](double a, double b){return a > b;});
    std::cout << "#2" << std::endl;
    for (auto i : double_vector){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(string_vector, [](const std::string & a, const std::string & b){return a.size() > b.size();});
    std::cout << "#3" << std::endl;
    for (auto i : string_vector){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(string_vector, [](const std::string & a, const std::string & b){return b.compare(a);});
    std::cout << "#4" << std::endl;
    for (auto i : string_vector){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    bubble_sort(int_vector, [](int a, int b){return a < b;});
    std::cout << "#5" << std::endl;
    for (auto i : int_vector){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}

