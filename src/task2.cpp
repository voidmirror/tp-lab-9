#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;
std::condition_variable con_var;
bool sorted = true, printed = false;

void bubble_sorting2(std::string* array, int size, int (*comparator)(const std::string, const std::string), bool& is_sorting) {	
	for (int j = size - 1; j > 0; j--) {
		std::unique_lock <std::mutex> lock(mutex);
		con_var.wait(lock, [] { return printed;});
		for (int i = 0; i < j; i++) {
			if (comparator(array[i], array[i + 1]) > 0) {
				std::string temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
		std::cout << "STEP-" << (size-1)-j<<"\t";
		sorted = true;
		printed = false;
		lock.unlock();
		con_var.notify_all();
	}	
	is_sorting = false;
}

void print_array(std::string* array, int size) {
	std::unique_lock <std::mutex> lock(mutex);
	con_var.wait(lock, [] {return sorted;});

	for (int i = 0; i < size; i++) {
		std::cout << array[i] << "  ";
	}
	std::cout << std::endl<<std::endl;

	sorted = false;
	printed = true;
	lock.unlock();
	con_var.notify_all();
}

int main() {
	std::string a3[] = { (char*) "Hello", (char*) "!!!", (char*)"how", (char*)"are", (char*)"You", (char*)"?" };
	int size_a3 = sizeof(a3) / sizeof(a3[0]);
	std::cout << "Original array:" << std::endl;

	bool is_sorting = true;	
	
	std::thread t1(bubble_sorting2, a3, size_a3, [](std::string item1, std::string item2) -> int {return  item1.compare(item2);}, std::ref(is_sorting));
	while (is_sorting) {		
		print_array(a3, size_a3);
	};
	
	t1.join();
}