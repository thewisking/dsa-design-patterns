#include "heap_sort.h"
#include <vector>

template <typename T>
void HeapSort<T>::heapify(std::vector<T> &data, size_t end) const {
    for (size_t i = end; i > 0; i--) {
        if (data[i] > data[(i - 1) / 2]) {
            std::swap(data[i], data[(i - 1) / 2]);
        }
    }
}

template <typename T>
void HeapSort<T>::sort(std::vector<T> &data) const {
    size_t size = data.size();
    if (size <= 1) {
        return;
    }
    sortHelper(data, size - 1);
    return;
}

template <typename T>
void HeapSort<T>::sortHelper(std::vector<T> &data, size_t end) const {
    if (end == 1) {
        return;
    }
    heapify(data, end);
    std::swap(data[0], data[end]);
    sortHelper(data, end - 1);
    return;
}