#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <mutex>
#include <string>

void bubbleSort(std::string *array, int size, bool cmp(std::string a, std::string b))
{
    std::mutex om;
    std::lock_guard<std::mutex> lm(om);
    for (int i = 0; i < size; i++)
    {
        bool flag = true;
        std::thread tr([size](std::string* array)
        {
            for (int i = 0; i < size; i++)
                std::cout<<array[i]<<" ";
            std::cout << std::endl;
        }, array);
        tr.join();

        for (int j = 0; j < size - (i + 1); j++)
        {
            if (cmp(array[j], array[j+1]))
            {
                flag = false;
                std::swap (array[j], array[j + 1]);
            }
        }
        if (flag)
            break;
    }
}

int main()
{
    int size = 7;
    std::string array [7] = {"из", "колхозной", "молодёжи", "панковал", "один", "лишь", "я"};

    std::thread t(bubbleSort, array, size, [](std::string a, std::string b){return a<b;});
    t.join();

    return 0;
}
