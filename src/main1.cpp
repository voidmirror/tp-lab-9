#include <vector>


template <typename T, typename C>
void bubbleSort(T* array, int length, C comparator) {
    while (length > 1) {
        for (int i = 0; i < length - 1; i++) {
            if (comparator(array[i], array[i+1]) > 0) {
                std::swap(array[i], array[i + 1]);
            }
        }
        length--;
    }
}

int main() {
    int array[6] = { 235, 23, 65, 546, 2354, 56 };
    bubbleSort(array, 6, [](int first, int second) -> int {return first - second; });
    bubbleSort(array, 6, [](int first, int second) -> int {return second - first; });
}