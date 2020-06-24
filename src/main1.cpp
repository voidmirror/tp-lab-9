#include "task1.h"


void main()
{
	vector<string> array_to_sort = { "me", "cool", "oohh", "all", "family", "summer", "not", "exh" };
	vector<string> sorted_array;

	cout << "sort by first letter" << endl;
	sorted_array = bubble_sort( array_to_sort, [](string str1, string str2) {return str1[0] > str2[0]; });
	for (auto i : sorted_array)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	cout << "sort by last letter" << endl;
	sorted_array = bubble_sort(array_to_sort, [](string str1, string str2) {return str1[str1.size() - 1] > str2[str2.size() - 1]; });
	for (auto i : sorted_array)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	cout << "sort by size" << endl;
	sorted_array = bubble_sort(array_to_sort, [](string str1, string str2) {return str1.size() > str2.size(); });
	for (auto i : sorted_array)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	cout << "sort by h counter" << endl;
	sorted_array = bubble_sort(array_to_sort, [](string str1, string str2)
	{return count(str1.begin(), str1.end(), 'h') > count(str2.begin(), str2.end(), 'h'); });
	for (auto i : sorted_array)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	cout << "sort" << endl;
	sorted_array = bubble_sort(array_to_sort, [](string str1, string str2) {return str1 > str2; });
	for (auto i : sorted_array)
	{
		cout << i << " ";
	}
}