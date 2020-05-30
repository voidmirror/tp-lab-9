#include "task1.h"


std::vector<std::string> bubbleSorting(const std::vector<std::string>& baseArray, bool comparator(std::string &firstString, std::string &secondString))
{
    std::vector<std::string> sortedArray = baseArray;

    for(int i = 0; i < baseArray.size(); i++)
    {
        for(int j = 0; j < baseArray.size() - i - 1; j++)
        {
            if (comparator(sortedArray[j], sortedArray[j + 1]))
            {
                std::swap(sortedArray[j], sortedArray[j + 1]);
            }
        }
    }

    return sortedArray;

}


std::vector<std::string> firstLetterSortingUp(const std::vector<std::string>& baseArray)
{
    return bubbleSorting(baseArray, [](std::string& firstString, std::string& secondString){return firstString[0] > secondString[0];});
}

std::vector<std::string> firstLetterSortingDown(const std::vector<std::string>& baseArray)
{
    return bubbleSorting(baseArray, [](std::string& firstString, std::string& secondString){return firstString[0] < secondString[0];});
}

std::vector<std::string> maxSizeSorting(const std::vector<std::string>& baseArray)
{
    return bubbleSorting(baseArray, [](std::string& firstString, std::string& secondString){return firstString.length() > secondString.length();});
}

std::vector<std::string> minSizeSorting(const std::vector<std::string>& baseArray)
{
    return bubbleSorting(baseArray, [](std::string& firstString, std::string& secondString){return firstString.length() < secondString.length();});
}

std::vector<std::string> lastLetterSorting(const std::vector<std::string>& baseArray)
{
    return bubbleSorting(baseArray, [](std::string& firstString, std::string& secondString){return firstString[firstString.length() - 1] < secondString[secondString.length() - 1];});
}


void printSortedVector(const std::vector<std::string>& baseArray)
{
    std::cout << std::endl;
    for(const auto & i : baseArray)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

