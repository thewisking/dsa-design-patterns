#pragma once
#include "sorting/bubble_sort.h"
#include "sort_strategy.h"

class BubbleSortStrategy final : public SortStrategy {
  public:
    void sort(std::vector<int> &data) const override {
        BubbleSort<int> impl;
        impl.sort(data);
    }

    std::string name() const override { return "bubble_sort"; }
};
