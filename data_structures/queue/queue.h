#pragma once
#include <vector>

template <typename T>
class Queue {
  private:
    void grow() {
        std::vector<T> newData(data.size() * 2);
        for (std::size_t i = 0; i < count; ++i) {
            newData[i] = data[(head + i) % data.size()];
        }
        data.swap(newData);
        head = 0;
        tail = count;
    }

    std::vector<T> data;
    std::size_t head = 0;
    std::size_t tail = 0;
    std::size_t count = 0;

  public:
    Queue(std::size_t cap = 8) : data(cap) {}
    void enqueue(const T &value) {
        if (count == data.size()) {
            grow();
        }
        data[tail] = value;
        tail = (tail + 1) % data.size();
        count++;
    }
    T dequeue() {
        T value = data[head];
        head = (head + 1) % data.size();
        count--;
        return value;
    }
    bool empty() const { return count == 0; }
};