#include <string>
#include <vector>
#include <iostream>
#include <functional>

using std::vector;
using std::string;

template<class F>
void bubbleSort(vector<string> &a, F cmp) {
    size_t n = a.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (!cmp(a[j], a[j + 1])) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}