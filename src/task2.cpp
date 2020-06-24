#include "task.h"


mutex mtx;
bool printed = false, sorted = true, ended = false;
condition_variable cond;

void PrintVector(vector<string>& arr)
{
	for (string elem : arr) {
		cout << elem << " ";
	}
	cout << endl;
}

template<typename F>
void BubbleSortThreads(vector<string>& arr, F Comparator)
{
	size_t size = arr.size();

	for (size_t i = 0; i < size; i++) {

		for (size_t j = 0; j < size - i - 1; j++) {
			std::unique_lock<std::mutex> lock(mtx);
			cond.wait(lock, [] {return printed; });

			if (!Comparator(arr[j], arr[j + 1]))
			{
				swap(arr[j], arr[j + 1]);
			}
			sorted = true;
			printed = false;
			cond.notify_all();
		}
	}

	ended = true;
}

int main()
{
	vector<string> srcVec = { "avcv","asfdssadg","a","123","oleg","1234", "12", "g" };

	auto lenComparator = [](const string& a, const string& b) -> bool
	{
		return a.length() < b.length();
	};

	thread thr(BubbleSortThreads<decltype(lenComparator)>, ref(srcVec), lenComparator);

	while (!ended)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cond.wait(lock, [] {return sorted; });
		PrintVector(srcVec);
		sorted = false;
		printed = true;
		cond.notify_all();
	}

	thr.join();
}