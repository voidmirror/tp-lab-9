#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
template<typename Iterator, typename Comparator>
void bubbleSort(Iterator begin, Iterator end, Comparator comp) {
    int n = end - begin;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comp(*(begin + j),*(begin + j + 1)))
                std::iter_swap(begin + j, begin + j + 1);
        }
    }
}
int main() {
    vector<string> v = {"asd", "adz", "qwerty", "", "HSE NN", "87ASUS", "Clion", "a", "y", "W", "Doroshenko", "vector321"};
    auto lambda1 = [](const string& a, const string& b) -> bool { return a.size() > b.size(); };
    auto lambda2 = [](const string& a, const string& b) -> bool { return a.front() > b.front(); };
    auto lambda3 = [](const string& a, const string& b) -> bool { return a.back() > b.back(); };
    auto lambda4 = [](const string& a, const string& b) -> bool {
        return accumulate(a.begin(), a.end(), 0) > accumulate(b.begin(), b.end(), 0);
    };
    auto lambda5 = [](const string& a, const string& b) -> bool {
        if (a.size() == b.size())
            for (int i = 0; i < a.size(); i++)
                if (a[i] != b[i])
                    return a[i] > b[i];
        return a.size() > b.size();
    };
    bubbleSort(v.begin(), v.end(), lambda1);
    for (auto x : v) {
        cout << x << endl;
    }
    bubbleSort(v.begin(), v.end(), lambda2);
    for (auto x : v) {
        cout << x << endl;
    }
    bubbleSort(v.begin(), v.end(), lambda3);
    for (auto x : v) {
        cout << x << endl;
    }
    bubbleSort(v.begin(), v.end(), lambda4);
    for (auto x : v) {
        cout << x << endl;
    }
    bubbleSort(v.begin(), v.end(), lambda5);
    for (auto x : v) {
        cout << x << endl;
    }
    return 0;
}
