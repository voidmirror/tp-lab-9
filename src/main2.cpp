#include "task2.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>

using namespace std;

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

    auto comparator = [](const string& left, const string& right){return left > right;};
    auto *sortingThread = new thread(sorted, ref(strings), comparator);
    auto *loggingThread = new thread(logProcess, ref(strings));

    sortingThread->join();
    loggingThread->join();
}
