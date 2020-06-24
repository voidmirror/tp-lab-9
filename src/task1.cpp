#include <iostream>
#include <string>

using namespace std;


void bSort(string* mas, int masLen, bool cmp(string a, string b))
{
	for (int i = 0; i < masLen; i++)
	{
		for (int j = 0; j < masLen - (i + 1); j++)
		{
			if (cmp(mas[j], mas[j + 1]))
				swap(mas[j], mas[j + 1]);
		}
	}
}
void printMas(string* mas, int lenMas)
{
	for (int i = 0; i < lenMas; i++)
		cout << mas[i] << " ";
	cout << endl;
}

int main()
{
	const short int MASlen = 10;
	string mas[MASlen] = { "uno", "dos", "tres", "cuatro","cinco", "seis", "siete","ocho","nueve","diez" };

	bSort(mas, MASlen, [](string a, string b) { return a[0] > b[0]; });
	printMas(mas, MASlen);

	bSort(mas, MASlen, [](string a, string b) { return a[0] < b[0]; });
	printMas(mas, MASlen);

	bSort(mas, MASlen, [](string a, string b) { return a.length() > b.length(); });
	printMas(mas, MASlen);

	bSort(mas, MASlen, [](string a, string b) { return a[a.length()-1] > b[b.length()-1]; });
	printMas(mas, MASlen);

	bSort(mas, MASlen, [](string a, string b) { return a[a.length() - 1] < b[b.length() - 1]; });
	printMas(mas, MASlen);

	

	return 0;


}