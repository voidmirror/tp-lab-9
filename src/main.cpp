#include "task1.h"
#include "task2.h"
#include "task3.h"


void testTask1()
{
    std::cout << "<<<<< Task 1 >>>>>";
    std::cout << std::endl;

    std::vector<std::string> startArray = {"Python", "Java", "Swift", "Assembler", "Haskell"};

    std::vector<std::string> sortedByLetterUp = firstLetterSortingUp(startArray);
    std::cout << "Sorted by FirstLetter (Up)";
    printSortedVector(sortedByLetterUp);
    std::vector<std::string> sortedByLetterDown = firstLetterSortingDown(startArray);
    std::cout << "Sorted by FirstLetter (Down)";
    printSortedVector(sortedByLetterDown);
    std::vector<std::string> sortedByMaxSize = maxSizeSorting(startArray);
    std::cout << "Sorted by Size (Up)";
    printSortedVector(sortedByMaxSize);
    std::vector<std::string> sortedByMinSize = minSizeSorting(startArray);
    std::cout << "Sorted by Size (Down)";
    printSortedVector(sortedByMinSize);
    std::vector<std::string> sortedByLastLetter = lastLetterSorting(startArray);
    std::cout << "Sorted by LastLetter (Down)";
    printSortedVector(sortedByLastLetter);
}


void testTask2()
{
    std::cout << "<<<<< Task 2 >>>>>";
    std::cout << std::endl;

    std::vector<std::string> startArray = {"Python", "Java", "Swift", "Assembler", "Haskell"};
    bubbleSortingByThreads(startArray);
    std::cout << std::endl;
}


void testTask3()
{
    std::cout << "<<<<< Task 3 >>>>>";
    std::cout << std::endl;
    shopService();
}


int main()
{
    testTask1();
    testTask2();
    testTask3();
}
