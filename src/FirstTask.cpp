#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename RandIterator, typename Comparator>
void bubble(RandIterator head, RandIterator tail, Comparator cr){
	for (RandIterator right = tail - 1; right > head; --right){
		for (RandIterator left = head; left < right; ++left){
			if (!cr(*left, *right)){
				std::swap(*left, *right);}
		}
	}
}

std::ostream& operator<< (std::ostream& output, const std::vector<std::string>& mVector) {
	for (auto v : mVector) {
		output << v << " ";
	}
	output << '\n';
	return output;
}

int main() {
	std::vector<std::string> v1 = { "One", "Two", "Three", "Four", "Fiva"};
	std::vector<std::string> v2 = { "Hamilton", "Adams", "Washington", "Jefferson" };
	std::vector<std::string> v3 = { "Mosha", "Kartosha", "Playng", "Games" };
	std::vector<std::string> v4 = { "A", "B", "C" };
	std::vector<std::string> v5 = { "FGDHGFHSDFGH", "FDGHSDFHERTDRHFG", "FGHDFGHDFGH", "GFHDFGHDF", "GFRrtertertertTGRTE5HGKJHHHDFGHDF" };

	bubble(v1.begin(), v1.end(), [](const std::string& a, const std::string& b) {
		return a > b; 
		});
	bubble(v2.begin(), v2.end(), [](const std::string& a, const std::string& b) {
		return a[0] < b[0];
		});
	bubble(v3.begin(), v3.end(), [](const std::string& a, const std::string& b) {
		return a > b;
		});
	bubble(v4.begin(), v4.end(), [](const std::string& a, const std::string& b) {
		return a[0] > b[0];
		});
	bubble(v5.begin(), v5.end(), [](std::string  a, std::string  b) {
		return a + a > b;
		});

	std::cout << v1;
	std::cout << v2;
	std::cout << v3;	
	std::cout << v4;
	std::cout << v5;

	return 0;
}
