#include "deque.h"
#include <iostream>

int main() {
    Deque<int> dq;

    std::cout << "pushBack 1,2,3\n";
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);

    std::cout << "front=" << dq.front() << " back=" << dq.back() << "\n";

    std::cout << "pushFront 0\n";
    dq.pushFront(0);

    while (!dq.empty()) {
        std::cout << "popFront -> " << dq.front() << "\n";
        dq.popFront();
    }

    std::cout << "Re-test with back pops\n";
    dq.pushBack(10);
    dq.pushBack(20);
    dq.pushBack(30);
    dq.pushFront(5);

    while (!dq.empty()) {
        std::cout << "popBack -> " << dq.back() << "\n";
        dq.popBack();
    }
}
