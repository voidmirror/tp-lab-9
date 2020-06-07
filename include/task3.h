#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <ctime>
#include <windows.h>

typedef unsigned int uint;
std::mutex mtx;
const uint MAX_NUMBER = 8;

class Customer
{
private:
	uint prodNumber = 0;
public:
	Customer() {
		srand(time(NULL));
		this->prodNumber = rand() % MAX_NUMBER;
	}
	void exec() {
		Sleep(this->getProd());
	}
	uint getProd() {
		return this->prodNumber;
	}
};

void cash(std::queue<Customer*>, uint);