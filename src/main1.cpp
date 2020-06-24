#include <task1.h>
#include <algorithm>
using std::ostream;

ostream& operator<<(ostream& out, vector<string> &a) {
    for(auto &x: a) {
       out << x << ' ';
    }
    out << '\n';
    return out;
}

int main() {
    vector<string> s = {"lol", "kek", "aab", "aa", "b", "ca", "test"};
    bubbleSort(s, [](string &a, string &b) {
        return a < b;
    });
    std::cout << s;
    bubbleSort(s, [](string &a, string &b) {
        return a.size() < b.size();
    });
    std::cout << s;
    bubbleSort(s, [](string &a, string &b) {
        return a[0] < b[0];
    });
    std::cout << s;
    bubbleSort(s, [](string &a, string &b) {
        return a[a.size() - 1] < b[b.size() - 1];
    });
    std::cout << s;
    bubbleSort(s, [](string a, string b) {
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());
        return a < b;
    });
    std::cout << s;
    return 0;
}