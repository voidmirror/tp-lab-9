#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


condition_variable cv;
bool stop = false, need_print = true;
mutex mut;

template <typename T, typename C>
void buble_sort(T* mas, int len, C comp)
{
    while (len > 1) {
        for (int i = 0; i < len - 1; i++)
        {
            if (comp(mas[i], mas[i+1])>0) {
                T temp = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = temp;
            }
        }
        len--;
    }
}

template <typename C>
void buble_sort2(string* mas, int len, C comp)
{
    unique_lock<mutex> lock(mut);
    while (len > 1) {
        cv.wait(lock, [] { return !need_print; });
        for (int i = 0; i < len - 1; i++)
        {
            if (comp(mas[i], mas[i + 1]) > 0) {
                string temp = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = temp;
            }
        }
        len--;
        need_print = true;
        cv.notify_all();
    }
    stop = true;
}

void print(string* mas, int len)
{
    while (!stop) {
        unique_lock<mutex> lock(mut);
        cv.wait(lock, [] { return need_print; });
        for (int i = 0; i < len; i++)
        {
            cout << mas[i] << "  ";
        }
        cout << endl;
 
        need_print = false;
        cv.notify_all();
    }
}

int comp5(string a, string b)
{
    return a.compare(b);
}

int main()
{
    int mas[6] = { 1,4,6,8,2,-3 };
    buble_sort(mas, 6, [](int a, int b) -> int {return a - b; });
    buble_sort(mas, 6, [](int a, int b) -> int {return b - a;; });
    buble_sort(mas, 6, [](int a, int b) -> int {return abs(a) - abs(b); });
    buble_sort(mas, 6, [](int a, int b) -> int {return abs(b) - abs(a); });

    

    string a = "Hello";
    string b = "world";
    string c = "please";
    string mas2[3] = { a, b, c };
    
    thread t1([&mas2]() {buble_sort2(mas2, 3, [](string a, string b) -> int {return a.compare(b); }); });
    print(mas2, 3);
    t1.join();
    
}

