#include "task1.h"
#include <iostream>

int main() {
	vector<function<int(const string &, const string &)>> comparators{
		[](const string& s1, const string& s2) -> int { return s1.compare(s2); },
		[](const string& s1, const string& s2) -> int { return s2.compare(s1); },
		[](const string& s1, const string& s2) -> int { return s1.size() - s2.size(); },
		[](const string& s1, const string& s2) -> int { return s2.size() - s1.size(); },
		[](const string& s1, const string& s2) -> int { return s1.back() - s2.back(); }
	};

	vector<string> arr = { "cdefg", "aba", "dz", "bbbb", "e" };
	cout << "Before sort: " << endl;
	for (auto i = arr.begin(); i < arr.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	for (int func = 0; func < comparators.size(); func++) {
		BubbleSort(arr.begin(), arr.end(), comparators[func]);
		cout << "Sort " << func + 1 << ":" << endl;
		for (auto i = arr.begin(); i < arr.end(); i++) {
			cout << *i << " ";
		}
		cout << endl;
	}

	return 0;
}
