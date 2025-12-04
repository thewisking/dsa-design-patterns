// test_queue.cpp
#include "queue.h"
#include <iostream>

int main() {
    std::cout << "Creating Queue<int> q...\n";
    Queue<int> q;

    std::cout << "\nEnqueue 1, 2, 3\n";
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    std::cout << "Dequeuing two elements:\n";
    if (!q.empty())
        std::cout << "dequeue -> " << q.dequeue() << "\n";
    if (!q.empty())
        std::cout << "dequeue -> " << q.dequeue() << "\n";

    std::cout << "\nEnqueue 4, 5, 6, 7\n";
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);

    std::cout << "\nDraining the rest of the queue:\n";
    while (!q.empty()) {
        std::cout << "dequeue -> " << q.dequeue() << "\n";
    }

    std::cout << "\nQueue should now be empty.\n";
    return 0;
}
