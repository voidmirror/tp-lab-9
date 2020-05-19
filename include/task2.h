#ifndef TASK_2_H
#define TASK_2_H

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <algorithm>

extern std::mutex mutex;
extern bool resume; // = true;
extern bool print;  // = true;

void sort(std::vector<std::string> &var,  bool comp(const std::string a, const std::string b));


#endif