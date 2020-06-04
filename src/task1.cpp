# include <iostream>

template <typename T, typename L>
void bubble_sorting(T* array, int size, L comparator) {
	for (int j = size - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			if (comparator(array[i], array[i + 1]) > 0) {
				T temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}

template<typename T>
void print_array(T* array, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << "  ";
	}
	std::cout << std::endl;
}

int main() {
	//------------------------INT------------------------------------
	int a[] = { 6, 5, -4, 3, 2, 1 };	
	int size_a = sizeof(a) / sizeof(a[0]);
	std::cout << "Original array:" << std::endl;
	print_array(a, size_a);

	std::cout << "Sort Ascending:" << std::endl;
	bubble_sorting(a, size_a, [](const int item1, const int item2) -> int  {return  item1 - item2;});
	print_array(a, size_a);

	std::cout << "Sort Descending:" << std::endl;
	bubble_sorting(a, size_a, [](const int item1, const int item2) -> int {return  (-1)*(item1 - item2);});
	print_array(a, size_a);

	std::cout << "Sort by square of numbers:" << std::endl;
	bubble_sorting(a, size_a, [](const int item1, const int item2) -> int {return  item1*item1 - item2*item2;});
	print_array(a, size_a);
	std::cout << std::endl << std::endl;

	//-----------------------STRING---------------------------------
	std::string a3[] = { (char*) "Hello", (char*)"how", (char*)"are", (char*)"you", (char*)"?" };
	int size_a3 = sizeof(a3) / sizeof(a3[0]);
	std::cout << "Original array:" << std::endl;
	print_array(a3, size_a3);

	std::cout << "Sort Ascending:" << std::endl;
	bubble_sorting(a3, size_a3, [](const std::string& item1, const std::string& item2) -> int {return  item1.compare(item2);});
	print_array(a3, size_a3);

	std::cout << "Sort Descending:" << std::endl;
	bubble_sorting(a3, size_a3, [](const std::string& item1, const std::string& item2) -> int {return  (int) (-1) * item1.compare(item2);});
	print_array(a3, size_a3);
}