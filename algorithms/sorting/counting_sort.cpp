#include "counting_sort.h"
#include <vector>

template <typename T>
void CountingSort<T>::sort(std::vector<T> &data) const {
    if (data.size() <= 1) {
        return;
    }
    T minValue = data[0];
    T maxValue = minValue;

    for (T x : data) {
        if (x > maxValue) {
            maxValue = x;
        } else if (x < minValue) {
            minValue = x;
        }
    }

    size_t range = static_cast<size_t>(maxValue - minValue + 1);
    std::vector<size_t> count(range, 0);

    for (T x : data) {
        ++count[static_cast<size_t>(x - minValue)];
    }

    size_t index = 0;

    for (size_t j = 0; j < range; j++) {
        for (size_t k = 0; k < count[j]; k++) {
            data[index++] = static_cast<T>(j + minValue);
        }
    }
}