#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<mutex>
#include<functional>
#include<condition_variable>

using namespace std; 

mutex mtx;
condition_variable condition;
bool isFinished = false, isPrinted = false, isSorted = true;

template<typename T>
void BubbleSort(vector<string>& strings, T comparator) {
	for (size_t i = 0; i < strings.size(); i++) {
		for (size_t j = 0; j < strings.size() - i - 1; j++) {
			unique_lock<mutex> lock(mtx);
			condition.wait(lock, [] { return isPrinted; });
			if (!comparator(strings[j], strings[j + 1])) {
				swap(strings[j], strings[j + 1]);
			}
			isPrinted = false;
			isSorted = true;
			condition.notify_all();
		}
	}
	isFinished = true;
}

int main() {
	vector<string> strings = { "aaaa", "a", "aaaaaaa", "ba", "cab", "abc", "acb", "da", "davcf", "ab" };
	auto comparator = [](const string & first, const string & second) { return first < second; };
	thread t(BubbleSort<decltype(comparator)>, ref(strings), comparator);
	while (!isFinished) {
		unique_lock<mutex> lock(mtx);
		condition.wait(lock, [] {return isSorted; });
		for (string i : strings) {
			cout << i << " ";
		}
		cout << endl;
		isPrinted = true;
		isSorted = false;
		condition.notify_all();
	}
	t.join();
	return 0;
}