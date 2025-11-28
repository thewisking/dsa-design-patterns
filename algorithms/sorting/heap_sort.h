#pragma once
#include <vector>

template <typename T>
class HeapSort {
  private:
    void heapify(std::vector<T> &data, size_t end) const;
    void sortHelper(std::vector<T> &data, size_t end) const;

  public:
    void sort(std::vector<T> &data) const;
};