#include <task2.h>
#include <thread>

mutex mtx;
condition_variable cv;

bool step = false;
bool printed = true;
bool sorted = false;

ostream& operator<<(ostream& out, vector<string> &a) {
    for(auto &x: a) {
        out << x << ' ';
    }
    out << endl;
    return out;
}

void task2() {
    vector<string> s = {"test", "lol", "ca", "kek", "aab", "b", "aa"};
    auto cmp = [](const string &a, const string &b) -> bool {
        return a < b;
    };
    thread w(bubbleSort, ref(s), cmp);
    cv.notify_all();
    while(!sorted) {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [](){ return step; });
        cout << s;
        step = false;
        printed = true;
        lk.unlock();
        cv.notify_all();
    }
    sorted = false;
    w.join();
}

void bubbleSort(vector<string> &a, bool cmp(const string& a, const string& b)) {
    size_t n = a.size();
    for (size_t i = 0; i < n; i++) {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [](){ return printed; });
        for (size_t j = 0; j < n - 1; j++) {
            if (!cmp(a[j], a[j + 1])) {
                std::swap(a[j], a[j + 1]);
            }
        }
        step = true;
        printed = false;
        lk.unlock();
        cv.notify_all();
    }
    sorted = true;

}