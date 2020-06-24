#include "task3.h"
#include <list>
#include <conio.h>

int main() {
	srand(time(nullptr));

	list<CashDeck*> shop;
	int cashNum;
	for (cashNum = 0; cashNum < 3; cashNum++) {
		CashDeck* deck = new CashDeck(new Customer(), cashNum);
		shop.push_back(deck);
	}

	// after _kbhit() new Customer objects will not be created
	// (shop is closing)
	while (!_kbhit() && !shop.empty()) {
		auto it = shop.begin();
		while (it != shop.end()) {
			if ((*it)->empty()) {
				CashDeck* deckToDel = *it;
				shop.erase(it++);
				delete deckToDel;
			}
			else {
				it++;
			}
		}

		auto randIt = shop.begin();
		advance(randIt, rand() % shop.size());
		Customer* newCustomer = new Customer();
		if (!(*randIt)->putCustomer(newCustomer)) {
			shop.push_back(new CashDeck(newCustomer, ++cashNum));
		}
		this_thread::sleep_for(chrono::milliseconds(rand() % 2500));
	}

	auto it = shop.begin();
	while (it != shop.end()) {
		CashDeck* deckToDel = *it;
		shop.erase(it++);
		delete deckToDel;
	}

	return 0;
}