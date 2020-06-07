#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

mutex mutex_name;


bool finish = false;
bool sort = true;
bool print = false;
condition_variable condition;

template<typename F>

void Bubblesort(vector<string>& vector, F Comparator)
{
	for (size_t i = 0; i < vector.size(); i++) {
		for (size_t j = 0; j < vector.size() - i - 1; j++) {
			unique_lock<mutex> lock(mutex_name);
			condition.wait(lock, [] {return print; });
			if (!Comparator(vector[j], vector[j + 1])) {
				swap(vector[j], vector[j + 1]);
			}
			sort = true;
			print = false;
			condition.notify_all();
		}
	}
	finish = true;
}

int main() {
	vector<string> v = {"test3222", "test1", "test444", "test12", "test3131133"};
	auto test1 = [](const string& a, const string& b) -> bool { return a.size() < b.size(); };

	thread t(Bubblesort<decltype(test1)>, ref(v), test1);

	while (!finish)
	{
		unique_lock<mutex> lock(mutex_name);
		condition.wait(lock, [] {return sort;});
		for (auto s : v)
		{
			cout << s << " ";
		}
		cout << endl;
		sort = false;
		print = true;
		condition.notify_all();
	}
	t.join();
}