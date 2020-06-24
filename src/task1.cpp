#include "task.h"


void PrintArray(vector<string>& arr)
{
	for (string elem : arr) {
		cout << elem << " ";
	}
	cout << endl;
}

template<typename F>
void BubbleSort(vector<string>& arr, F Comparator)
{
	size_t size = arr.size();

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size - i - 1; j++)
			if (!Comparator(arr[j], arr[j + 1]))
				swap(arr[j], arr[j + 1]);
}


int main()
{
	vector<string> arr = { "avcv","asfdssadg","a","bd","123" };
	PrintArray(arr);

	auto lenComparator = [](string& a, string& b)
	{
		return a.length() < b.length();
	};

	auto alphabetComparator = [](string& a, string& b)
	{
		return a < b;
	};

	auto firstLetterComparator = [](string& a, string& b)
	{
		return a[0] < b[0];
	};

	auto lastLetterComparator = [](string& a, string& b)
	{
		return a[a.length() - 1] < b[b.length() - 1];
	};

	auto reverseComparator = [](string& a, string& b)
	{
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		return a < b;
	};

	BubbleSort(arr, lenComparator);
	PrintArray(arr);

	BubbleSort(arr, alphabetComparator);
	PrintArray(arr);

	BubbleSort(arr, firstLetterComparator);
	PrintArray(arr);

	BubbleSort(arr, lastLetterComparator);
	PrintArray(arr);

	BubbleSort(arr, reverseComparator);
	PrintArray(arr);
}