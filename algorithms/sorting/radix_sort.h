#pragma once
#include <vector>

template <typename T>
class RadixSort {
  private:
    void bucketSort(std::vector<T> &data, int shift) const;

  public:
    void sort(std::vector<T> &data) const;
};