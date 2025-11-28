#pragma once
#include <vector>

template <typename T>
class MergeSort {
  public:
    void sort(std::vector<T> &data) const;

  private:
    void sortHelper(std::vector<T> &leftArray, std::vector<T> &rightAray, std::vector<T> &array) const;
};