#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <ctime>

std::mutex mtx;
bool readyToPrint = true;
bool strIsReady = false;

template <typename T>
void bubble_sort(std::vector<std::string>& strings, T lambda)
{
	for (int i = strings.size() - 1; i > 0; i--) {
		mtx.lock();
		for (int j = 0; j < i; j++) {
			if (lambda(strings[j], strings[j + 1])) {
				std::swap(strings[j], strings[j + 1]);
			}
		}
		strIsReady = true;
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	readyToPrint = false;
}

int main()
{
	std::vector<std::string> vector = { "123", "321", "A" , "B", "C" , "a", "b", "z" };

	std::thread secondThread(bubble_sort<bool(*)(const std::string&, const std::string&)>,
		std::ref(vector), [](const std::string& a, const std::string& b) { return a < b; });

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	while (readyToPrint)
	{
		if (strIsReady)
		{
			mtx.lock();
			for (int i = 0; i < vector.size(); i++)
			{
				std::cout << vector[i] << " ";
			}
			std::cout << std::endl;
			strIsReady = false;
			mtx.unlock();
		}
	}

	std::cout << std::endl;
	std::cout << "Run time: " << clock() / 1000.0;
	secondThread.join();
	return 0;
}