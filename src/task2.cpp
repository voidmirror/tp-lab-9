#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
bool finish = false, printed = true, sorted = false;


void BubbleSort(vector<string>& arr, bool comparator(const string& a, const string& b))
{
	vector<string>::iterator pos;
	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		unique_lock<mutex> ul(mtx);

		cv.wait(ul, []() {return printed; }); // while (!printed)
		for (size_t j = 0; j < arr.size() - 1 - i; j++)
		{
			if (comparator(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}

		printed = false;
		sorted = true;
		ul.unlock();
		cv.notify_all();
	}
	finish = true;
}

int main()
{
	vector<string> vec = {"weekends", "summer", "hse", "exams", "weekdays", "or" };
	auto comparator = [](const string& a, const string& b)
	{
		return a.size() > b.size();
	};

	thread th(BubbleSort, ref(vec), comparator);
	while (!finish)
	{
		unique_lock<mutex> ul(mtx);
		
		cv.wait(ul, []() {return sorted; }); //while(!sorted)
		for (auto str : vec)
		{
			cout << str << " ";
		}
		cout << endl;
		this_thread::sleep_for(chrono::milliseconds(1500));
		printed = true;
		sorted = false;
		ul.unlock();
		cv.notify_all();
	}

	th.join();
	getchar();
	return 0;
}
