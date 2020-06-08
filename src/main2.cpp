#include "task2.h"
#include <iostream>

extern mutex sort_mtx;
extern condition_variable sort_cv;
extern bool sort_step_done;
extern bool main_step_done;
extern bool sorting_done;

int main() {
	vector<string> arr = { "55555", "4444", "333", "22", "1" };
	
	thread sort_th(BubbleSortMtx, arr.begin(), arr.end(), [](string s1, string s2) -> int { return s1.size() - s2.size(); });
	while (!sorting_done) {
		unique_lock<mutex> lk(sort_mtx);
		sort_cv.wait(lk, []() { return sort_step_done; });
		sort_step_done = false;
		for (auto i = arr.begin(); i < arr.end(); i++) {
			cout << *i << " ";
		}
		cout << endl;
		main_step_done = true;
		sort_cv.notify_one();
	}

	sort_th.join();
	return 0;
}