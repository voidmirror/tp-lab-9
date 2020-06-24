#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <mutex>
#include <condition_variable>


using namespace std;

void bubbleSort(vector<string> &a, bool cmp(const string& a, const string& b));

void task2();