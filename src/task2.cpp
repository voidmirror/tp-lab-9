#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <algorithm>
#include <ctime>

std::mutex mutex;
bool locker = true, isSorting = true;

void sort(std::vector<std::string> &var, bool comp(const std::string a, const std::string b)) {
	for (int i = 0; i < var.size() - 1; i++) {
		for (int j = 0; j < var.size() - i - 1; j++) {
			mutex.lock();
			if (comp(var[j], var[j + 1])) {
				std::swap(var[j], var[j + 1]);
				locker = true;
			}
			mutex.unlock();
		}
	}
	isSorting = false;
}

int main()
{
	std::vector<std::string> var = {
		"could",
		"igess",
		"something",
		"abc",
		"Loop",
		"sorting",
		"STOMA",
		"Layer" };
	std::thread thread(sort, std::ref(var), [](const std::string a, const std::string b){ return a > b; });

	while (isSorting) {
		if (locker) {
			mutex.lock();
			for (int i = 0; i < var.size(); i++) {
				std::cout << var[i] << " ";
			}
			std::cout << std::endl;
			locker = false;
			mutex.unlock();
		}
	}

	thread.join();

	return 0;
}