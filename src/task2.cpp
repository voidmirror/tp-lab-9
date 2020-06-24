#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

bool toPrint = false;
bool sorted = false;

void bubbleSort(vector<string>& vector, bool comparator(const string&, const string&)) {
    size_t vectorSize = vector.size();
    for (size_t i = 0; i < vectorSize; i++) {
        lock_guard<mutex> guard(mtx);
        if (!toPrint) {
            for (size_t j = 0; j < vectorSize - i - 1; j++)
                if (!comparator(vector[j], vector[j + 1])) {
                    swap(vector[j], vector[j + 1]);
                }
            toPrint = true;
        }
    }
    sorted = true;
}

void printVector(vector<string> vector) {
    for (string& element : vector)
        cout << element << " ";
    cout << endl;
}

int main() {

    vector<string> vec = { "hello", "world", "apple", "human", "man", "communication", "and", "in", "o" };
    
    printVector(vec);

    auto comparator = [](const string& a, const string& b) {return a[0] < b[0];};
    
    thread thr(bubbleSort, ref(vec), comparator);

    while (!sorted) 
        if (toPrint) {
            lock_guard<mutex> guard(mtx);
            printVector(vec);
            toPrint = false;
        }

    thr.join();
}