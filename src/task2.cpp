#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


mutex mutObj;
condition_variable_any accessThread;

bool accessMainThread = true;
bool accessAddThread = false;

void bubSort(string* mas, int masSize, bool cmp(string a, string b))
{
	for (int i = 0; i < masSize; i++)
	{
		lock_guard<mutex> guard(mutObj); 
		accessThread.wait(mutObj, [] { return accessAddThread; });

		for (int j = 0; j < masSize - (i + 1); j++)
		{
			if (cmp(mas[j], mas[j + 1]))
				swap(mas[j], mas[j + 1]);
		}

		accessMainThread = true; 
		accessAddThread = false; 

		accessThread.notify_all(); 
	}
}
void printMas(string* mas, int lenMas)
{
	for (int i = 0; i < lenMas; i++) {
		cout << mas[i] << " ";
	}

	cout << endl;
}

int main(){

	const short int MASlen = 7;
	string mas[MASlen] = { "uno", "dos", "tres", "cuatro","cinco", "seis", "siete" };

	
	thread addThread(bubSort, mas, MASlen, [](string a, string b) { return a[0] > b[0]; });

	for (int i = 0; i < MASlen; i++)
	{
		
		lock_guard<mutex> guard(mutObj);


		accessThread.wait(mutObj, [] { return accessMainThread; });

		printMas(mas, MASlen);

		accessMainThread = false;
		accessAddThread = true;

		accessThread.notify_all();
	}
	addThread.join(); 

	return 0; 
}