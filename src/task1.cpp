#include <iostream>
#include <vector>
#include <string>

using namespace std;


void BubbleSort(vector<string>& arr, bool comparator(const string& a, const string& b))
{
	vector<string>::iterator pos;
	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		for (size_t j = 0; j < arr.size() - 1 - i; j++)
		{
			if (comparator(arr[j], arr[j + 1]))
				swap(arr[j], arr[j + 1]);
		}
	}
	for (pos = arr.begin(); pos != arr.end(); pos++)
	{
		cout << *pos << " ";
	}
	cout << endl;
}

int main()
{
	vector<string> vec = {"summer", "hse", "exams", "weekdays", "or", "weekends"};

	cout << "sort by decrease : " << endl;
	BubbleSort(vec, [](const string& a, const string& b) {return a < b; });

	cout << "\nsort by increase : " << endl;
	BubbleSort(vec, [](const string& a, const string& b) {return a > b; });

	cout << "\nsort by size increase : " << endl;
	BubbleSort(vec, [](const string& a, const string& b) {return a.size() > b.size(); });

	cout << "\nsort by size decrease : " << endl;
	BubbleSort(vec, [](const string& a, const string& b) {return a.size() < b.size(); });

	cout << "\nsort by last symbol increase : " << endl;
	BubbleSort(vec, [](const string& a, const string& b) {return  *(a.end() - 1)> *(b.end() - 1); });

	getchar();
	return 0;
}