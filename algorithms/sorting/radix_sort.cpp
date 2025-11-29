#include "radix_sort.h"

template <typename T>
void RadixSort<T>::bucketSort(std::vector<T> &data, int shift) const {
    std::vector<size_t> count(16, 0);
    std::vector<T> output(data.size());

    for (const T &element : data) {
        size_t digit = (static_cast<size_t>(element) >> shift) & 0xf;
        ++count[digit];
    }

    for (size_t i = 1; i < 16; i++) {
        count[i] += count[i - 1];
    }

    for (size_t i = data.size(); i-- > 0;) {
        size_t digit = (static_cast<size_t>(data[i]) >> shift) & 0xF;
        output[--count[digit]] = data[i];
    }
    data.swap(output);
}

template <typename T>
void RadixSort<T>::sort(std::vector<T> &data) const {
    if (data.size() <= 1) {
        return;
    }

    for (int shift = 0; shift < 32; shift += 4) {
        bucketSort(data, shift);
    }
    return;
}
