#ifndef LAB9_TASK2_H
#define LAB9_TASK2_H


#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>


void bubbleSortingUtil(std::vector<std::string>& baseArray, bool comparator(std::string firstString, std::string secondString));
void bubbleSortingByThreads(std::vector<std::string>& baseArray);
void printSortedVectorByThreads(const std::vector<std::string>& baseArray);


#endif //LAB9_TASK2_H
