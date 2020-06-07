#pragma once
#include <iostream>
#include <vector>


std::vector <std::string> bubble(std::vector<std::string> arr, bool comp(std::string s1, std::string s2)) {
	for (int i = 0; i < arr.size()-1; i++)
		for (int j = 0; j < arr.size() - i-1; j++)
			if (comp(arr[j], arr[j+1])) {
				auto temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
	return arr;
}
