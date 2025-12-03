#pragma once
#include <utility>

template <typename T>
class DoublyLinkedList;

template <typename T>
class DoublyNode {
    friend class DoublyLinkedList<T>;

  public:
    DoublyNode(const T &value) : m_value(value) {}
    DoublyNode(T &&value) : m_value(std::move(value)) {}

  private:
    T m_value;
    DoublyNode *m_next = nullptr;
    DoublyNode *m_prev = nullptr;
};