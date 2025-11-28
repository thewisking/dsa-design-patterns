#include "merge_sort.h"
template <typename T>
void MergeSort<T>::sort(std::vector<T> &data) const {
    size_t size = data.size();
    if (size <= 1) {
        return;
    }

    size_t middle = size / 2;
    std::vector<T> leftArray(middle);
    std::vector<T> rightArray(size - middle);

    for (size_t i = 0; i < middle; i++) {
        leftArray[i] = data[i];
    }
    for (size_t i = middle, j = 0; i < size; i++) {
        rightArray[j++] = data[i];
    }
    sort(leftArray);
    sort(rightArray);
    sortHelper(leftArray, rightArray, data);
    return;
}

template <typename T>
void MergeSort<T>::sortHelper(std::vector<T> &leftArray, std::vector<T> &rightArray, std::vector<T> &array) const {
    size_t leftSize = leftArray.size();
    size_t rightSize = rightArray.size();
    size_t i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        if (leftArray[l] > rightArray[r]) {
            array[i++] = rightArray[r++];
        } else {
            array[i++] = leftArray[l++];
        }
    }

    while (l < leftSize) {
        array[i++] = leftArray[l++];
    }

    while (r < rightSize) {
        array[i++] = rightArray[r++];
    }
    return;
}