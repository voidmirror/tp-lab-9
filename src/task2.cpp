#include "task2.h"


std::mutex testMutex;


void bubbleSortingUtil(std::vector<std::string>& baseArray, bool comparator(std::string firstString, std::string secondString))
{
    for(int i = 0; i < baseArray.size() - 1; i++)
    {
        for (int j = 0; j < baseArray.size() - i - 1; j++)
        {
            if(comparator(baseArray[j], baseArray[j + 1]))
            {
                testMutex.lock();
                std::swap(baseArray[j], baseArray[j + 1]);
                printSortedVectorByThreads(baseArray);
                testMutex.unlock();
            }
        }
    }
}


void bubbleSortingByThreads(std::vector<std::string>& baseArray)
{
    std::vector<std::string> sortedArray = baseArray;
    std::thread testThread(bubbleSortingUtil, std::ref(sortedArray), [](std::string firstString, std::string secondString){return firstString[0] > secondString[0];});

    testThread.join();
}


void printSortedVectorByThreads(const std::vector<std::string>& baseArray)
{
    for(const auto & i : baseArray)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
