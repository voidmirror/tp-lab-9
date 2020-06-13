#include <string>
#include <vector>
#include <iostream>

using namespace std;

template<class T>
void bubbleSort(vector<string> &vect, T cmp) {
	size_t n = vect.size();
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n - 1; j++) {
			if (!cmp(vect[j], vect[j + 1])) {
				swap(vect[j], vect[j + 1]);
			}
		}
	}
}
void print(vector<string>& vect)
{
	for (auto i : vect) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<string> arr = { "John", "Charles", "Oliver", "Frank", "Peter", "Donald", "Bryan" };
	bubbleSort(arr, [](string &a, string &b) {return a < b; });
	print(arr);
	bubbleSort(arr, [](string &a, string &b) {return a.size() < b.size(); });
	print(arr);
	bubbleSort(arr, [](string &a, string &b) {return a[0] < b[0]; });
	print(arr);
	bubbleSort(arr, [](string &a, string &b) {return a[a.size() - 1] < b[b.size() - 1]; });
	print(arr);
	bubbleSort(arr, [](string a, string b) {return a > b; });
	print(arr);
		
}