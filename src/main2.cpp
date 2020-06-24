//
// Created by Ivan Razzhivin  on 21.06.2020.
//

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <thread>
#include <mutex>

using namespace std;


template<typename T>
void bubble_sort(std::vector<T>* seqc, std::function<bool(T, T)> comparator) 
{

    if (seqc->empty())
        return;

    std::mutex output_mutex;
    std::lock_guard<std::mutex> lock(output_mutex);
    bool srt = true;
    int tmp = 0;

    for (unsigned int i = 0; i < seqc->size(); i++)
    {
        std::thread inner_thread([&output_mutex, &tmp](vector<T>* seqc)
            {
            std::for_each((*seqc).begin(), (*seqc).end(), [](T x) 
                { 
                    std::cout << x << " "; 
                });

            std::cout << "  " << tmp << "-th iteration" << std::endl;
            tmp++;
            }, seqc);
        inner_thread.join();

        for (unsigned int j = 0; j < (*seqc).size() -1 - i; j++) {
            if (comparator((*seqc)[j], (*seqc)[j + 1])) {
                swap((*seqc)[j], (*seqc)[j + 1]);
                srt = false;
            }
        }
        if (srt)
            return;
    }
}


int main(int argc, char* argv[]) {
    std::vector<std::string> phrases{ "test", "lorem", "ipsum", "a", "aa", "bb", "123" };
    std::cout << "Input text: ";
    for_each(phrases.begin(), phrases.end(), [](std::string x) 
        {
            std::cout << x << " "; 
        });
    std::cout << std::endl;

    //1
    cout << "Bubble sorting for input text from up to down (cmp):";
    thread thread1(bubble_sort<std::string>, &phrases, [](std::string a, std::string b) 
        {
        if (a < b)
            return true;
        else
            return false;
        });
    thread1.join();

    for_each(phrases.begin(), phrases.end(), [](std::string x) 
        {
            std::cout << x << " "; 
        });
    std::cout << std::endl;

   

    return EXIT_SUCCESS;;
}
