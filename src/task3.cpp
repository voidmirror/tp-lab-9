#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

bool sort_completed{ false };
bool vector_displayed{ true };
bool sort_step_completed{false};
mutex mt;
condition_variable cv;

template<typename T, typename TCOMP>
void bubble(T itstart, T itend, const TCOMP& comparator) {
	for (auto i = itstart; i != itend; ++i) {
		for (auto j = itstart; j != itend; ++j) {
			unique_lock<mutex> ul(mt);
			cv.wait(ul, []() {return vector_displayed; });

			if (comparator(*i, *j)) {
				swap(*i, *j);
			}

			vector_displayed = false;
			sort_step_completed = true;
			ul.unlock();
			cv.notify_one();

		}
	}
	sort_completed = true;
}

template<typename T>
void displayVector(vector<T> vec) {
	for (T i : vec) {
		cout << i << " ";
	}
	cout << endl;
}


int main() {	
	vector<string> vec = { "Artem", "artem", "Cpp", "cpp", "Jejejej", "lilpip", "Jojo" };
	thread t(bubble<vector<string>::iterator, bool(*)(string, string)>, vec.begin(), vec.end(), [](string a, string b) {return a.size() > b.size(); });
	while (!sort_completed) {
		unique_lock<mutex> ul(mt);
		cv.wait(ul, []() {return sort_step_completed; });
		displayVector(vec);
		vector_displayed = true;
		sort_step_completed = false;
		ul.unlock();
		cv.notify_one();
	}


	t.join();
	return 0;
}