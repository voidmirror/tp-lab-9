#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std; 

template <typename F>

void Bubblesort(vector<string>& vector, F Comparator)
{
	for (size_t i = 0; i < vector.size(); i++) {
		for (size_t j = 0; j < vector.size() - i - 1; j++) {
			if (!Comparator(vector[j], vector[j + 1])) {
				swap(vector[j], vector[j + 1]);
			}
		}
	}
}


int main() {
	vector<string> vector1 = { "fds", "f0fds", "fdds", "ggfd", "asd"};
	vector<string> vector3 = { "test12", "test1", "test3222", "test444"};
	
	Bubblesort(vector1, [](string& a, string& b) { return a < b; });
	for (auto s : vector1) {
		cout << s << "  ";
	}
	cout << endl;

	Bubblesort(vector3, [](string& a, string& b) { return a < b; });
	cout << "---------------------------------------------------" << endl;
	for (auto s : vector3) {
		cout << s << "  ";
	}
	cout << endl;

	Bubblesort(vector3, [](string& a, string& b) { return a.length() < b.length(); });
	cout << "---------------------------------------------------" << endl;
	for (auto s : vector3) {
		cout << s << "  ";
	}
	cout << endl;

	Bubblesort(vector3, [](string& a, string& b) { reverse(a.begin(), a.end()); reverse(b.begin(), b.end()); return a < b; });
	cout << "---------------------------------------------------" << endl;
	for (auto s : vector3) {
		cout << s << "  ";
	}
	cout << endl;


	Bubblesort(vector3, [](string& a, string& b) { return a[0] > b[0];  });
	cout << "---------------------------------------------------" << endl;
	for (auto s : vector3) {
		cout << s << "  ";
	}
	cout << endl;
}
