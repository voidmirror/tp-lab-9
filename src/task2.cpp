#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mx;
condition_variable cv;
bool main_flag = true;
bool finished = false;

template<class T>
ostream& operator<<(ostream& out, vector<T>v){
	for (const T& t : v) {
		out << t << " ";
	}
	return out;
}

void bubbleSortTask2(vector<string> &v, bool comparator(string a, string b)) {
	for (int i = 0; i < (int)v.size() - 1; i++) {
		for (int j = 0; j < (int)v.size() - 1 - i; j++) {
			unique_lock<mutex> lk(mx);
			cv.wait(lk, []() {return !main_flag; });
			if (!comparator(v[j], v[j + 1])) {
				swap(v[j], v[j + 1]);
				main_flag = true;
				cv.notify_all();
			}
		}
	}
	lock_guard<std::mutex> lk(mx);
	finished = true;
	main_flag = true;
	cv.notify_all();
}

void task2() {
	vector<string>v = { "9", "8", "7", "6", "5", "4", "3", "2", "1", "0" };
	thread sortThread(bubbleSortTask2, ref(v), [](string a, string b) {return a < b; });
	while (true) {
		unique_lock<mutex> lk(mx);
		cv.wait(lk, [](){return main_flag; });
		cout << v << '\n';
		main_flag = false;
		if (finished)break;
		cv.notify_one();
	}
	sortThread.join();
}

int main() {
	task2();
}