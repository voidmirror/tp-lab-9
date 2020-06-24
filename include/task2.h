//
//  task2.h
//  lab9
//
//  Created by Андрей Журавлев on 18.05.2020.
//  Copyright © 2020 Андрей Журавлев. All rights reserved.
//

#ifndef task2_h
#define task2_h
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <string>
#include <mutex>
#include <thread>

template<class iterator, class T = typename std::iterator_traits<iterator>::value_type>
void bubble_sort_thread(iterator const& first, iterator const& last, std::function<bool(T, T)> comparator) {
	if (first == last) return;
	
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);
	
	for (auto i = first; i != last; i++) {
		std::thread t([&first, &last, &i] {
			std::cout << "Iteration " << std::distance(first, i) << ": \t";
			std::for_each(first, last, [](T x) { std::cout << x << " "; });
			std::cout << std::endl;
		});
		t.join();
		
		for (auto j = first; j != i; j++) {
			if (comparator(*i, *j)) {
				std::iter_swap(i, j);
			}
		}
	}
}

void testTask2() {
	std::vector<std::string> arr1 = {"45", "104245", "456", "2", "452"};
	std::cout << "Source array:" << std::endl;
	print_arr(arr1.begin(), arr1.end());
	
	std::thread t(bubble_sort_thread<str_iter, std::string>, arr1.begin(), arr1.end(), [](std::string lhs, std::string rhs) {
		if (lhs.length() < rhs.length()) {
			return true;
		} else {
			return false;
		}
	});
	t.join();
	std::cout << std::endl << "Result: " << std::endl;
	print_arr(arr1.begin(), arr1.end());
}

#endif /* task2_h */
