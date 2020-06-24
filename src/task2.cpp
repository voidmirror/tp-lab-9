#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>

using namespace std;

mutex mtx;
condition_variable var;
bool printed = false, sorted = true, ended = false;

void print(vector<string>& vect)
{
	for (auto i : vect) {
		cout << i << " ";
	}
	cout << endl;
}


void bubble_sort(vector<string> & arr, bool cmp(const string &, const string &))
{
	for (size_t i = 0; i < arr.size(); i++) {
		unique_lock <mutex> ulock(mtx);
		var.wait(ulock, [] { return printed; });
		for (size_t j = 0; j < arr.size() - i - 1; j++) {
			if (cmp(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
		sorted = true;
		printed = false;
		ulock.unlock();
		var.notify_all();
	}
	ended = true;
}

int main() {
	vector<string> arr = { "John", "Charles", "Oliver", "Frank", "Peter", "Donald", "Bryan" };
	thread th = thread(bubble_sort, ref(arr), [](const string & a, const string & b) {return a > b; });
	while (!ended) {
		unique_lock<mutex> ulock(mtx);
		var.wait(ulock, [] { return sorted; });
		sorted = false;
		print(arr);
		printed = true;
		ulock.unlock();
		var.notify_all();
	}
	th.join();
}