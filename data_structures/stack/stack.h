#pragma once
#include <vector>

template <typename T>
class Stack {
  private:
    std::vector<T> data_;

  public:
    void pop() { data_.pop_back(); }
    void push(const T &value) { data_.push_back(value); }
    T &top() { return data_.back(); }
    bool empty() const { return data_.empty(); }
    std::size_t size() { return data_.size(); }
};