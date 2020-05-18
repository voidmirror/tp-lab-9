#ifndef TASK_1_H
#define TASK_1_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


std::vector<std::string> sort(std::vector<std::string> var, bool comp(const std::string& a, const std::string& b));

std::vector<std::string> sortByAscendingLength(std::vector<std::string> var);
std::vector<std::string> sortByDescendingLength(std::vector<std::string> var);
std::vector<std::string> sortByAscending(std::vector<std::string> var);
std::vector<std::string> sortByDescending(std::vector<std::string> var);
std::vector<std::string> sortByAscendingLastCharacters(std::vector<std::string> var);
std::vector<std::string> sortByDescendingLastCharacters(std::vector<std::string> var);


#endif