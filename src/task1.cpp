#include<iostream>
#include<vector>
#include<string>

using namespace std;

template<typename T>
void BubbleSort(vector<string>& strings, T comparator) {
	for (size_t i = 0; i < strings.size(); i++) {
		for (size_t j = 0; j < strings.size() - i - 1; j++) {
			if (!comparator(strings[j], strings[j + 1])) {
				swap(strings[j], strings[j + 1]);
			}
		}
	}
}

int main() {
	vector<string> strings = { "aaaa", "a", "aaaaaaa", "ba", "cab", "abc", "acb", "da", "davcf", "ab" };
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
	BubbleSort(strings, [](string & first, string & second) {return first.length() < second.length(); });
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
	BubbleSort(strings, [](string & first, string & second) {return first[0] < second[0]; });
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
	BubbleSort(strings, [](string & first, string & second) {return first[first.length() - 1] < second[second.length() - 1]; });
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
	BubbleSort(strings, [](string & first, string & second) {return first < second; });
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
	BubbleSort(strings, [](string & first, string & second) {reverse(first.begin(), first.end()); reverse(second.begin(), second.end()); return first < second; });
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}