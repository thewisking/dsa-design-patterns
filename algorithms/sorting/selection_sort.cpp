#include "selection_sort.h"
#include <vector>

template <typename T>
void SelectionSort<T>::sort(std::vector<T> &data) const {

    std::size_t size = data.size();

    if (size == 0) {
        return;
    }
    int currentMin;

    for (std::size_t i = 0; i < size; i++) {
        currentMin = i;
        for (std::size_t j = i; j < size; j++) {
            if (data[j] > data[currentMin]) {
                currentMin = j;
            }
        }
        data[i] = data[currentMin];
    }
    return;
}