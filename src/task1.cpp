#include "task1.h"
#include <algorithm>

void BubbleSort(vector
	<string>::iterator vBegin, 
	vector<string>::iterator vEnd, 
	const function<int(const string&, const string&)>& comparator
) {
	for (auto i = vBegin; i < vEnd - 1; i++) {
		for (auto j = vEnd - 1; j > i; j--) {
			if (comparator(*j, *(j - 1)) < 0) {
				iter_swap(j, j - 1);
			}
		}
	}
}