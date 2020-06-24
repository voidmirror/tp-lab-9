#include "head.h"
/*
void bubbleSortStringThr(vector<string> &input, bool comp(string str1, string str2)){
	for (int i = 0; i < input.size(); i++){
		for (int j = 0; j < input.size() - 1; j++){
			unique_lock<mutex> lck(mu);
			con.wait(lck, []{return !printing; });
			if (!comp(input[j], input[j + 1]))
				swap(input[j], input[j + 1]);
			printing = true;
			sorting = false;
			con.notify_all();
		}
	}
	working = false;
}*/