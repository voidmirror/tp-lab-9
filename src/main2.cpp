#include "head.h"

using namespace std;

mutex mu;
bool sorting = true;
bool printing = false;
bool working = true;
condition_variable con;

void bubbleSortStringThr(vector<string> &input, bool comp(string str1, string str2)){
	for (int i = 0; i < input.size(); i++){
		unique_lock<mutex> lck(mu);
		con.wait(lck, []() { return sorting; });
		for (int j = 0; j < input.size() - 1; j++){
			if (!comp(input[j], input[j + 1]))
				swap(input[j], input[j + 1]);
		}
		sorting = false;
		printing = true;
		con.notify_all();
	}
	working = false;
}

int main(){
	vector<string> inp = { "asjfbiajsbf", "afASFmkk", "154355", "Inincsq", "hey", "zzzzzzzzz", "ABCDE" };
	thread th(bubbleSortStringThr, ref(inp), [](string str1, string str2){ return str1.length() < str2.length(); });
	while (working){
		unique_lock<mutex> lck(mu);
		con.wait(lck, []() { return printing; });
		for (auto word : inp)
			cout << word << " ";
		cout << endl;
		sorting = true;
		printing = false;
		con.notify_all();
	}
	th.join();
	getchar();
	return 0;
}