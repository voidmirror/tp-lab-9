#include "task3.h"
#include "task2.h"
#include "task1.h"


int main() {
	srand(time(NULL));
	startTask1();
	startTask2();
	startTask3();
	system("pause");
	return 0;
}

/*

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>

std::mutex mutex;
std::condition_variable cv;
bool printed(false);
bool sorted(true);
bool finished(false);

void bubble_sort(std::vector<std::string> & arr, bool comparator(const std::string &, const std::string &));

int main() {
	std::vector <std::string> string_vector = { "deb", "dab", "rreeeee", "Ian" };
	std::thread t = std::thread(
		bubble_sort, 
		std::ref(string_vector), 
		[](const std::string & a, const std::string & b) {return a.size() > b.size();}
	);
	while (!finished) {
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [] { return sorted; });
		sorted = false;
		for (auto i : string_vector) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
		printed = true;
		lock.unlock();
		cv.notify_all();
	}
	t.join();
	system("pause");
	return 0;
}

void bubble_sort(std::vector<std::string> & arr, bool comparator(const std::string &, const std::string &)) {
	for (size_t i = 0; i < arr.size(); i++) {
		std::unique_lock <std::mutex> lock(mutex);
		cv.wait(lock, [] { return printed; });
		for (size_t j = 0; j < arr.size() - i - 1; j++) {
			if (comparator(arr[j], arr[j + 1])) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
		sorted = true;
		printed = false;
		lock.unlock();
		cv.notify_all();
	}
	finished = true;
}
*/