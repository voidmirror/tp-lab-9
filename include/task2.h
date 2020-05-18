#ifndef TASK_2_H
#define TASK_2_H

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>

std::mutex mutex;
bool resume = true;
bool print = true;

void sort(std::vector<std::string> &var,  bool comp(const std::string a, const std::string b));


#endif