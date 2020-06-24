#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

std::mutex muMutex;
std::condition_variable cv;
bool finSort = false;
bool endIterator = false;
bool printed = true;

template <typename RandIterator, typename Comparator>
void bubble(
	RandIterator head, RandIterator tail,
	Comparator cp){
	for (RandIterator right = tail - 1; right > head; --right) 
	{
		for (RandIterator left = head; left < right; ++left) 
		{
			std::unique_lock<std::mutex> lk(muMutex);
			cv.wait(lk, []() {
				return printed;
				});
			if (!cp(*left, *right)) 
			{
				std::swap(*left, *right);
			}
			endIterator = true;
			printed = false;

			lk.unlock();
			cv.notify_all();
		}
	}
	finSort = true;
}

int main() {
	std::vector<std::string> v = { "one", "twoo", "ther", "fofvvv" };

	std::thread t(bubble<std::vector<std::string>::iterator, bool(*)
		(const std::string&, const std::string&)>,

		v.begin(), v.end(), [](const std::string& a,
			const std::string& b) {return a < b; });

	while (!finSort) {
		std::unique_lock<std::mutex> lk(muMutex);
		cv.wait(lk, []() { return endIterator; });
		for (auto s : v) {
			std::cout << s << " ";
		}
		std::cout << std::endl;
		endIterator = false;
		printed = true;

		lk.unlock();
		cv.notify_all();
	}

	t.join();

	return 0;
}