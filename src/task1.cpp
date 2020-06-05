#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T, typename C>
void bubbleSort(vector<T>& vector, C comparator) {
    size_t vectorSize = vector.size();
    for (size_t i = 0; i < vectorSize; i++) {
        for (size_t j = 0; j < vectorSize - i - 1; j++)
            if (!comparator(vector[j], vector[j + 1])) {
                swap(vector[j], vector[j + 1]);
            }
    }
}

template <typename T>
void printVector(vector<T> vector) {
    for (T element : vector) 
        cout << element << " ";
    cout << endl;
}

int main() {
	
    // 1
    vector<int> vec1 = { 1, 7, 2, 3, -1, 2 };
    printVector(vec1);
    bubbleSort(vec1, [](int& a, int& b) {return a < b;});
    printVector(vec1);
    cout << "------" << endl;

    // 2
    vector<string> vec2 = { "hello", "world", "apple", "human", "man", "communication", "and", "in", "o"};
    printVector(vec2);
    bubbleSort(vec2, [](string& a, string& b) {return a[0] < b[0];});
    printVector(vec2);
    cout << "------" << endl;

    // 3
    vector<string> vec3 = { "hello", "world", "apple", "human", "man", "communication", "and", "in", "o" };
    printVector(vec3);
    bubbleSort(vec3, [](string& a, string& b) {return a[a.size() - 1] < b[b.size() - 1];});
    printVector(vec3);
    cout << "------" << endl;

    // 4
    vector<string> vec4 = { "hello world", "apple or samsung", "human", "man", "communication", "and", "in", "o"};
    printVector(vec4);
    bubbleSort(vec4, [](string& a, string& b) {return a + b < b + a;});
    printVector(vec4);
    cout << "------" << endl;

    // 5
    vector<int> vec5 = { 1, 7, 2, 3, -1, 2 };
    printVector(vec5);
    bubbleSort(vec5, [](int& a, int& b) {return a > b; });
    printVector(vec5);
    cout << endl;
}