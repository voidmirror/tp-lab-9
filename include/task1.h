#ifndef TASK1_H
#define TASK1_H
#include <iostream>
#include <vector>
#include <functional>
#include <string>

template <class T, class Comporator>
void bubbleSort(std::vector<T> & arr, Comporator comparator) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr.size() - i - 1; j++) {
			if (comparator(arr[j], arr[j + 1])) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

template <class T>
void printVector(T *arr) {
	for (auto &i : *arr) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void startTask1() {
	std::cout << "-------------------------\nTask number 1:" << std::endl;
	std::vector <int> vectorOfInts = { 1, 2, 43, 54, 6, 5, 76, 4, 1 , 4, 0, -1000000 };
	std::vector <double> vectorIfDoubles = { 3.1, 34.0, -34.24, 1.1, 1.11, 1.101 };
	std::vector <std::string> vectorOfStrings = { "dab", "deb", "rreeeee", "Ian" };

	bubbleSort(vectorOfInts, [](int a, int b) {return a > b; });
	std::cout << "Sorted ints in one way" << std::endl;
	printVector(&vectorOfInts);

	bubbleSort(vectorOfInts, [](int a, int b) {return a < b; });
	std::cout << "Sorted int in another way" << std::endl;
	printVector(&vectorOfInts);

	bubbleSort(vectorIfDoubles, [](double a, double b) {return a > b; });
	std::cout << "Sorted doubles" << std::endl;
	printVector(&vectorIfDoubles);

	bubbleSort(vectorOfStrings, [](const std::string & a, const std::string & b) {return a.size() > b.size(); });
	std::cout << "Sorted strings" << std::endl;
	printVector(&vectorOfStrings);

	bubbleSort(vectorOfStrings, [](const std::string & a, const std::string & b) {return b.compare(a); });
	std::cout << "Sorted strings" << std::endl;
	printVector(&vectorOfStrings);
}

#endif