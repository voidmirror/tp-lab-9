#pragma once

#include <thread>
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <mutex>
#include <random>
#include <ctime>
using namespace std;

extern mutex mtx;

class customer
{
private:
	const int max_num = 5;
	int product_num = 0;
public:
	customer();
	int getProducts();
	void perform();
};

void kassa(queue<customer*> var, int index);