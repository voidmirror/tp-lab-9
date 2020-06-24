#include "task1.h"

#include <iostream>
#include <algorithm>

using namespace std;

string lowercase(string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return str;
}

bool contains(char element, vector<char> data) {
    return std::find(data.begin(), data.end(), element) != data.end();
}

int main() {
    vector<string> strings = {
            "cityward",
            "nonskeletal",
            "loment",
            "lotze",
            "conceptualising",
            "uncoagulative",
            "proextension",
            "siris",
            "heartburning",
            "shabbiest"
    };

    // ascending
    cout << "\nascending\n" << endl;

    vector<string> sorted = bubbleSort(strings, [](const string& left, const string& right){return left > right;});

    for (const string& str : sorted) {
        cout << str << endl;
    }

    // descending
    cout << "\ndescending\n" << endl;

    sorted = bubbleSort(strings, [](const string& left, const string& right){return left < right;});

    for (const string& str : sorted) {
        cout << str << endl;
    }

    // by string length ascending
    cout << "\nlength ascending\n" << endl;

    sorted = bubbleSort(strings, [](const string& left, const string& right){return left.size() < right.size();});

    for (const string& str : sorted) {
        cout << str << endl;
    }

    // by string length descending
    cout << "\nlength descending\n" << endl;

    sorted = bubbleSort(strings, [](const string& left, const string& right){return left.size() > right.size();});

    for (const string& str : sorted) {
        cout << str << endl;
    }


    // by vowels num
    cout << "\nvowels num\n" << endl;

    vector<char> vowels = {'a', 'e', 'y', 'u', 'i', 'o'};

    sorted = bubbleSort(strings, [vowels](const string& left, const string& right){
        int vowelsleft = 0, vowelsright = 0;
        string lowerleft = lowercase(left);
        string lowerright = lowercase(right);

        for(char letter: lowerleft) {
            if (contains(letter, vowels)) {
                vowelsleft += 1;
            }
        }

        for(char letter: lowerright) {
            if (contains(letter, vowels)) {
                vowelsright += 1;
            }
        }

        return vowelsleft > vowelsright;
    });

    for (const string& str : sorted) {
        cout << str << endl;
    }

}
