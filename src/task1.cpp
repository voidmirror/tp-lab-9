#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename RandIterator, typename Comparator>
void bubble_sort(
	RandIterator first, RandIterator last,
	Comparator comparator
) {

	for (RandIterator right = last-1; right > first; --right) {
		for (RandIterator left = first; left < right; ++left) {
			if (!comparator(*left, *right)) {
				std::swap(*left, *right);
			}
		}
	}
}

std::ostream& operator<< (std::ostream& out, const std::vector<std::string>& vec) {
	for (auto x : vec) {
		out << x << " ";
	}
	out << '\n';
	return out;
}

int main() {
	// #1
	std::vector<std::string> vector1 = { "hello", "everyone", "who", "watch", "this", "code" };
	bubble_sort(vector1.begin(), vector1.end(), [](const std::string & a, const std::string& b) {return a < b; });
	std::cout << vector1;

	// #2
	std::vector<std::string> vector2 = { "deadlines", "research", "HSE", "code" };
	bubble_sort(vector2.begin(), vector2.end(), [](const std::string & a, const std::string & b) {return a[0] > b[0]; });
	std::cout << vector2;

	// #3 
	std::vector<std::string> vector3 = { "laba 9", "github", "repository" };
	bubble_sort(vector3.begin(), vector3.end(), [](const std::string& a, const std::string& b) {return a + b < b + a; });
	std::cout << vector3;

	// #4
	std::vector<std::string> vector4 = { "PMI-1", "PMI-2", "PI-1", "PI-2" };
	bubble_sort(vector4.begin(), vector4.end(), [](const std::string& a, const std::string& b) {return a > b; });
	std::cout << vector4;

	// #5
	std::vector<std::string> vector5 = { "deadlines", "research", "HSE", "code" };
	bubble_sort(vector5.begin(), vector5.end(), []( std::string  a,  std::string  b) {
		std::reverse(a.begin(), a.end());
		std::reverse(b.begin(), b.end());
		return  a < b; 
			});
	std::cout << vector5;

	return 0;
}