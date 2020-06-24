#include <cstring>
#include <iostream>

using namespace std;

#define SIZE 7

void BubbleSort(string mas[], bool cmp(string a, string b)) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE - 1; j++) {
			if (cmp(mas[j], mas[j + 1]))
				swap(mas[j], mas[j + 1]);
		}
	}
	for (int i=0; i < SIZE; i++){
		cout << " " << mas[i] << " ";
	}
	cout << endl;
}

int main() {
	string mas[SIZE] = {"I", "WWn", "not", "nnnnN", "LLLLe", "tRRR", "ANRore"};

	cout << "Sort by first character (small): \n";
	BubbleSort(mas, [](string a, string b) { return a[0] < b[0]; });
	cout << endl;

	cout << "Sort by first character (great): \n";
	BubbleSort(mas, [](string a, string b) { return a[0] > b[0]; });
	cout << endl;

	cout << "Sort by string length (descending): \n";
	BubbleSort(mas, [](string a, string b) { return a.length() < b.length(); });
	cout << endl;

	cout << "Sort by string length (ascending): \n";
	BubbleSort(mas, [](string a, string b) { return a.length() > b.length(); });
	cout << endl;

	cout << "Sort by last character (small): \n";
	BubbleSort(mas, [](string a, string b) { return a[a.length() - 1] < b[b.length() - 1]; });
	cout << endl;

	cout << "Sort by last character (great): \n";
	BubbleSort(mas, [](string a, string b) { return a[a.length() - 1] > b[b.length() - 1]; });
	cout << endl;

	return 0;
}