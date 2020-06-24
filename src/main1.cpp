#include "task1.h"

int main()
{
	vector<string> data_for_sort = { "sea", "turtle", "named", "Natashka", "LOOK!", "Oo", "2000", "OMG" };
	cout << "Before sort:" << endl;
	for (auto i : data_for_sort)
	{
		cout << i << " ";
	}
	cout << endl;

	cout << endl << "Sort (1) ~ alph :" << endl;
	bubble_sort(data_for_sort, [](string a, string b) { return a > b; });
	cout << endl;

	cout << "Sort (2) ~ size <- :" << endl;
	bubble_sort(data_for_sort, [](string a, string b) {	return a.size() < b.size(); });
	cout << endl;

	cout << "Sort (3) ~ size -> :" << endl;
	bubble_sort(data_for_sort, [](string a, string b) { return a.size() > b.size(); });
	cout << endl;

	cout << "Sort (4) ~ first letter :" << endl;
	bubble_sort(data_for_sort, [](string a, string b) {	return a[0] > b[0]; });
	cout << endl;

	cout << "Sort (5) ~ reverse :" << endl;
	bubble_sort(data_for_sort, [](string a, string b) {	return a != b; });
	cout << endl;

	return 0;
}
