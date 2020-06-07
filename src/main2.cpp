#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <algorithm>
#include <mutex>
#include <condition_variable>

using namespace std;
bool stop_printing_fl = 0;
bool finished_printing_fl = 1;
bool finished_sorting_fl = 0;

mutex mtx;
condition_variable cv;

void bubbleSortStr(vector<string>& list, bool compare(const string& word1, const string& word2)) {
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = 0; j < list.size() - i - 1; j++) {
			unique_lock<mutex> lk(mtx);
			cv.wait(lk, []() { // ждем, пока поток с печатью после очередной итерации поднимет флаг
				return finished_printing_fl;
				});
			finished_printing_fl = 0;
			if (compare(list[j + 1], list[j])) {
				swap(list[j + 1], list[j]);
			}
			finished_sorting_fl = 1; // прошла итерация, поднимаем флаг
			cv.notify_one();
		}
	}
	stop_printing_fl = 1;
}

int main() {
	vector<string> text = { "hello", "extremelylongword", "wassup", "a-word", "understanding", "halo" };

	thread th1(bubbleSortStr, ref(text),
		[](const string& word1, const string& word2) {
		return word1.size() < word2.size();
		});

	while (!stop_printing_fl) {
		unique_lock<mutex> lk(mtx);

		cv.wait(lk, []() { // ждем, пока поток с сортировкой после очередной итерации поднимет флаг
			return finished_sorting_fl; 
		});
		finished_sorting_fl = 0;
		for (auto word : text) {
			cout << word << " ";
		}
		cout << endl;
		finished_printing_fl = 1;
		cv.notify_one();
	}

	th1.join();
	return 0;
}



