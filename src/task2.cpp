#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
bool next_iter = true;
bool finished = false;

void bubble_sort2(vector<string> &a, bool comp(string a, string b))
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		for (int j = 1; j < a.size(); j++)
		{
			while (next_iter)
			{
				continue;
			}
			m.lock();
			if (comp(a[j - 1], a[j]))
			{
				swap(a[j - 1], a[j]);
				next_iter = true;
			}
			m.unlock();
		}
	}
	finished = true;
}

int main2() {
	vector<string> vec = { "k", "j", "i", "h", "g", "f", "e", "d", "c", "b", "a" };
	thread sort_thread(bubble_sort2, ref(vec), [](string a, string b) {return a > b; });
	while (true)
	{
		if (finished) break;
		m.lock();
		if (!next_iter)
		{
			m.unlock();
			continue;
		}
		for (int i = 0; i < vec.size(); i++)
		{
			cout << vec[i] << ' ';
		}
		cout << '\n';
		next_iter = false;
		m.unlock();
	}
	sort_thread.join();
	return 0;
}
//
//int main()
//{
//	main2();
//}