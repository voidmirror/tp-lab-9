#include <iostream>
#include <vector>
#include <string>
using namespace std; 


template<typename T>
void bubbleSortStr(vector<string> &list, T compare) {
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = 0; j < list.size() - i - 1; j++) {
			if (compare(list[j + 1], list[j])) {
				swap(list[j + 1], list[j]);
			}
		}
	}	
}

int main() {	
	vector<string> text = { "hello", "extremelylongword", "wassup", "a-word", "understanding", "halo" };
	
	// First
	bubbleSortStr(text, 
		[](string &word1, string &word2) {
		return word1.size() < word2.size();
	});

	cout << "Sorted by length in ascending order:" << endl;
	for (auto word : text) {
		cout << word << endl;
	}
	cout << endl;

	// Second
	bubbleSortStr(text,
		[](string& word1, string& word2) {
			return word1.size() > word2.size();
		});

	cout << "Sorted by length in descending order:" << endl;
	for (auto word : text) {
		cout << word << endl;
	}
	cout << endl;

	// Third
	bubbleSortStr(text,
		[](string& word1, string& word2) {
			return word1[0] < word2[0];
		});

	cout << "Sorted by first letter in aplhabetic order:" << endl;
	for (auto word : text) {
		cout << word << endl;
	}
	cout << endl;

	// Fourth
	bubbleSortStr(text,
		[](string& word1, string& word2) {
			return word1 < word2;
		});

	cout << "Sorted in aplhabetic order:" << endl;
	for (auto word : text) {
		cout << word << endl;
	}
	cout << endl;

	// Fifth
	bubbleSortStr(text,
		[](string& word1, string& word2) {
			return word1[word1.size() - 1] < word2[word2.size() - 1];
		});

	cout << "Sorted by last letter in aplhabetic order:" << endl;
	for (auto word : text) {
		cout << word << endl;
	}
	cout << endl;

	return 0; 
}