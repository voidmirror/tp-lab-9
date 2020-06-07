#include "Task1.h"
#include "Task2.h"
#include "Task3.h"


void Task1() {
	std::vector<std::string> array = { "one", "two", "three", "four", "five", "six", "seven" };
	std::vector<std::string> out = bubble(array, [](std::string s1, std::string s2) {return s1 < s2; });
	for (auto item : out)
		std::cout << item << " ";
	std::cout << "\n";

	out = bubble(array, [](std::string s1, std::string s2) {return s1[0] > s2[0]; });
	for (auto item : out)
		std::cout << item << " ";
	std::cout << "\n";

	out = bubble(array, [](std::string s1, std::string s2) {return s1[s1.size() - 1] < s2[s2.size() - 1]; });

	for (auto item : out)
		std::cout << item << " ";
	std::cout << "\n";

	out = bubble(array, [](std::string s1, std::string s2) {return s1.size() < s2.size(); });
	for (auto item : out)
		std::cout << item << " ";
	std::cout << "\n";

	out = bubble(array, [](std::string s1, std::string s2) {return s1[0] != s2[0]; });
	for (auto item : out)
		std::cout << item << " ";
	std::cout << "\n";
}




void Task2() {
	std::vector<std::string> array = { "one", "two", "three", "four", "five", "six", "seven" };
	std::thread th(bubble_thread, ref(array), [](std::string s1, std::string s2) {return s1 > s2; });
	
	while (!flag) {
		mutex_1.lock();
		for (auto item : array)
			std::cout << item << " ";
		std::cout << "\n";
		iter = false;
		mutex_1.unlock();
	}
	th.join();
}


void Task3() {
	queue<customer*> customers;
	vector<thread*> threads;
	for (int i = 1; i <= 30; i++) {
		customers.push(new customer(i));
		if (i % max_queue == 0) {
			threads.push_back(new thread(serve, customers, threads.size() + 1));
			while (!customers.empty())
				customers.pop();
		}
	}
	for (auto thread : threads)
		thread->join();
	
}
int main() {
	Task1();
	Task2();
	Task3();
	return 1;
}