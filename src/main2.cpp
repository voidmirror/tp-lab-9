#include "task2.h"

int main2()
{
	vector<string> data_for_sort = { "me", "cool", "oohh", "all", "family", "summer", "not", "ex" };

	cout << "Before sort:" << endl;
	for (auto i : data_for_sort)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << "Sort_step:" << endl;

	thread th(bubble_sort, ref(data_for_sort), [](string a, string b) { return a > b; });

	while (!sort_done)
	{
		unique_lock<mutex> lk(mtx);
		c_v.wait(lk, []() { return sort_step_done; });

		for (auto i : data_for_sort)
		{
			cout << i << " ";
		}
		cout << endl;

		print_done = true;
		sort_step_done = false;
		lk.unlock();
		c_v.notify_all();
	}

	th.join();

	return 0;
}
