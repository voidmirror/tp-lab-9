#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <thread>

void sort(std::string *array, int array_size, bool comp(const std::string &, const std::string &));