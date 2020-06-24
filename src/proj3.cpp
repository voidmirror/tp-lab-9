#include "head.h"

Customer::Customer(){
	srand(time(0));
	for (int i = 1; i <= rand() % 20 + 1; i++){
		products.push_back(i);
	}
}

vector<int> Customer::getProducts(){
	return products;
}