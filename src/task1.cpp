#include <iostream>
#include <string>
#include <vector>

using namespace std;


void bubble_sort(vector<string> &a, bool comp(string a, string b))
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		for (int j = 1; j < a.size(); j++) 
		{
			if (comp(a[j - 1], a[j])) 
			{
				swap(a[j - 1], a[j]);
			}
		}
	}
}

int main1()
{
	vector<string> vec = { "1", "a", "abcde", "qwerty", "09", "zxc", "C++", "ec9" };
	
	cout << "Default comparator\n";
	bubble_sort(vec, [](string a, string b) {return a > b; });
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ';
	}
	cout << '\n';

	cout << "Size comparator\n";
	bubble_sort(vec, [](string a, string b) {return a.size() > b.size(); });
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ';
	}
	cout << '\n';

	cout << "First character comparator\n";
	bubble_sort(vec, [](string a, string b) {return a[0] > b[0]; });
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ';
	}
	cout << '\n';

	cout << "Last character comparator\n";
	bubble_sort(vec, [](string a, string b) {return a[a.size() - 1] > b[b.size() - 1]; });
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ';
	}
	cout << '\n';

	cout << "Reverse comparator\n";
	bubble_sort(vec, [](string a, string b) {return a < b; });
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ';
	}
	cout << '\n';
	return 0;
}

//int main()
//{
//	main1();
//}