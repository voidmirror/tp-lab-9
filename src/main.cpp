//
//  main.cpp
//  finalLab
//
//  Created by Олеся Мартынюк on 21.05.2020.
//  Copyright © 2020 Olesia Martinyuk. All rights reserved.
//

#include <iostream>
#include "task1.h"

using namespace std;


int main(int argc, const char * argv[]) {
    
    // task 1
    
    vector<string> array = {"i", "love", "quarantine", "so", "much", "somebody", "help", "me"};
    vector<string> res = sortBySizeUp(array);
    printVector(res);
    
    res = sortByStringUp(array);
    printVector(res);
    
    res = sortByLastLetter(array);
    printVector(res);
    
    res = sortBySizeDown(array);
    printVector(res);
    
    res = sortByStringDown(array);
    printVector(res);
    
}
