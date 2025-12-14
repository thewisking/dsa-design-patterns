#pragma once
#include "sort_strategy.h"
#include "sorting/bogo_sort.h"
#include <stdexcept>

class BogoSortStrategy final : public SortStrategy {
  public:
    void sort(std::vector<int> &data) const override {

        if (data.size() > 8) {
            throw std::runtime_error("bogo_sort demo guard: use <= 8 elements");
        }

        BogoSort<int> impl;
        impl.sort(data);
    }

    std::string name() const override { return "bogo_sort"; }
};
