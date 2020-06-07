#include "task2.h"
#include "task1.h"

void sort(std::string *mas, int arrSize, bool comp(const std::string &, const std::string &))
{
	std::mutex out;
	std::lock_guard<std::mutex> lockMutex(out);
	for (uint i = 0; i < arrSize; i++) {
		bool flag = true;
		std::thread thr([arrSize] (std::string* arr) {
			for (uint i = 0; i < arrSize; i++) std::cout << arr[i] << " ";
			std::cout << std::endl;
		}, mas);
		thr.join();

		for (uint j = 0; j < arrSize - i - 1; j++)
			if (comp(mas[j], mas[j + 1])) {
				flag = false;
				swap(mas[j], mas[j + 1]);
			}

		if (flag) {
			break;
		}
	}

}
int main() {
	int arrSize = 6;
	std::string* array = new std::string [arrSize] { "in", "omnia", "paratus!", "Acta", "non" "verba" };

	std::thread thrd(sort, array, arrSize, 
		[] (const std::string &unit1, const std::string &unit2) {
		return unit1 < unit2; 
	}
	);

	thrd.join();

	delete[] array;
	return 0;
}