#include "bubble_sort.h"
#include <vector>

template <typename T>
void BubbleSort<T>::sort(std::vector<T> &data) const {
    std::size_t size = data.size();
    if (size == 0) {
        return;
    }
    T temp;
    std::size_t numOfSwaps = 0;
    bool swapped = true;
    while (swapped) {
        numOfSwaps = 0;
        swapped = false;
        for (std::size_t i = 0; i < (size - numOfSwaps - 1); i++) {
            if (data[i] > data[i + 1]) {
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                numOfSwaps++;
                swapped = true;
            }
        }
    }
    return;
}