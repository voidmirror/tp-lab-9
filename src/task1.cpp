#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T, class C>
void bubble_sort(vector<T> &obj, C cmp)
{
    for(size_t i = 0; i < obj.size() - 1; i++)
    {
        for(size_t j = 0; j < obj.size() - 1 - i; j++)
        {
            if(cmp(obj[j], obj[j + 1]))
            {
                swap(obj[j], obj[j + 1]);
            }
        }
    }
}

template <class T>
void print(const vector<T> &obj)
{
    for(const auto &value : obj)
    {
        cout << value << " ";
    }
    cout << endl;
}

int main()
{
    vector<string> data;

    data = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    print(data);
    cout << endl;

    cout << "sorted in increasing alphabetical order: "<< endl;
    bubble_sort(data, [](const auto &lhs, const auto &rhs) { return lhs > rhs; });
    print(data);
    cout << endl;

    data = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    cout << "sorted in decreasing alphabetical order: "<< endl;
    bubble_sort(data, [](const auto &lhs, const auto &rhs) { return lhs < rhs; });
    print(data);
    cout << endl;

    data = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    cout << "sorted by first symbol: "<< endl;
    bubble_sort(data, [](const auto &lhs, const auto &rhs) { return lhs[0] > rhs[0]; });
    print(data);
    cout << endl;

    data = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    cout << "sorted by last symbol: "<< endl;
    bubble_sort(data, [](const auto &lhs, const auto &rhs) { return lhs[lhs.size() - 1] > rhs[rhs.size() -1]; });
    print(data);
    cout << endl;

    data = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    cout << "sorted by size: "<< endl;
    bubble_sort(data, [](const auto &lhs, const auto &rhs) { return lhs.size() > rhs.size(); });
    print(data);
    cout << endl;

    vector<int> idata{9, 5, 3, 4, 5, 1, 0, 6, 7, 2};
    print(idata);
    bubble_sort(idata, [](const auto &lhs, const auto &rhs) { return lhs > rhs; });
    print(idata);

    idata = {9, 5, 3, 4, 5, 1, 0, 6, 7, 2};
    bubble_sort(idata, [](const auto &lhs, const auto &rhs) { return lhs < rhs; });
    print(idata);
    cout << endl;





    return 0;
}
