#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
using namespace std;

mutex mutex_out;
mutex mutex_i;


void bubble_sort(vector<string> &arr, bool comparator(const string &a, const string &b), bool &flag) {
    for (int i = 0; i < arr.size(); i++) {
        mutex_i.lock();
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (!comparator(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
        mutex_out.unlock();
    }
    flag = false;
}


int main() {
    vector<string> string_vector = {"one","two_words","three_words","long_string_for_test"};
    bool flag = true;
    thread t(bubble_sort, ref(string_vector),[](const string &a, const string &b) { return a.size() > b.size(); }, ref(flag));
    mutex_out.lock();
    while (flag) {
        for (const string &i: string_vector) {
            cout << i << " ";
        }
        cout << endl;
        mutex_out.lock();
        mutex_i.unlock();
    }
    t.join();
    return 0;
}