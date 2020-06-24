#pragma once
#include <string>
#include <vector>
#include <functional>

using namespace std;

void BubbleSort(
	vector<string>::iterator vBegin, 
	vector<string>::iterator vEnd, 
	const function<int(const string&, const string&)>& comparator);