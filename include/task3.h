//
//  task3.h
//  lab9
//
//  Created by Андрей Журавлев on 19.05.2020.
//  Copyright © 2020 Андрей Журавлев. All rights reserved.
//

#ifndef task3_h
#define task3_h
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <string>
#include <mutex>
#include <thread>
#include <map>
#include <random>
#include <queue>
#include <deque>

static std::mutex mutex;

class Buyer {
	std::vector<std::string> goods;
	
	static inline std::map<int, std::string> goodsDict = {
		{0, "Milk"},
		{1, "Chips"},
		{2, "Apples"},
		{3, "Bread"},
		{4, "Butter"},
		{5, "Cucumbers"},
		{6, "Potatos"},
		{7, "Tomatos"},
		{8, "Garlic"},
		{9, "Water"}
	};
	
public:
	Buyer() {
		int basketSize = rand() % 5 + 1;
		for (int i = 0; i < basketSize; i++) {
			int index = rand() % goodsDict.size();
			goods.push_back(goodsDict[index]);
		}
	}
	~Buyer() {
		goods.clear();
	}
	
	void serve() {
		for (int i = 0; i < goods.size(); i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		goods.clear();
		mutex.lock();
		std::cout << "\tFinished serving buyer on window " << std::this_thread::get_id() << std::endl;
		mutex.unlock();
	}
	
	size_t getBasketSize() {
		return goods.size();
	}
};

class CashWindow {
	
public:
	static void serveBuyers(std::deque<Buyer> buyers) {
		while (!buyers.empty()) {
			mutex.lock();
			std::cout << "CashWindow num " << std::this_thread::get_id() << " with " << buyers.size() << " customers\n";
			std::cout << "Current buyer has " << buyers.front().getBasketSize() << " goods\n";
			mutex.unlock();
			buyers.front().serve();
			buyers.pop_front();
		}
	}
};

class Shop {
	std::vector<std::thread> threads;
	
public:
	
	void work(size_t numberOfBuyers) {
		std::deque<Buyer> buyers;
		
		for (int i = 0; i < numberOfBuyers; i++) {
			buyers.push_back(Buyer());
			if (buyers.size() >= 5 || numberOfBuyers - i == 1) {
				threads.push_back(std::thread(CashWindow::serveBuyers, buyers));
				buyers.clear();
			}
		}
		
		std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
	}
	
};

#endif /* task3_h */
