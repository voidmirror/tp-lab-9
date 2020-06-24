#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;

bool finished = false;
bool changed_data = false;
bool data_out = true;
mutex m1x;
condition_variable cv;

void BubbleSort(vector<string>::iterator begin, vector<string>::iterator end, bool(*comp)(const string& lhs, const string& rhs)) {
	for (auto i = end; i > begin; i--) {
		for (auto j = begin; j < i - 1; j++) {
			unique_lock<mutex> lk(m1x);
			if (changed_data) {
				cv.wait(lk, []() { return data_out; });
			}
			if (comp(*j, *(j + 1))) {
				swap(*j, *(j + 1));
				changed_data = true;
				data_out = false;
			}
			lk.unlock();
			cv.notify_all();
		}
	}
	unique_lock<mutex> lk(m1x);
	if (changed_data) {
		cv.wait(lk, []() { return data_out; });
	}
	finished = true;
	lk.unlock();
	cv.notify_all();
}

template<class T>
ostream& operator<<(ostream& out, const vector<T>& data) {
	for (const T& i : data) {
		out << i << " ";
	}
	return out;
}

int main() {
	vector<string> data = { "tower", "city", "house", "home", "data", "class", "ability", "box" };
	cout << data << endl;

	thread t(BubbleSort, data.begin(), data.end(), [](const string& lhs, const string& rhs) {return lhs > rhs; });
	
	while (true) {
		unique_lock<mutex> lk(m1x);
		cv.wait(lk, []() {return changed_data || finished; });
		if (finished) break;
		cout << data << endl;
		data_out = true;
		changed_data = false;
		lk.unlock();
		cv.notify_all();
	}
	
	t.join();
	return 0;
}