#include "quick_sort.h"
template <typename T>
void QuickSort<T>::sort(std::vector<T> &data) const {
    if (data.size() <= 1) {
        return;
    }
    sortHelper(data, 0, data.size());
    return;
}

template <typename T>
void QuickSort<T>::sortHelper(std::vector<T> &data, size_t start, size_t end) const {
    size_t size = end - start;
    if (size <= 1 || start > end) {
        return;
    }

    size_t i = start, j = start + 1;
    size_t pivotIndex = end - 1;
    T pivotValue = data[pivotIndex];

    if (data[start] < pivotValue) {
        i++;
    }
    while (j < end - 1) {
        if (data[j] < pivotValue) {
            std::swap(data[j], data[i++]);
        }
        j++;
    }
    std::swap(data[i], data[pivotIndex]);
    sortHelper(data, start, i);
    sortHelper(data, i + 1, end);
}