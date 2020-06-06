#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

void sortBuble1(vector<string>& vec, function<bool(string, string)> f) {
    int vec_size = vec.size();
    string tmp;
    for (int i = 0; i < vec_size; i++) {
        for (int j = 0; j < (vec_size - i - 1); j++) {
            if (f(vec[j], vec[j + 1])) {
                tmp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = tmp;
            }
        }
    }
}


void print1(vector<string>& vec) {
    for (auto v : vec) {
        cout << v << endl;
    }
    cout << endl;
}


int main()
{
    vector<string> v = { "Ivan", "Petya", "Koly", "Dima", "Misha", "Sasha", "Sergey", "Semen"};

    sortBuble1(v, [](string a, string b) {return (a > b); });
    print1(v);

    sortBuble1(v,[](string a, string b) {return (a.size() < b.size()); });
    print1(v);
    
    sortBuble1(v,[](string a, string b) {return (b.size() % 2 == 0 && a.size() % 2 != 0); });
    print1(v);
    
    sortBuble1(v, [](string a, string b) {return ((int)a[0] > (int)b[0]); });
    print1(v);

    sortBuble1(v, [](string a, string b) {return (a.size() < b.size() && b.size() % 2 == 0 && a.size() % 2 != 0); });
    print1(v);
    return 0;
}