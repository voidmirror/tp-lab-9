#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unistd.h>

using namespace std;

bool ready = false;
bool swaped = false;
bool print = true;
mutex mtx;
condition_variable convar;

void BubbleSort(vector<string>::iterator begin, vector<string>::iterator end, bool(*lambda)(const string& first, const string& second)) {
	for (auto i = end; i > begin; i--) {
		for (auto j = begin; j < i - 1; j++) {
			unique_lock<mutex> lock(mtx);
			if (swaped) {
				convar.wait(lock, []() { return print; });
			}
			if (lambda(*j, *(j + 1))) {
				swap(*j, *(j + 1));
				sleep(1);
				swaped = true;
				print = false;
			}
			lock.unlock();
			convar.notify_all();
		}
	}

	unique_lock<mutex> lock(mtx);
	if (swaped) {
		convar.wait(lock, []() { return print; });
	}
	ready = true;
	lock.unlock();
	convar.notify_all();
}

int main() {
	vector<string> strings = { "a", "c", "f", "g", "db", "e", "b", "x" };
	for (string i : strings) {
		cout << i << " ";
	}
	cout << endl;

	thread thread0(BubbleSort, strings.begin(), strings.end(), [](const string& first, const string& second) {return first > second; });

	while (true) {
		unique_lock<mutex> lock(mtx);
		convar.wait(lock, []() {return swaped || ready; });
		if (ready) break;

		for (string i : strings) {
			cout << i << " ";
		}
		cout << endl;

		print = true;
		swaped = false;
		lock.unlock();
		convar.notify_all();
	}

	thread0.join();
	return 0;
}