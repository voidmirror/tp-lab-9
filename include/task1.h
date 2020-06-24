//
//  task1.h
//  lab9
//
//  Created by Андрей Журавлев on 18.05.2020.
//  Copyright © 2020 Андрей Журавлев. All rights reserved.
//

#ifndef task1_h
#define task1_h
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <string>
typedef std::vector<int>::iterator int_iter;
typedef std::vector<std::string>::iterator str_iter;

template<class iterator, class T = typename std::iterator_traits<iterator>::value_type>
void bubble_sort(iterator const& first, iterator const& last, std::function<bool(T, T)> comparator) {
	if (first == last) return;
	for (auto i = first; i != last; i++) {
		for (auto j = first; j != i; j++) {
			if (comparator(*i, *j)) {
				std::iter_swap(i, j);
			}
		}
	}
}

template <class iterator, class T = typename std::iterator_traits<iterator>::value_type>
void print_arr(iterator first, iterator last) {
	std::for_each(first, last, [](T x){ std::cout << x << " ";});
	std::cout << std::endl << std::endl;
}

void testTask1() {
	std::vector<std::string> arr1 = {"45", "2", "456", "104245", "452"};
	std::vector<std::string> arr2 = {"45", "2", "456", "104245", "452"};
	std::vector<std::string> arr3 = {"45", "2", "456", "104245", "452"};
	std::vector<std::string> arr4 = {"45", "2", "456", "104245", "452"};
	std::vector<std::string> arr5 = {"45", "2", "456", "104245", "452"};
	
	std::cout << "Source array:" << std::endl;
	print_arr(arr1.begin(), arr1.end());
	
	//common sort lexicographically from lesser to greater
	std::cout << "common sort lexicographically from lesser to greater" << std::endl;
	bubble_sort<str_iter, std::string>(arr1.begin(), arr1.end(), [](std::string lhs, std::string rhs) -> bool {
		if (lhs < rhs) {
			return true;
		} else {
			return false;
		}
	});
	print_arr(arr1.begin(), arr1.end());
	
	//common sort lexicographically from greater to lesser
	std::cout << "common sort lexicographically from greater to lesser" << std::endl;
	bubble_sort<str_iter, std::string>(arr2.begin(), arr2.end(), [](std::string lhs, std::string rhs) -> bool {
		if (lhs > rhs) {
			return true;
		} else {
			return false;
		}
	});
	print_arr(arr2.begin(), arr2.end());
	
	//sort by string length
	std::cout << "sort by string length" << std::endl;
	bubble_sort<str_iter, std::string>(arr3.begin(), arr3.end(), [](std::string lhs, std::string rhs) -> bool {
		if (lhs.length() < rhs.length()) {
			return true;
		} else {
			return false;
		}
	});
	print_arr(arr3.begin(), arr3.end());
	
	//sort by string length in reverse order
	std::cout << "sort by string length in reverse order" << std::endl;
	bubble_sort<str_iter, std::string>(arr4.begin(), arr4.end(), [](std::string lhs, std::string rhs) -> bool {
		if (lhs.length() < rhs.length()) {
			return false;
		} else {
			return true;
		}
	});
	print_arr(arr4.begin(), arr4.end());
	
	//sort by last char
	std::cout << "sort by last char" << std::endl;
	bubble_sort<str_iter, std::string>(arr5.begin(), arr5.end(), [](std::string lhs, std::string rhs) -> bool {

		if (lhs[lhs.length() - 1] < rhs[rhs.length() - 1]) {
			return true;
		} else {
			return false;
		}
	});
	print_arr(arr5.begin(), arr5.end());
}


#endif /* task1_h */
