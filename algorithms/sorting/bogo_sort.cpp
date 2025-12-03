#include "bogo_sort.h"
#include <algorithm>
#include <random>
#include <vector>

template <typename T>
void BogoSort<T>::sort(std::vector<T> &data) const {
    auto size = data.size();
    if (size < 2) {
        return;
    }

    // This means that it's only done once per thread. we only need one of them to create random numbers
    // unless we move to a new thread. This process is expensive to repeat and is unncessary since we'll
    // stil get random numbers.
    static thread_local std::mt19937 rng(std::random_device{}());

    while (!isSorted(data)) {
        std::shuffle(data.begin(), data.end(), rng);
    }
}

template <typename T>
bool BogoSort<T>::isSorted(const std::vector<T> &data) const {
    auto size = data.size();
    if (size < 2) {
        return true;
    }
    for (std::size_t i = 1; i < size; i++) {
        if (data[i] < data[i - 1]) {
            return false;
        }
    }
    return true;
}
