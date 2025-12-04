#include "priority_queue.h"
#include <iostream>
#include <vector>

int main() {
    PriorityQueue<int> pq;

    pq.push(5);
    pq.push(1);
    pq.push(9);
    pq.push(3);
    pq.push(7);

    std::cout << "Popping elements (should be in descending order):\n";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";

    std::vector<int> values;
    values.push_back(10);
    values.push_back(4);
    values.push_back(8);
    values.push_back(15);
    values.push_back(2);

    PriorityQueue<int> pq2;
    pq2.insert_range(values.begin(), values.end());

    std::cout << "Popping elements from pq2 (should be 15 10 8 4 2):\n";
    while (!pq2.empty()) {
        std::cout << pq2.top() << " ";
        pq2.pop();
    }
    std::cout << "\n";

    struct GreaterInt {
        bool operator()(const int &a, const int &b) const {
            return a > b;
        }
    };

    PriorityQueue<int, GreaterInt> min_pq;

    min_pq.push(5);
    min_pq.push(1);
    min_pq.push(9);
    min_pq.push(3);

    std::cout << "Popping elements from min-heap (should be ascending: 1 3 5 9):\n";
    while (!min_pq.empty()) {
        std::cout << min_pq.top() << " ";
        min_pq.pop();
    }
    std::cout << "\n";

    return 0;
}
