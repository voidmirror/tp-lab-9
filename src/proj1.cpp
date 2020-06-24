#include "head.h"

using namespace std;

void bubbleSortString(vector<string> &input, bool comp(string str1, string str2)){
	for (int i = 0; i < input.size(); i++){
		for (int j = 0; j < input.size() - 1; j++){
			if (!comp(input[j], input[j + 1]))
				swap(input[j], input[j + 1]);
		}
	}
}