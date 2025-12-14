#pragma once
#include <string>
#include <vector>

class SortStrategy {
  public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int> &data) const = 0;
    virtual std::string name() const = 0;
};
