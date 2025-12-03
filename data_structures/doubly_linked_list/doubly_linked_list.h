#pragma once
#include "doubly_node.h"
#include <cassert>
#include <cstddef>
#include <utility>

template <typename T>
class DoublyLinkedList {
  public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList &other) {
        if (other.m_head == nullptr) {
            return;
        }

        m_head = new DoublyNode<T>(other.m_head->m_value);
        m_tail = m_head;
        m_size = 1;

        DoublyNode<T> *currentOtherNode = other.m_head->m_next;
        while (currentOtherNode != nullptr) {
            DoublyNode<T> *newNode = new DoublyNode<T>(currentOtherNode->m_value);
            if (m_tail != nullptr) {
                newNode->m_prev = m_tail;
            }
            m_tail->m_next = newNode;
            m_tail = newNode;
            m_size++;
            currentOtherNode = currentOtherNode->m_next;
        }
    }
    DoublyLinkedList(DoublyLinkedList &&other) noexcept
        : m_head(other.m_head),
          m_tail(other.m_tail),
          m_size(other.m_size) {

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    DoublyLinkedList &operator=(const DoublyLinkedList &other) {
        if (this == &other) {
            return *this;
        }

        clear();

        if (other.m_head == nullptr) {
            return *this;
        }

        m_head = new DoublyNode<T>(other.m_head->m_value);
        m_tail = m_head;
        m_size = 1;

        DoublyNode<T> *currentOtherNode = other.m_head->m_next;

        while (currentOtherNode != nullptr) {
            DoublyNode<T> *newNode = new DoublyNode<T>(currentOtherNode->m_value);
            newNode->m_prev = m_tail;
            m_tail->m_next = newNode;
            m_tail = newNode;
            m_size++;
            currentOtherNode = currentOtherNode->m_next;
        }
        return *this;
    }
    DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept {

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

    ~DoublyLinkedList() {
        clear();
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
        auto *node = new DoublyNode<T>(value);

        if (m_head == nullptr) {
            m_tail = node;
        } else {
            node->m_next = m_head;
            m_head->m_prev = node;
        }

        m_head = node;
        m_size++;
    }
    void push_front(T &&value) {
        auto *node = new DoublyNode<T>(std::move(value));

        if (m_head == nullptr) {
            m_tail = node;
        } else {
            node->m_next = m_head;
            m_head->m_prev = node;
        }

        m_head = node;
        m_size++;
    }

    void push_back(const T &value) {
        auto *node = new DoublyNode<T>(value);
        if (m_tail != nullptr) {
            node->m_prev = m_tail;
            m_tail->m_next = node;
        } else {
            m_head = node;
        }

        m_tail = node;
        m_size++;
    }
    void push_back(T &&value) {
        auto *node = new DoublyNode<T>(std::move(value));
        if (m_tail != nullptr) {
            node->m_prev = m_tail;
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
        } else {
            m_head->m_prev = nullptr;
        }
        delete toPop;
        --m_size;
    }
    void pop_back() {
        if (m_tail == nullptr) {
            return;
        }

        DoublyNode<T> *toPop = m_tail;
        m_tail = m_tail->m_prev;

        if (m_tail == nullptr) {
            m_head = nullptr;
        } else {
            m_tail->m_next = nullptr;
        }

        delete toPop;
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
        DoublyNode<T> *currentNode = nullptr;

        if (index < m_size / 2) {
            currentNode = m_head;
            while (currentIndex < (index - 1)) {
                currentNode = currentNode->m_next;
                currentIndex++;
            }
        } else {
            currentNode = m_tail;
            currentIndex = m_size - 1;
            while (currentIndex > (index - 1)) {
                currentNode = currentNode->m_prev;
                currentIndex--;
            }
        }

        auto *newNode = new DoublyNode<T>(value);
        newNode->m_next = currentNode->m_next;
        newNode->m_prev = currentNode;
        if (currentNode->m_next != nullptr) {
            currentNode->m_next->m_prev = newNode;
        }
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
        DoublyNode<T> *currentNode = nullptr;

        if (index < m_size / 2) {
            currentNode = m_head;
            while (currentIndex < (index - 1)) {
                currentNode = currentNode->m_next;
                currentIndex++;
            }
        } else {
            currentNode = m_tail;
            currentIndex = m_size - 1;
            while (currentIndex > (index - 1)) {
                currentNode = currentNode->m_prev;
                currentIndex--;
            }
        }

        auto *newNode = new DoublyNode<T>(std::move(value));
        newNode->m_next = currentNode->m_next;
        newNode->m_prev = currentNode;
        if (currentNode->m_next != nullptr) {
            currentNode->m_next->m_prev = newNode;
        }
        currentNode->m_next = newNode;
        m_size++;
        return;
    }

    // delete
    void erase(std::size_t index) {
        assert(index < m_size && "erase() index out of range");

        if (index == (m_size - 1)) {
            pop_back();
            return;
        }

        if (index == 0) {
            pop_front();
            return;
        }

        std::size_t currentIndex = 0;
        DoublyNode<T> *currentNode = nullptr;

        if (index < m_size / 2) {
            currentNode = m_head;
            while (currentIndex < (index - 1)) {
                currentNode = currentNode->m_next;
                currentIndex++;
            }
        } else {
            currentNode = m_tail;
            currentIndex = m_size - 1;
            while (currentIndex > (index - 1)) {
                currentNode = currentNode->m_prev;
                currentIndex--;
            }
        }

        auto *toPop = currentNode->m_next;
        currentNode->m_next = toPop->m_next;
        toPop->m_next->m_prev = currentNode;

        delete toPop;
        m_size--;
        return;
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
    DoublyNode<T> *m_head = nullptr;
    DoublyNode<T> *m_tail = nullptr;
    std::size_t m_size = 0;
};