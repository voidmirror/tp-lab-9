#ifndef _TASK_1_H_
#define _TASK_1_H_

#include <algorithm>
#include <cstdint>

template<typename T>
void BubbleSort(T* array, int32_t arrayLength, int32_t(*comparsion)(T *left, T *right))
{
    for (int32_t j = 0; j < arrayLength; j++)
    {
        bool anySwaps = false;
        for (int32_t i = 0; i < arrayLength - j - 1; i++)
        {
            if (comparsion(array + i, array + i + 1) > 0)
                std::swap(array[i], array[i + 1]), anySwaps = true;
        }

        if (!anySwaps)
            return;
    }
};

template<typename T>
void BubbleSort(T *array, int32_t arrayLength, int32_t(*comparsion)(T left, T right))
{
    for (int32_t j = 0; j < arrayLength; j++)
    {
        bool anySwaps = false;
        for (int32_t i = 0; i < arrayLength - j - 1; i++)
        {
            if (comparsion(array [i], array[i + 1]) > 0)
                std::swap(array[i], array[i + 1]), anySwaps = true;
        }

        if (!anySwaps)
            return;
    }
};

#endif // _TASK_1_H_
