#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

#define SIZE 7

mutex mut;
condition_variable_any cond_var;

bool sort = false;
bool mainth = true; 
bool addth = false;

void BubbleSort(string mas[], bool cmp(string a, string b)){
	for (int i=0; i < SIZE; i++){
		mut.lock();
		cond_var.wait(mut, [] {return addth; });
		sort = true;
		for (int j=0; j < SIZE - 1; j++){
			if (cmp(mas[j], mas[j + 1])){
				sort = false;
				swap(mas[j], mas[j + 1]);
			}
		}
		mainth = true;
		addth = false;
		mut.unlock();
		cond_var.notify_all();
		if (sort)
			break;
	}

}

int main(){
	string mas[SIZE] = { "I", "WWn", "not", "nnnnN", "LLLLe", "tRRR", "ANRore" };

	thread NewStream(BubbleSort, mas, [](string a, string b) {return a.length() < b.length(); }); 
	while (true){	//main stream
		mut.lock();
		cond_var.wait(mut, [] {return mainth; });
		for (int i=0; i < SIZE; i++){
			cout << " " << mas[i] << " ";
		}
		cout << endl;
		mainth = false;
		addth = true;
		mut.unlock();
		cond_var.notify_all();
		if (sort)
			break;
	}

	NewStream.join();
	return 0;
}