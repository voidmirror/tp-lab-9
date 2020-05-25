#include <iostream>
#include <functional>
#include <vector>
#include <string>


using namespace std;

template<class T>
ostream& operator<<(ostream& out, vector<T>v) {
	for (T t : v) {
		out << t << " ";
	}
	return out;
}

template<class T, class C>
vector<T> bubbleSort(vector<T> v, C comparator) {
	for (int i = 0; i < (int)v.size() - 1; i++) {
		for (int j = 0; j < (int)v.size() - 1 - i; j++) {
			if (!comparator(v[j], v[j + 1])) {
				swap(v[j], v[j + 1]);
			}
		}
	}
	return v;
}

void task1() {
	vector<string>v = { "abc", "ABC", "BCD", "B", "XXX", "abb", "b", "bb", "ab", "" };
	cout << bubbleSort(v, [](const string& a, const string& b) {return a < b; }) << '\n';
	cout << bubbleSort(v, [](const string& a, const string& b) {return a > b; }) << '\n';
	cout << bubbleSort(v, [](const string& a, const string& b) {return a.size() < b.size(); }) << '\n';
	cout << bubbleSort(v, [](const string& a, const string& b) {return a.size() > b.size(); }) << '\n';
	cout << bubbleSort(v, [](string a, string b) {return !a.empty() && !b.empty() && (a.back() < b.back()); }) << '\n';
}

int main() {
	task1();
}