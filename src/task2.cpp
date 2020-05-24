#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;
bool toPrint = false;
bool done = false;
template<typename Iterator, typename Comparator>
void bubbleSort(Iterator begin, Iterator end, Comparator comp) {
    int n = end - begin;
    for (int i = 0; i < n - 1; i++) {
        lock_guard<mutex> lg(mtx);
        if (!toPrint) {
            for (int j = 0; j < n - i - 1; j++) {
                if (comp(*(begin + j), *(begin + j + 1)))
                    std::iter_swap(begin + j, begin + j + 1);
            }
            toPrint = true;
        }
    }


    done = true;
}
int main() {
    vector<string> v = { "asd", "adz", "qwerty", "", "HSE NN", "87ASUS", "Clion", "a", "y", "W", "Doroshenko", "vector321" };
    auto lambda1 = [](const string& a, const string& b) -> bool { return a.size() > b.size(); };

    thread t1(bubbleSort<decltype(v.begin()), decltype(lambda1)>, v.begin(), v.end(), lambda1);
	
    while (true)
    {
        if(toPrint)
        {
            lock_guard<mutex> lg(mtx);
            for (auto& x : v)
                cout << x << " ";
            cout << endl;
            toPrint = false;
        }
        if (done)
            break;
    }

    t1.join();
}