#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T, typename TCOMP>
void bubble(T itstart, T itend, const TCOMP& comparator) {
	for (auto i = itstart; i != itend; ++i) {
		for (auto j = itstart; j != itend; ++j) {
			if (comparator(*i, *j)) {
				swap(*i, *j);
			}
		}
	}
}
template<typename T>
void displayVector(vector<T> vec) {
	for (T i : vec) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<string> vec = { "Artem", "artem", "Cpp", "cpp", "test", "persik" };

	cout << "\n#1\n";
	cout << "Vector before sort:\n";
	displayVector(vec);
	bubble(vec.begin(), vec.end(), [](string a, string b) {return a > b; });
	cout << "Vector after sort:\n";
	displayVector(vec);

	cout << "\n#2\n";
	cout << "Vector before sort:\n";
	displayVector(vec);
	bubble(vec.begin(), vec.end(), [](string a, string b) {return a[0] % 4 > b[0] % 4; });
	cout << "Vector after sort:\n";
	displayVector(vec);

	cout << "\n#3\n";
	cout << "Vector before sort:\n";
	displayVector(vec);
	bubble(vec.begin(), vec.end(), [](string a, string b) {return a[0] / 5 >= a[0] / 5; });
	cout << "Vector after sort:\n";
	displayVector(vec);

	cout << "\n#4\n";
	cout << "Vector before sort:\n";
	displayVector(vec);
	bubble(vec.begin(), vec.end(), [](string a, string b) {return a[0] > b[0]; });
	cout << "Vector after sort:\n";
	displayVector(vec);

	cout << "\n#5\n";
	cout << "Vector before sort:\n";
	displayVector(vec);
	bubble(vec.begin(), vec.end(), [](string a, string b) {return a.size() > b.size(); });
	cout << "Vector after sort:\n";
	displayVector(vec);

	return 0;
}