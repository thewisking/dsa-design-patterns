#pragma once
#include <algorithm>
#include <vector>

template <typename T>
class QuickSelect {
  public:
    QuickSelect() = default;

    T *select_kth_smallest(std::vector<T> &data, std::size_t k) const {
        if (k == 0 || k > data.size()) {
            return nullptr;
        }
        return select_kth_smallest_helper(data, 0, data.size(), k - 1);
    }

    T *select_kth_largest(std::vector<T> &data, std::size_t k) const {
        if (k == 0 || k > data.size()) {
            return nullptr;
        }

        std::size_t n = data.size();
        std::size_t target_index = n - k;

        return select_kth_smallest_helper(data, 0, n, target_index);
    }

  private:
    T *select_kth_smallest_helper(std::vector<T> &data, size_t start, size_t end, std::size_t k) const {

        if (start >= end || k >= end || k < start) {
            return nullptr;
        }
        if (start + 1 == end) {
            return &data[start];
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

        if (k == i) {
            return &data[i];
        } else if (k < i) {
            return select_kth_smallest_helper(data, start, i, k);
        } else {
            return select_kth_smallest_helper(data, i + 1, end, k);
        }
    }
};