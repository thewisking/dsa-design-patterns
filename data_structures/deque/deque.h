#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class Deque {
  private:
    std::vector<T> m_data;
    std::size_t m_head = 0;
    std::size_t m_count = 0;
    bool isFull() const {
        return m_count == m_data.size();
    }

    void grow() {
        std::size_t oldCap = m_data.size();

        // 2 times the size or 1
        std::size_t newCap = (oldCap == 0) ? 1 : oldCap * 2;
        std::vector<T> newData(newCap);

        for (std::size_t i = 0; i < m_count; i++) {
            newData[i] = std::move(m_data[(m_head + i) % oldCap]);
        }

        m_data = std::move(newData);
        m_head = 0;
    }

    std::size_t backIndex() const {
        return (m_head + m_count - 1) % m_data.size();
    }

  public:
    Deque() = default;

    explicit Deque(std::size_t initialCapacity) : m_data(initialCapacity == 0 ? 1 : initialCapacity) {}

    bool empty() const { return m_count == 0; }
    std::size_t size() const { return m_count; }

    std::size_t capacity() const { return m_data.size(); }

    void clear() {
        m_head = 0;
        m_count = 0;
        // we don't need to clear the contents we just mark it as empty.
        // just like how normal storage isnt cleared we just mark it as empty.
    }

    T &front() {
        if (empty()) {
            throw std::out_of_range("Deque::front on empty deque");
        }
        return m_data[m_head];
    }
    const T &front() const {
        if (empty()) {
            throw std::out_of_range("Deque::front on empty deque");
        }
        return m_data[m_head];
    }

    T &back() {
        if (empty()) {
            throw std::out_of_range("Deque::back on empty deque");
        }
        return m_data[backIndex()];
    }
    const T &back() const {
        if (empty()) {
            throw std::out_of_range("Deque::back on empty deque");
        }
        return m_data[backIndex()];
    }

    void pushBack(const T &value) {
        if (m_data.empty() || isFull()) {
            grow();
        }
        m_data[(m_head + m_count) % m_data.size()] = value;
        m_count++;
    }
    void pushBack(T &&value) {
        if (m_data.empty() || isFull()) {
            grow();
        }
        m_data[(m_head + m_count) % m_data.size()] = std::move(value);
        m_count++;
    }

    void pushFront(const T &value) {
        if (m_data.empty() || isFull()) {
            grow();
        }
        m_head = (m_head + m_data.size() - 1) % m_data.size();
        m_data[m_head] = value;
        m_count++;
    }
    void pushFront(T &&value) {
        if (m_data.empty() || isFull()) {
            grow();
        }
        m_head = (m_head + m_data.size() - 1) % m_data.size();
        m_data[m_head] = std::move(value);
        m_count++;
    }

    void popFront() {
        if (empty()) {
            throw std::out_of_range("Deque::pop_front on empty deque");
        }
        m_head = (m_head + 1) % m_data.size();
        m_count--;
    }
    void popBack() {
        if (empty()) {
            throw std::out_of_range("Deque::pop_back on empty deque");
        }
        m_count--;
    }
};