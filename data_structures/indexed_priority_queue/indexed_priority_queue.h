#pragma once

#include <cstddef>
#include <vector>

template <typename Key>
class IndexedPriorityQueue {
  public:
    explicit IndexedPriorityQueue(std::size_t capacity);

    bool empty() const;
    bool contains(int index) const;
    void insert(int index, const Key &key);
    void decrease_key(int index, const Key &key);
    int pop_min();

  private:
    int m_n;
    std::vector<int> m_pq;
    std::vector<int> m_qp;
    std::vector<Key> m_keys;
};
