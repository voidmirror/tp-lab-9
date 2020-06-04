#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

template <class t, class t2>
void bubbleSort(vector<t>& a, t2 comparator) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size() - i - 1; j++) {
            if (comparator(a[j], a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}



int main1() {
    vector <int> ints = { 6, 7, 4, 1, 10, 5, 20, 2, 32 };
    vector <double> doubles = { 2.2, 3.3, 1.0, 4.1, 4.0, 6.2, 5.5, 1.6, 9.4, 9.3, 11.1 };
    vector <string> strings = { "qwe", "qweewewq", "qwwweeeqqw", "we", "weqq", "qqqqq","q", "wwweee" };
    cout << "Base vectors: \n "  << endl;
    for (auto item : ints) {
        cout << item << " ";
    }
    cout << endl;
    for (auto item : doubles) {
        cout << item << " ";
    }
    cout << endl;
    for (auto item : strings) {
        cout << item << " ";
    }
    cout << endl;
    bubbleSort(ints, [](int a, int b) {return a < b; });
    cout << "Vector of integers in descending order: \n " << endl;
    for (auto item : ints) {
        cout << item << " ";
    }
    bubbleSort(ints, [](int a, int b) {return a > b; });
    cout << "\nVector of integers in ascending order: \n" << endl;
    for (auto item : ints) {
        cout << item << " ";
    }
    bubbleSort(doubles, [](double a, double b) {return a < b; });
    cout << "\nVector of doubles in descending order: \n " << endl;
    for (auto item : doubles) {
        cout << item << " ";
    }
    bubbleSort(doubles, [](double a, double b) {return a > b; });
    cout << "\nVector of doubles in ascending order: \n " << endl;
    for (auto item : doubles) {
        cout << item << " ";
    }
    bubbleSort(strings, [](const string& a, const string& b) {return b.size() < a.size(); });
    cout << "\nVector of strings in ascending order of the size: \n " << endl;
    for (auto item : strings) {
        cout << item << " ";
    }
    bubbleSort(strings, [](const string& a, const string& b) {return b.size() > a.size(); });
    cout << "\nVector of strings in descending order of the size: \n" << endl;
    for (auto item : strings) {
        cout << item << " ";
    }
    return 0;
}