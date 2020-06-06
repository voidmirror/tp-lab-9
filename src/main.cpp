#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include "StringSorter.h"
#include "Shop.h"
using namespace std;

std::mutex mut;
bool threadProgress = true;
bool timeToShow = false;


void threadSort(vector<string> &input, bool lambda(string a, string b)){
    threadProgress = true;
    for(int i = 0; i < input.size() - 1; i++){
        for(int o = 0; o < input.size() - (i + 1); o++){
            mut.lock();
            if(lambda(input[o], input[o + 1])){
                std::swap(input[o], input[o + 1]);
                timeToShow = true;
            }
            mut.unlock();
        }
    }
    threadProgress = false;
}

int main()
{
    //task 1
    cout << "Source string vector:";
    vector<string> source = {"jjj", "a", "aa", "bbb", "cccc", "plpl", "aa"};
    for(int i = 0; i < source.size(); i++){
        cout << source.at(i) << " ";
    }
    cout << endl;
    StringSorter ss;
    cout << "Sort by length:";
    vector<string> result = ss.sortByLambdaSavingSource(source, [](string a, string b){ return a.length() > b.length();});
    for(int i = 0; i < result.size(); i++){
        cout << result.at(i) << " ";
    }
    cout << endl;

    cout << "Sort by first symbol:";
    result = ss.sortByLambdaSavingSource(source, [](string a, string b){ return a > b;});
    for(int i = 0; i < result.size(); i++){
        cout << result.at(i) << " ";
    }
    cout << endl;

    cout << "Sort by last symbol:";
    result = ss.sortByLambdaSavingSource(source, [](string a, string b){ return a[a.size() - 1] > b[b.size() - 1];});
    for(int i = 0; i < result.size(); i++){
        cout << result.at(i) << " ";
    }
    cout << endl;

    cout << "Sort by middle symbol:";
    result = ss.sortByLambdaSavingSource(source, [](string a, string b){ return a[a.size() / 2] > b[b.size() / 2];});
    for(int i = 0; i < result.size(); i++){
        cout << result.at(i) << " ";
    }
    cout << endl;

    cout << "Sort by length and first symbol:";
    result = ss.sortByLambdaSavingSource(source, [](string a, string b){ return (a > b) && [](string a, string b){ return a.length() < b.length();};});
    for(int i = 0; i < result.size(); i++){
        cout << result.at(i) << " ";
    }
    cout << endl;

    //task 2

    cout << "Sort by last symbol in sepparate thread progress:\n";
    thread sortThread(threadSort, std::ref(source), [](string a, string b){ return a > b;});
    while (threadProgress){
        if (timeToShow){
            mut.lock();
            for (int i = 0; i < source.size();i++){
                cout<<source.at(i)<< " ";
            }
            cout << endl;
            timeToShow = false;
            mut.unlock();
        }
    }
    sortThread.join();

    //task3
    Shop shop = *(new Shop());
    shop.openDoors();
    return 0;
}
