#ifndef LAB9_TASK1_H
#define LAB9_TASK1_H

#include <vector>
#include <string>
#include <iostream>


std::vector<std::string> bubbleSorting(const std::vector<std::string>& baseArray, bool comparator(std::string &firstString, std::string &secondString));

std::vector<std::string> firstLetterSortingUp(const std::vector<std::string>& baseArray);
std::vector<std::string> firstLetterSortingDown(const std::vector<std::string>& baseArray);
std::vector<std::string> maxSizeSorting(const std::vector<std::string>& baseArray);
std::vector<std::string> minSizeSorting(const std::vector<std::string>& baseArray);
std::vector<std::string> lastLetterSorting(const std::vector<std::string>& baseArray);

void printSortedVector(const std::vector<std::string>& baseArray);


#endif //LAB9_TASK1_H
