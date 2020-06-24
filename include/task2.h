//
//  task2.h
//  finalLab
//
//  Created by Олеся Мартынюк on 21.05.2020.
//  Copyright © 2020 Olesia Martinyuk. All rights reserved.
//

#ifndef task2_h
#define task2_h
#include <thread>
#include <mutex>

bool flagDone = true;
bool flagPrint = true;
mutex mtx;

using namespace std;

void bubbleSortThreaded (vector<string> &array, bool comparator(string a, string b)){
    for (size_t i = 0; i < array.size()-1; i++) {
        for (size_t j = 0; j < array.size()-i-1; j++) {
            if (comparator(array[j], array[j+1])) {
                mtx.lock();
                swap(array[j], array[j+1]);
                flagPrint = true;
                mtx.unlock();
            }
        }
    }
    flagDone = true;
}
#endif /* task2_h */
