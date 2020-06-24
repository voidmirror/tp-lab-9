#pragma once 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void bubble_sort(vector<string> data, bool comparator(string a, string b))
{
	for (int i = data.size() - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (comparator(data[j], data[j + 1]))
			{
				swap(data[j], data[j + 1]);
			}
		}
	}

	for (auto i : data)
	{
		cout << i << " ";
	}
	cout << endl;
}
