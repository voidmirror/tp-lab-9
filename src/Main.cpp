#define _TASK_1_MAIN_

#ifdef _TASK_1_MAIN_

#include <cstdint>
#include <cctype>
#include <iostream>
#include <string>

#include "Task1.h"

template<typename T>
void PrintArray(T *array, int32_t length)
{
    for (int32_t i = 0; i < length; i++)
        std::cout << array[i] << (i < length - 1 ? ", " : "");
    std::cout << std::endl;
}

int32_t main()
{
    int32_t int32Array[5] = { 4, 1, 3, 5, 2 };
    BubbleSort<int32_t>(int32Array, 5, [](int left, int right) { return left - right; }); // sort in ascending order
    PrintArray(int32Array, 5);
    BubbleSort<int32_t>(int32Array, 5, [](int left, int right) { return right - left; }); // sort in descending order
    PrintArray(int32Array, 5);


    std::string stringArray[5] = { "CCC", "bbbb", "E", "dd", "AAAAA" };
    BubbleSort<std::string>(stringArray, 5, [](std::string *left, std::string *right) { return (int32_t)left->size() - (int32_t)right->size(); }); // compare by length
    PrintArray(stringArray, 5);
    BubbleSort<std::string>(stringArray, 5, [](std::string *left, std::string *right) { return left->compare(*right); }); // compare as usual
    PrintArray(stringArray, 5);
    BubbleSort<std::string>(stringArray, 5, [](std::string *left, std::string *right) { return std::tolower((*left)[0]) - std::tolower((*right)[0]); }); // compare by first symbols casted to lower register
    PrintArray(stringArray, 5);
}

#endif // _TASK_1_MAIN_
