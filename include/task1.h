#ifndef task1_h
#define task1_h

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

void printVector(vector<string> array){
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

vector<string> bubbleSort(vector<string> array, bool comparator(string &a, string &b)) {
    vector <string> result = array;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array.size() - i - 1; j ++){
            if (comparator(result[j], result[j+1])) {
                swap(result[j], result[j+1]);
            }
        }
    }
    return result;
}

vector<string> sortBySizeUp(vector<string> array) {
    return bubbleSort(array, [](string& a, string& b){ return a.length() > b.length() ? true : false;});
}

vector<string> sortByStringUp(vector<string> array) {
    return bubbleSort(array, [](string& a, string& b){ return a > b ? true : false;});
}

vector<string> sortByLastLetter(vector<string> array) {
    return bubbleSort(array, [](string& a, string& b){ return a[a.length()-1] > b[b.length()-1] ? true : false;});
}

vector<string> sortBySizeDown(vector<string> array) {
    return bubbleSort(array, [](string& a, string& b){ return a.length() < b.length() ? true : false;});
}

vector<string> sortByStringDown(vector<string> array) {
    return bubbleSort(array, [](string& a, string& b){ return a < b ? true : false;});
}


#endif
