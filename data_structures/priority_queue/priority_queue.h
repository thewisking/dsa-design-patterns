#pragma once

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
  private:
    std::vector<T> m_data;
    Compare m_compare;

    std::size_t parent_index(std::size_t index) const { return (index - 1) / 2; }
    std::size_t left_child_index(std::size_t index) const { return (2 * index + 1); }
    std::size_t right_child_index(std::size_t index) const { return (2 * index) + 2; }

    bool has_left_child(std::size_t index) const { return left_child_index(index) < m_data.size(); }
    bool has_right_child(std::size_t index) const { return right_child_index(index) < m_data.size(); }

    void heapify_up(std::size_t index) {
        while (index != 0) {
            std::size_t parent = parent_index(index);
            if (m_compare(m_data[parent], m_data[index])) {
                std::swap(m_data[parent], m_data[index]);
                index = parent;
            } else {
                break;
            }
        }
    }
    void heapify_down(std::size_t index) {
        while (has_left_child(index)) {
            std::size_t left = left_child_index(index);
            std::size_t right = right_child_index(index);

            std::size_t best_child = left;

            if (has_right_child(index) && m_compare(m_data[left], m_data[right])) {
                best_child = right;
            }

            if (!m_compare(m_data[index], m_data[best_child])) {
                break;
            }

            std::swap(m_data[index], m_data[best_child]);
            index = best_child;
        }
    }

  public:
    PriorityQueue() : m_data(), m_compare() {}
    explicit PriorityQueue(const Compare &compare) : m_data(), m_compare(compare) {}

    bool empty() const { return m_data.empty(); }
    std::size_t size() const { return m_data.size(); }

    const T &top() const { return m_data[0]; }

    void push(const T &value) {
        m_data.push_back(value);
        heapify_up(m_data.size() - 1);
    }
    void push(T &&value) {
        m_data.push_back(std::move(value));
        heapify_up(m_data.size() - 1);
    }

    template <typename InputIt>
    void insert_range(InputIt first, InputIt last) {
        m_data.insert(m_data.end(), first, last);

        if (m_data.empty()) {
            return;
        }

        for (std::size_t i = m_data.size() / 2; i-- > 0;) {
            heapify_down(i);
        }
    }

    void pop() {
        if (m_data.empty()) {
            return;
        }

        std::swap(m_data[0], m_data[m_data.size() - 1]);
        m_data.pop_back();

        if (!m_data.empty()) {
            heapify_down(0);
        }
    }
    void clear() { m_data.clear(); }
};
