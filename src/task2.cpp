#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex Mut;
condition_variable cv;
bool flag = true;
bool finished = false;

template<class t>
ostream& operator<<(ostream& out, vector<t>v) {
	for (const t& f : v) {
		out << f << " ";
	}
	return out;
}
void bubbleSort(vector<string>& a, bool comparator(string a, string b)) {
	for (int i = 0; i < (int)a.size() - 1; i++) {
		for (int j = 0; j < (int)a.size() - 1 - i; j++) {
			unique_lock<mutex> lk(Mut);
			cv.wait(lk, []() {return !flag; });
			if (!comparator(a[j], a[j + 1])) {
				swap(a[j], a[j + 1]);
				flag = true;
				cv.notify_all();
			}
		}
	}
	lock_guard<std::mutex> lk(Mut);
	finished = true;
	flag = true;
	cv.notify_all();
}

int main2() {
vector<string>strings = { "qwer", "qw", "qwerty", "q", "qwe", "qwert", "trewqyueq", "qweerte" };
thread sortThread(bubbleSort, ref(strings), [](string a, string b) {return b.size() > a.size(); });
while (true) {
	unique_lock<mutex> lk(Mut);
	cv.wait(lk, []() {return flag; });
	cout << strings << '\n';
	flag = false;
	if (finished)break;
	cv.notify_one();
}
sortThread.join();
return 0;
}