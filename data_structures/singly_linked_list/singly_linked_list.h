#pragma once
#include "singly_node.h"
#include <cassert>
#include <cstddef>
#include <ostream>
#include <utility>

template <typename T>
class SinglyLinkedList {
  public:
    SinglyLinkedList() = default;
    SinglyLinkedList(const SinglyLinkedList &other) {
        if (other.m_head == nullptr) {
            return;
        }
        m_head = new SinglyNode<T>(other.m_head->m_value);
        m_tail = m_head;
        m_size = 1;

        SinglyNode<T> *currentOtherNode = other.m_head->m_next;

        while (currentOtherNode != nullptr) {
            SinglyNode<T> *newNode = new SinglyNode<T>(currentOtherNode->m_value);
            m_tail->m_next = newNode;
            m_tail = newNode;
            m_size++;
            currentOtherNode = currentOtherNode->m_next;
        }
    }
    SinglyLinkedList(SinglyLinkedList &&other) noexcept
        : m_head(other.m_head),
          m_tail(other.m_tail),
          m_size(other.m_size) {

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    SinglyLinkedList &operator=(const SinglyLinkedList &other) {
        if (this == &other) {
            return *this;
        }

        clear();

        if (other.m_head == nullptr) {
            return *this;
        }

        m_head = new SinglyNode<T>(other.m_head->m_value);
        m_tail = m_head;
        m_size = 1;

        SinglyNode<T> *currentOtherNode = other.m_head->m_next;

        while (currentOtherNode != nullptr) {
            SinglyNode<T> *newNode = new SinglyNode<T>(currentOtherNode->m_value);
            m_tail->m_next = newNode;
            m_tail = newNode;
            m_size++;
            currentOtherNode = currentOtherNode->m_next;
        }
        return *this;
    }
    SinglyLinkedList &operator=(SinglyLinkedList &&other) noexcept {

        if (this == &other) {
            return *this;
        }

        clear();

        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
        return *this;
    }

    ~SinglyLinkedList() {
        auto *node = m_head;

        while (node) {
            auto *next = node->m_next;
            delete node;
            node = next;
        }
    }

    // capacity
    bool empty() const { return (m_size == 0); }
    std::size_t size() const { return m_size; }

    // element access
    const T &front() const {
        assert(m_head != nullptr && "front() called on empty list");
        return m_head->m_value;
    }
    T &front() {
        assert(m_head != nullptr && "front() called on empty list");
        return m_head->m_value;
    }

    const T &back() const {
        assert(m_tail != nullptr && "back() called on empty list");
        return m_tail->m_value;
    }
    T &back() {
        assert(m_tail != nullptr && "back() called on empty list");
        return m_tail->m_value;
    }

    // O(1) push modifiers
    void push_front(const T &value) {
        auto *node = new SinglyNode<T>(value);
        node->m_next = m_head;
        m_head = node;
        if (!m_tail) {
            m_tail = node;
        }
        m_size++;
    }
    void push_front(T &&value) {
        auto *node = new SinglyNode<T>(std::move(value));
        node->m_next = m_head;
        m_head = node;
        if (!m_tail) {
            m_tail = node;
        }
        m_size++;
    }

    void push_back(const T &value) {
        auto *node = new SinglyNode<T>(value);
        if (m_tail != nullptr) {
            m_tail->m_next = node;
        } else {
            m_head = node;
        }

        m_tail = node;
        m_size++;
    }
    void push_back(T &&value) {
        auto *node = new SinglyNode<T>(std::move(value));
        if (m_tail != nullptr) {
            m_tail->m_next = node;
        } else {
            m_head = node;
        }

        m_tail = node;
        m_size++;
    }

    // O(1) pop modifiers
    void pop_front() {
        if (m_head == nullptr) {
            return;
        }
        auto *toPop = m_head;
        m_head = m_head->m_next;
        if (m_head == nullptr) {
            m_tail = nullptr;
        }
        delete toPop;
        --m_size;
    }
    void pop_back() {
        if (m_head == nullptr) {
            return;
        }

        if (m_head == m_tail) {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
            return;
        }

        auto *prev = m_head;
        while (prev->m_next != m_tail) {
            prev = prev->m_next;
        }

        delete m_tail;
        m_tail = prev;
        m_tail->m_next = nullptr;
        --m_size;
    }

    // insertion
    void insert(std::size_t index, const T &value) {
        assert(index <= m_size && "insert() index out of range");

        if (index == m_size) {
            push_back(value);
            return;
        }

        if (index == 0) {
            push_front(value);
            return;
        }

        std::size_t currentIndex = 0;
        auto *currentNode = m_head;

        while (currentIndex < (index - 1) && currentNode != nullptr) {
            currentNode = currentNode->m_next;
            currentIndex++;
        }

        auto *newNode = new SinglyNode<T>(value);
        newNode->m_next = currentNode->m_next;
        currentNode->m_next = newNode;
        m_size++;
        return;
    }
    void insert(std::size_t index, T &&value) {
        assert(index <= m_size && "insert() index out of range");

        if (index == m_size) {
            push_back(std::move(value));
            return;
        }

        if (index == 0) {
            push_front(std::move(value));
            return;
        }

        std::size_t currentIndex = 0;
        auto *currentNode = m_head;

        while (currentIndex < (index - 1) && currentNode != nullptr) {
            currentNode = currentNode->m_next;
            currentIndex++;
        }

        auto *newNode = new SinglyNode<T>(std::move(value));
        newNode->m_next = currentNode->m_next;
        currentNode->m_next = newNode;
        m_size++;
        return;
    }

    // delete
    void erase(std::size_t index) {
        assert(index < m_size && "erase() index out of range");

        if (index == 0) {
            pop_front();
            return;
        }

        std::size_t currentIndex = 0;
        auto *currentNode = m_head;

        while (currentIndex < (index - 1)) {
            currentNode = currentNode->m_next;
            currentIndex++;
        }

        auto *toErase = currentNode->m_next;
        currentNode->m_next = toErase->m_next;

        if (toErase == m_tail) {
            m_tail = currentNode;
        }

        delete toErase;

        m_size--;
    }
    void clear() {
        auto *node = m_head;

        while (node) {
            auto *next = node->m_next;
            delete node;
            node = next;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    // search
    std::size_t find(const T &value) const {
        const auto *currentNode = m_head;
        std::size_t index = 0;

        while (currentNode != nullptr) {
            if (currentNode->m_value == value) {
                return index;
            }
            currentNode = currentNode->m_next;
            index++;
        }
        return m_size;
    }

  private:
    SinglyNode<T> *m_head = nullptr;
    SinglyNode<T> *m_tail = nullptr;
    std::size_t m_size = 0;
};