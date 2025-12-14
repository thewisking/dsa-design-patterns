#pragma once
#include <vector>

template <typename T>
class BogoSort {
  private:
    bool isSorted(const std::vector<T> &data) const;

  public:
    void sort(std::vector<T> &data) const;
};