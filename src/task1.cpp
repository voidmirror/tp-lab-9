#include <iostream>
#include <vector>
#include <string>

template<class T, class E>
std::vector<T> simpleBubbleSort(std::vector<T> vector, E compare) {
    for (int i = 0; i < vector.size() - 1; i++) {
        for (int j = 0; j < vector.size() - 1 - i; j++) {

            if (!compare(vector[j], vector[j + 1])) {
                auto temp = vector[j + 1];
                vector[j + 1] = vector[j];
                vector[j] = temp;
            }
        }
    }
    return vector;
}

template<class T>
std::ostream &operator<<(std::ostream &out, std::vector<T> vector) {
    for (const T &elem : vector) {
        out << elem << " ";
    }
    out << "\n";
    return out;
}

void task1Tests() {
    std::vector<int> intVector = {1, 3, 2, 4, 0, 8, 9, 7, 5, 6};
    std::cout << simpleBubbleSort(intVector, [](const int a, const int b) { return a < b; });
    std::cout << simpleBubbleSort(intVector, [](const int a, const int b) { return a > b; });

    std::vector<char> charVector = {'a', 'b', 'd', 'c', 'e', 'f'};
    std::cout << simpleBubbleSort(charVector, [](const char a, const char &b) { return a < b; });
    std::cout << simpleBubbleSort(charVector, [](const char &a, const char &b) { return a > b; });

    std::vector<std::string> stringVector = {"aaa", "bbb", "ccc", "AAA", "BBB", "CCC"};
    std::cout << simpleBubbleSort(stringVector, [](const std::string &a, const std::string &b) { return a < b; });
    std::cout << simpleBubbleSort(stringVector, [](const std::string &a, const std::string &b) { return a > b; });
}