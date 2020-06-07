#pragma once
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

bool flag = false;
bool iter = true;
std::mutex mutex_1;

void bubble_thread(std::vector<std::string>& arr, bool comp(std::string s1, std::string s2)) {
	for (int i = 0; i < arr.size()-1; i++)
		for (int j = 0; j < arr.size() - i-1; j++) {
			if (comp(arr[j], arr[j+1])) {
				mutex_1.lock();
				std::swap(arr[j], arr[j+1]);
				iter = true;
				mutex_1.unlock();
			}
		}
	flag = true;
}