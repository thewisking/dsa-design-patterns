#pragma once
#include <vector>

template <typename T>
class QuickSort {
  public:
    void sort(std::vector<T> &data) const;

  private:
    void sortHelper(std::vector<T> &data, size_t start, size_t end) const;
};