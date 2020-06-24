#include "head.h"

using namespace std;

int main(){
	vector<string> inp = { "asjfbiajsbf", "afASFmkk", "154355", "Inincsq", "hey", "zzzzzzzzz", "ABCDE" };
	bubbleSortString(inp, [](string str1, string str2){ return str1.length() < str2.length(); });
	for (auto word : inp)
		cout << word << " ";
	cout << endl;
	bubbleSortString(inp, [](string str1, string str2){ return str1 < str2; });
	for (auto word : inp)
		cout << word << " ";
	cout << endl;
	bubbleSortString(inp, [](string str1, string str2){ return str1.length() > str2.length(); });
	for (auto word : inp)
		cout << word << " ";
	cout << endl;
	bubbleSortString(inp, [](string str1, string str2){ return str1 > str2; });
	for (auto word : inp)
		cout << word << " ";
	cout << endl;
	bubbleSortString(inp, [](string str1, string str2){ return str1[str1.length() - 1] < str2[str2.length() - 1]; });
	for (auto word : inp)
		cout << word << " ";
	cout << endl;
	getchar();
}