#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

std::mutex mx;
std::condition_variable cv;
bool finished_sort = false;
bool finished_iter = false;
bool printed = true;

template <typename RandIterator, typename Comparator>
void bubble_sort(
	RandIterator first, RandIterator last,
	Comparator comparator
) {
	for (RandIterator right = last - 1; right > first; --right) {
		for (RandIterator left = first; left < right; ++left) {
			std::unique_lock<std::mutex> lk(mx);
			cv.wait(lk, []() { return printed; });
			if (!comparator(*left, *right)) {
				std::swap(*left, *right);
			}
			finished_iter = true;
			printed = false;
			lk.unlock();
			cv.notify_all();
		}
	}
	finished_sort = true;
}

int main() {
	std::vector<std::string> vec = { "hello", "everyone", "who", "watch", "this", "code" };

	std::thread t(bubble_sort<std::vector<std::string>::iterator, bool(*)(const std::string&, const std::string&)>,
		vec.begin(), vec.end(), [](const std::string& a, const std::string& b) {return a < b; });

	while (!finished_sort) {
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, []() { return finished_iter; });
		for (auto s : vec) {
			std::cout << s << " ";
		}
		std::cout << std::endl;
		finished_iter = false;
		printed = true;
		lk.unlock();
		cv.notify_all();
	}

	t.join();

	return 0;
}