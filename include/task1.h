#ifndef CLAB9_TASK1_H
#define CLAB9_TASK1_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;
template<class T, class C>
vector <T> bubbleSort(vector <T> vec, C comparator) {
    int len = vec.size();
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++)
            if (!comparator(vec[j], vec[j + 1])) {
                swap(vec[j], vec[j + 1]);
            }
    }
    return vec;
}

void task1(){
    vector <string> stringvec = { "aaa", "asdsdf", "xcvxf", "sdfs", "wer", "bb" };
    stringvec = bubbleSort(stringvec, [](const string& a, const string& b) -> bool {return a.size() < b.size(); });
    for (const string& s : stringvec){
        cout << s << endl;
    }

    cout << endl;

    stringvec = bubbleSort(stringvec, [](const string& a, const string& b) -> bool {return a.size() > b.size(); });
    for (const string& s : stringvec){
        cout << s << endl;
    }

    cout << endl;

    stringvec = bubbleSort(stringvec, [](const string& a, const string& b) -> bool {return a > b; });
    for (const string& s : stringvec){
        cout << s << endl;
    }

    cout << endl;

    vector <int> intvec = { 1, 2, 23, 0, 54, 633 };

    intvec = bubbleSort(intvec, [](int a, int b) -> bool {return a < b; });
    for (int s : intvec){
        cout << s << endl;
    }

    cout << endl;

    intvec = bubbleSort(intvec, [](int a, int b) -> bool {return a > b; });
    for (int s : intvec){
        cout << s << endl;
    }
}
#endif //CLAB9_TASK1_H
