#include "../include/task1.h"

vector<string> bubbleSort(vector<string> strings, const function<bool(string, string)>& comparator) {
    vector<string> sorted;
    copy(strings.begin(), strings.end(), back_inserter(sorted));
    for (int i = 0; i < sorted.size() - 1; ++i) {
        for (int j = 0; j < sorted.size() - 1; ++j) {
            if (comparator(sorted[j], sorted[j + 1])) {
                swap(sorted[j], sorted[j + 1]);
            }
        }
    }
    return sorted;
}
