#include "task1.h"

template<class T>
void bubbleSort(std::vector<std::string> &vec, T comp) {
	for (uint i = 0; i < vec.size(); i++)
		for (uint j = 0; j < vec.size() - 1; j++)
			if (comp(vec[j], vec[j + 1])) std::swap(vec[j], vec[j + 1]);
}

void print(std::vector<std::string> const &vec) {
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << std::endl;
}



int main() {
	std::vector<std::string> vstr1 = { "in", "omnia", "paratus!", "Acta", "non" "verba" };
	bubbleSort(vstr1,
		[](std::string& unit1, std::string& unit2) {
		return unit1 > unit2;
	}
	);
	print(vstr1);

	vstr1 = { "in", "omnia", "paratus!", "Acta", "non" "verba" };
	bubbleSort(vstr1,
		[](std::string& unit1, std::string& unit2) {
		return unit1 < unit2;
	}
	);
	print(vstr1);

	vstr1 = { "in", "omnia", "paratus!", "Acta", "non" "verba" };
	bubbleSort(vstr1,
		[](std::string& unit1, std::string& unit2) {
		return unit1[unit1.size() / 2] > unit2[unit2.size() / 2];
	}
	);
	print(vstr1);

	vstr1 = { "in", "omnia", "paratus!", "Acta", "non" "verba" };
	bubbleSort(vstr1,
		[](std::string& unit1, std::string& unit2) {
		return unit1[0] > unit2[0];
	}
	);
	print(vstr1);

	vstr1 = { "in", "omnia", "paratus!", "Acta", "non" "verba" };
	bubbleSort(vstr1,
		[](std::string& unit1, std::string& unit2) {
		return unit1[unit1.size()] > unit2[unit2.size()];
	}
	);
	print(vstr1);

	getchar();
	return 0;
}