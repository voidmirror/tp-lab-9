//
// Created by Ivan Razzhivin  on 21.06.2020.
//

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;


template<typename T>
void bubble_sort(std::vector<T>& seqc, std::function<bool(T, T)> comparator)
{

    if (seqc.empty())
        return;


    bool srt = true;

    for (unsigned int i = 0; i < seqc.size(); i++)
    {
        for (unsigned int j = 0; j < seqc.size() - i - 1; j++)
        {
            if (comparator(seqc[j], seqc[j + 1]) == 1)
            {
                swap(seqc[j], seqc[j + 1]);
                srt = false;
            }
        }
        if (srt)
            return;
    }
}


//*
int main(int argc, char *argv[]) 
{
    std::vector<std::string> phrases{ "test", "lorem", "ipsum", "a", "aa", "bb", "123" };
    std::cout << "Input text: ";
    for_each(phrases.begin(), phrases.end(), [](std::string x)
        { 
            std::cout << x << " ";
        });
    std::cout << std::endl;

    std::cout << "Bubble sorting for input text from down to up by length:";
    bubble_sort<std::string>(phrases, [](string a, string b)
        {
            if (a.length() > b.length())
                return true;
            else
                return false;
        });

    for_each(phrases.begin(), phrases.end(), [](std::string x)
        {
            std::cout << x << " ";
        });
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
