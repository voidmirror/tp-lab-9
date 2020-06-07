#include <string>
#include <thread>
#include <mutex>

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;


template<typename T>
void BubbleSort(vector<T>* vec, function<bool(T, T)> comparator) {
    if (vec->empty())
        return;
    mutex output_mutex;
    lock_guard<mutex> lock(output_mutex);
    bool isSorted = true;
    int k = 0;
    for (int i = 0; i < vec->size(); i++) {
        thread out_thread([&output_mutex, &k](vector<T>* vec) {
            for_each((*vec).begin(), (*vec).end(), [](T x) { cout << x << " "; });
            cout << "  " << k << "-th iteration" << endl;
            k++;
            }, vec);
        out_thread.join();

        for (int j = 0; j < (*vec).size() - i - 1; j++) {
            if (comparator((*vec)[j], (*vec)[j + 1])) {
                swap((*vec)[j], (*vec)[j + 1]);
                isSorted = false;
            }
        }
        if (isSorted)
            return;
    }
}


int main() {
    vector<string> vec{ "a", "aa", "aaa", "aaaa", "aaaaa" };
    cout << "Source vector : ";
    for_each(vec.begin(), vec.end(), [](string x) { cout << x << " "; });
    cout << endl;
    cout << "Sorting by string cmp up down : ";


    thread thread1(BubbleSort<string>, &vec, [](string a, string b) {
        if (a < b)
            return true;
        else
            return false;
        });
    thread1.join();

    for_each(vec.begin(), vec.end(), [](string x) { cout << x << " "; });
    cout << endl;


    return 0;
}

