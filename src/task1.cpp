#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T, typename Cmp>
void bubbleSort(vector<T> &arr, Cmp comparator) {
	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = 0; j < arr.size() - i - 1; j++) {
			if (comparator(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	for (size_t i = 0; i < arr.size(); i++) {
		cout << " " << arr[i] << " ";
	}
	cout << "\n";
}

int main() {	
	vector<int> numbers = { 54, 83, 64, 135, 105, -45, 23, 45, 11, 44, 32, 66, 74, 12 };
	vector<string> lines = { "hello", "my", "friends", "banana", "table", "coronavirus"};

	cout << "Sorting numbers in asceding order:\n";
	bubbleSort(numbers, [](int &a, int &b) { return a > b; });

	cout << "\nSorting numbers in desceding order:\n";
	bubbleSort(numbers, [](int &a, int &b) { return a < b; });

	cout << "\nSorting lines by length\n";
	bubbleSort(lines, [](string &a, string &b) { return a.length() > b.length(); });

	cout << "\nSorting lines by first character:\n";
	bubbleSort(lines, [](string &a, string &b) { return a[0] > b[0]; });

	cout << "\nSorting lines by last character:\n";
	bubbleSort(lines, [](string &a, string &b) { return a[a.length() - 1] > b[b.length() - 1]; });
}