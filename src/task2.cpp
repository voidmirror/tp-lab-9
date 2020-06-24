#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

mutex mtx;
condition_variable cv;
bool flag_term = false;
bool flag_sort = false;
bool flag_print = true;

template <class T>
void bubble_sort(vector<T> &obj,  bool cmp(const string &lhs, const string &rhs))
{
    for(size_t i = 0; i < obj.size() - 1; i++)
    {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [] {return (flag_sort); });
        for(size_t j = 0; j < obj.size() - 1 - i; j++)
        {
            if(cmp(obj[j], obj[j + 1]))
            {
                swap(obj[j], obj[j + 1]);
            }
        }
        flag_sort = false;
        flag_print = true;

        lk.unlock();
        cv.notify_all();
    }
    flag_term = true;
}

template <class T>
void print(const vector<T> &obj)
{
    for(const auto &value : obj)
    {
        cout << value << " ";
    }
    cout << endl;
}

int main()
{
    vector<string> data;

    data = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    print(data);
    cout << endl;

    thread sort_thread(bubble_sort<string>, ref(data),
            [](const string &lhs, const string &rhs) { return lhs > rhs; });

    while(!flag_term)
    {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [] {return (flag_print); });

        print(data);

        flag_print = false;
        flag_sort = true;
        lk.unlock();
        cv.notify_all();
    }

    sort_thread.join();
    return 0;
}