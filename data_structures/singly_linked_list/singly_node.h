#pragma once
#include <utility>

template <typename T>
class SinglyLinkedList;

template <typename T>
class SinglyNode {
    friend class SinglyLinkedList<T>;

  public:
    SinglyNode(const T &value) : m_value(value) {}
    SinglyNode(T &&value) : m_value(std::move(value)) {}

  private:
    T m_value;
    SinglyNode *m_next = nullptr;
};