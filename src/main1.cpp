//
// Created by Илья on 002 02.06.20.
//
#include <iostream>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;

template<class F>
void bubble_sort(vector<string>& a, F comparator) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size() - 1; j++) {
            if (!comparator(a[j], a[j + 1])) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

void print_vector(vector<string>& res) {
    for(auto x: res) {
        cout << x << ' ';
    }
    cout << endl;
}

int main() {
    vector<string> to_sort_0 = {"laba1", "laba2", "test", "course work", "I", "love", "c++"};
    bubble_sort(to_sort_0, [](string& str1, string& str2) {
        return str1 < str2;
    });
    print_vector(to_sort_0);


    vector<string> to_sort_1 = {"laba1", "laba2", "test", "course work", "I", "love", "c++"};
    bubble_sort(to_sort_1, [](string& str1, string& str2) {
        return str1 > str2;
    });
    print_vector(to_sort_1);


    vector<string> to_sort_2 = {"laba1", "laba2", "test", "course work", "I", "love", "c++"};
    bubble_sort(to_sort_2, [](string& str1, string& str2) {
        return str1[str1.size() / 2] > str2[str2.size() / 2];
    });
    print_vector(to_sort_2);


    vector<string> to_sort_3 = {"laba1", "laba2", "test", "course work", "I", "love", "c++"};
    bubble_sort(to_sort_3, [](string& str1, string& str2) {
        return str1[0] < str2[0];
    });
    print_vector(to_sort_3);


    vector<string> to_sort_4 = {"laba1", "laba2", "test", "course work", "I", "love", "c++"};
    bubble_sort(to_sort_4, [](string& str1, string& str2) {
        return str1[str1.size() - 1] < str2[str2.size() - 1];
    });
    print_vector(to_sort_4);
    return 0;
}
