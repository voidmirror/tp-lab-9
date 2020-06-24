#include <iostream>
#include <vector>
#include <ctime>
#include <string>


void bubbleSort(std::string *array, int array_size, bool cmp(std::string a, std::string b))
{
    for (int i = 0; i < array_size; i++)
    {
        bool flag = true;
        for (int j = 0; j < array_size - (i + 1); j++)
            if (cmp(array[j], array[j+1]))
            {
                flag = false;
                swap (array[j], array[j + 1]);
            }
        if (flag)
            break;
    }

    for (int i = 0; i < array_size; i++)
        std::cout<<array[i]<<" ";
    std::cout<<std::endl;
}

int main() 
{
    int size = 7;
    std::string array [7] = {"из", "колхозной", "молодёжи", "панковал", "один", "лишь", "я"};

    bubbleSort(array, size, [](std::string a, std::string b){ return a<b; });
    bubbleSort(array, size, [](std::string a, std::string b){ return a>b; });
    bubbleSort(array, size, [](std::string a, std::string b){ return a!=b; });
    bubbleSort(array, size, [](std::string a, std::string b){ return a[0] > b[0];});
    bubbleSort(array, size, [](std::string a, std::string b)->bool{ return b.find(a) != std::string::npos; });

    return 0;
}
