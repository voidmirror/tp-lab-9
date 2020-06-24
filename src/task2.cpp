#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

mutex mtx;
bool stop = true;
bool mainThread = true;
bool printElements = false;
condition_variable condition;

template <typename Cmp>
void bubbleSort(vector<string>& arr, Cmp comparator) {
	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = 0; j < arr.size() - i - 1; j++) {
			unique_lock<mutex> lock(mtx);
			condition.wait(lock, [] {return printElements; });
			if (comparator(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
			mainThread = true;
			printElements = false;
			condition.notify_all();
		}
	}
	stop = false;
}

int main() {
	vector<string> lines = { "first", "second", "programming", "wallpaper", "big", "apple", "amazing" };
	thread thrd(bubbleSort<bool(*)(string&, string&)>, ref(lines), [](string& a, string& b) {return a.length() < b.length(); });

	while (stop) {
		unique_lock<mutex> lock(mtx);
		condition.wait(lock, [] {return mainThread; });
		for (size_t i = 0; i < lines.size(); i++) {
			cout << " " << lines[i] << " ";
		}
		cout << "\n";
		mainThread = false;
		printElements = true;
		condition.notify_all();
	}
	thrd.join();
}