#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
void bubble_sort(std::vector<std::string> & strings, T lambda)
{
	for (int i = strings.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (lambda(strings[j], strings[j + 1])) {
				std::swap(strings[j], strings[j + 1]);
			}
		}
	}
}

std::ostream& operator<< (std::ostream& out, const std::vector<std::string>& v) {
	for (auto element : v) {
		out << element << " / ";
	}
	out << '\n';
	return out;
}

int main() {
	std::vector<std::string> vector1 = { "I", "love", "C++" };
	bubble_sort(vector1, [](const std::string& a, const std::string& b) {return a > b; });
	std::cout << vector1;

	std::vector<std::string> vector2 = { "I love food", "fresh fruits", "HSE one love forever" };
	bubble_sort(vector2, [](const std::string& a, const std::string& b)
		{return std::count(a.begin(), a.end(), ' ') > std::count(b.begin(), b.end(), ' '); });
	std::cout << vector2;

	std::vector<std::string> vector3 = { "COVID-19", "go", "away" };
	bubble_sort(vector3, [](const std::string& a, const std::string& b) {return a[1] > b[1]; });
	std::cout << vector3;

	std::vector<std::string> vector4 = { "sooolong", "middle", "short" };
	bubble_sort(vector4, [](const std::string& a, const std::string& b) {return a.length() > b.length(); });
	std::cout << vector4;

	std::vector<std::string> vector5 = { "big", "bigger", "the largest" };
	bubble_sort(vector5, [](const std::string& a, const std::string& b) {return b.find(a) != std::string::npos; });
	std::cout << vector5;
}