#pragma once
#include <string>
#include <vector>
#include <functional>
#include <mutex>

using namespace std;

void BubbleSortMtx(
	vector<string>::iterator vBegin,
	vector<string>::iterator vEnd,
	const function<int(const string&, const string&)>& comparator);