#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class F>
void bubbleSort(vector<string>& strs, F comparator) {
	int n = strs.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (comparator(strs[j], strs[j + 1])) {
				std::swap(strs[j], strs[j + 1]);
			}
		}
	}
}

ostream& operator<<(ostream& os, vector<string>& strings) {
	for (auto i : strings) {
		os << i << " ";
	}
	os << endl;
	return os;
}

int main() {
	vector<string> strings = { 
		"could", 
		"igess", 
		"something", 
		"abc", 
		"Loop", 
		"sorting", 
		"STOMA", 
		"Layer" };
	cout << "SOURCE:" << endl;
	cout << strings << endl << endl;
	cout << "SORTING:" << endl;
	bubbleSort(strings, [](const string& first, const string& second) {return first > second; });
	cout << "By Alphabet:  " << endl << strings;
	bubbleSort(strings, [](const string& first, const string& second) {return first < second; });
	cout << "By Alphabet Inverse:   " << endl << strings;
	bubbleSort(strings, [](const string& first, const string& second) {return first.front() > second.front(); });
	cout << "By First symbol:   " << endl << strings;
	bubbleSort(strings, [](const string& first, const string& second) {return first.size() > second.size(); });
	cout << "By Size:   " << endl << strings;
	bubbleSort(strings, [](const string& first, const string& second) {return first.size() < second.size(); });
	cout << "By Size Inverse:   " << endl << strings;
	
}