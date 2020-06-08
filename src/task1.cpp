//
// Created by Оксана on 03.06.2020.
//
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

template<class F>
void bubbleSort(vector<string> &a, F cmp) {
    size_t n = a.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (!cmp(a[j], a[j + 1])) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}
void printArray(vector<string>& a)
{
    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    vector<string> mas = {"one", "two", "free", "four", "five", "six", "seven"};
    bubbleSort(mas, [](string &a, string &b){return a < b;});
    printArray(mas);
    bubbleSort(mas, [](string &a, string &b){return a.size() < b.size();});
    printArray(mas);
    bubbleSort(mas, [](string &a, string &b){return a[0] < b[0];});
    printArray(mas);
    bubbleSort(mas, [](string &a, string &b){return a[a.size() - 1] < b[b.size() - 1];});
    printArray(mas);
    bubbleSort(mas, [](string a, string b){
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        return a < b;
    });
    printArray(mas);
    return 0;


}
