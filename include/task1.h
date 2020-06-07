#pragma once
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>

typedef unsigned int uint;

template<class T>
void bubbleSort(std::vector<std::string> &vec, T comp);
void print(std::vector<std::string>const &vec);