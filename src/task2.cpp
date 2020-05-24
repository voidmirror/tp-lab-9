//
// Created by aklen on 23.05.2020.
//
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

mutex outputMutex;
mutex iterMutex;


void bubble_sort(vector<string> &arr, bool comparator(const string& a, const string& b), bool & flag){
    for(size_t i = 0; i < arr.size(); i++){
        iterMutex.lock();
        for(size_t j = 0; j < arr.size() - i - 1; j++ ) {
            if (!comparator(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
        outputMutex.unlock();
    }
    flag = false;
}


int main(){
    vector <string> string_vector = { "asd", "asdasddas", "dasadsdsass", "a", "dasd", "asddd" };

    bool flag = true;

    thread t(bubble_sort, ref(string_vector),
            [](const string &a, const string &b){return a.size() > b.size();}, ref(flag));

    outputMutex.lock();
    while(flag){

        for(const string& i: string_vector){
            cout<<i<<" ";
        }

        cout<<endl;

        outputMutex.lock();
        iterMutex.unlock();
    }
    t.join();
    return 0;
}