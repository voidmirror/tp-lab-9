#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> strings = { "Artur", "Seregey", "Veniamin", "Alexey", "Gennady", "Max", "Yn" };


void out(vector<string> strings) {
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;
}

void BubbleSort(vector<string>::iterator begin, vector<string>::iterator end, bool (*lambda)(string& first, string& second)) {
	for (auto i = end; i > begin; i--) {
		for (auto j = begin; j < i - 1; j++) {
			if (lambda(*j, *(j + 1))) { swap(*j, *(j + 1)); }
		}
	}
}

int main() {
	BubbleSort(strings.begin(), strings.end(), [](string& first, string& second) {return first > second; });
	out(strings);

	BubbleSort(strings.begin(), strings.end(), [](string& first, string& second) {return first.size() > second.size(); });
	out(strings);

	BubbleSort(strings.begin(), strings.end(), [](string& first, string& second) {return first[0] > second[0]; });
	out(strings);

	BubbleSort(strings.begin(), strings.end(), [](string& first, string& second) {return first.end() > second.end(); });
	out(strings);

	BubbleSort(strings.begin(), strings.end(), [](string& first, string& second) {return count(first.cbegin(), first.cend(), 'e') > count(second.cbegin(), second.cend(), 'e'); });
	out(strings);

	return 0;
}