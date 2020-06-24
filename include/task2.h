#pragma once 

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;

condition_variable c_v;
mutex mtx;
bool print_done = true;
bool sort_step_done = false;
bool sort_done = false;

void bubble_sort(vector<string> &data, bool comparator(string a, string b))
{
	for (int i = data.size() - 1; i > 0; i--)
	{
		unique_lock<mutex> lk(mtx);
		c_v.wait(lk, []() { return print_done; });

		for (int j = 0; j < i; j++)
		{
			if (comparator(data[j], data[j + 1]))
			{
				swap(data[j], data[j + 1]);
			}
		}

		print_done = false;
		sort_step_done = true;
		lk.unlock();
		c_v.notify_all();
	}

	sort_done = true;
}
