#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
void BubbleSort(T begin, T end, bool (*comp)(const string& lhs, const string& rhs)) {
	for (auto i = end; i > begin; i--){
		for (auto j = begin; j < i - 1; j++) {
			if (comp(*j, *(j + 1))) {
				swap(*j, *(j + 1));
			}
		}
	}
}

template<class T>
ostream& operator<<(ostream& out, const vector<T>& data) {
	for (const T& i : data) {
		out << i << " ";
	}
	return out;
}

int main() {
	vector<string> data = { "tower", "city", "house", "home", "data", "class", "ability", "box" };
	cout << data << endl;

	BubbleSort(data.begin(), data.end(), [](const string& lhs, const string& rhs) {return lhs < rhs; });
	cout << data << endl;

	BubbleSort(data.begin(), data.end(), [](const string& lhs, const string& rhs) {return lhs > rhs; });
	cout << data << endl;

	BubbleSort(data.begin(), data.end(), [](const string& lhs, const string& rhs) {return lhs[0] < rhs[0]; });
	cout << data << endl;

	BubbleSort(data.begin(), data.end(), [](const string& lhs, const string& rhs) {return lhs[0] > rhs[0]; });
	cout << data << endl;

	BubbleSort(data.begin(), data.end(), [](const string& lhs, const string& rhs) {return lhs[2] > rhs[2]; });
	cout << data << endl;

	return 0;
}