#include "insertion_sort.h"
#include <vector>

template <typename T>
void InsertionSort<T>::sort(std::vector<T> &data) const {
    std::size_t size = data.size();
    if (size == 0) {
        return;
    }
    T temp;
    for (std::size_t i = 1; i < size; i++) {
        temp = data[i];
        size_t j = i;
        while (j > 0 && data[j - 1] > temp) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = temp;
    }

    return;
}