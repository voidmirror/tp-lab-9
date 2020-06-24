#include <iostream>
#include <vector>
#include <functional>
#include <string>
using namespace std;

template<class T1, class T2>
void bubble_sort(vector<T1> &array, T2 comparator) {
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array.size() - i - 1; j++) {
            if (comparator(array[j], array[j + 1])) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

int main() {
    vector<int> int_v = {1,5,3,17,2,4,6,8,90,0};
    vector<double> double_v = {0.1,8.9,12.3,4.4};
    vector<string> string_v = {"strings","for","the","test"};

    bubble_sort(int_v, [](int a, int b) { return a > b; });
    cout << "Test 1:\n";
    for (auto i : int_v) {
        cout << i << " ";
    }
    cout << endl;

    bubble_sort(int_v, [](int a, int b) { return a < b; });
    cout << "Test 2:\n";
    for (auto i : int_v) {
        cout << i << " ";
    }
    cout << endl;

    bubble_sort(double_v, [](double a, double b) { return a > b; });
    cout << "Test 3:\n";
    for (auto i : double_v) {
        cout << i << " ";
    }
    cout << endl;

    bubble_sort(string_v, [](const string &a, const string &b) { return a.size() > b.size(); });
    cout << "Test 4:\n";
    for (auto i : string_v) {
        cout << i << " ";
    }
    cout << endl;

    bubble_sort(string_v, [](const string &a, const string &b) { return b.compare(a); });
    cout << "Test 5:\n";
    for (auto i : string_v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
