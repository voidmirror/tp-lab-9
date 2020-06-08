#include "task2.h"
#include <algorithm>

mutex sort_mtx;
condition_variable sort_cv;
bool sort_step_done = true;
bool main_step_done = false;
bool sorting_done = false;

void BubbleSortMtx(vector
	<string>::iterator vBegin,
	vector<string>::iterator vEnd,
	const function<int(const string&, const string&)>& comparator
) {

	for (auto i = vBegin; i < vEnd - 1; i++) {
		for (auto j = vEnd - 1; j > i; j--) {
			unique_lock<mutex> lk(sort_mtx);
			sort_cv.wait(lk, []() { return main_step_done; });
			main_step_done = false;
			if (comparator(*j, *(j - 1)) < 0) {
				iter_swap(j, j - 1);
			}
			sort_step_done = true;
			sort_cv.notify_one();
		}
	}
	sorting_done = true;
}