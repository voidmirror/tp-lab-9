#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <ctime>
#include <queue>
#include <chrono>

using namespace std;

void bubbleSortString(vector<string> &input, bool comp(string str1, string str2));

void bubbleSortStringThr(vector<string> &input, bool comp(string str1, string str2));

class Customer{
	private:
		vector<int> products;
	public:
		Customer();
		vector<int> getProducts();
};