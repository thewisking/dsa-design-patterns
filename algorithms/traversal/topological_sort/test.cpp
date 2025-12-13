#include <iostream>
#include <optional>
#include <vector>

#include "topological_sort.h"

static void print_order(const std::optional<TopologicalSort::Order> &res) {
    if (!res) {
        std::cout << "nullopt";
        return;
    }
    std::cout << "[";
    for (std::size_t i = 0; i < res->size(); ++i) {
        std::cout << (*res)[i];
        if (i + 1 < res->size())
            std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    using Graph = TopologicalSort::AdjacencyList;

    // Test 1: Simple DAG
    // 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
    Graph dag1 = {
        {1, 2},
        {3},
        {3},
        {}};

    std::cout << "Test 1 (DAG)\n";
    std::cout << "Should be: a valid topo order such that 0 before 1&2, and 1&2 before 3.\n";
    std::cout << "Example:  [0, 1, 2, 3] or [0, 2, 1, 3]\n";
    std::cout << "It is:    ";
    print_order(TopologicalSort::sort(dag1));
    std::cout << "\n\n";

    // Test 2: DAG with multiple valid starts
    // 0 -> 2, 1 -> 2, 1 -> 3
    Graph dag2 = {
        {2},
        {2, 3},
        {},
        {}};

    std::cout << "Test 2 (DAG)\n";
    std::cout << "Should be: a valid topo order such that 0 and 1 are before 2, and 1 before 3.\n";
    std::cout << "Example:  [0, 1, 2, 3] or [1, 0, 3, 2] or [1, 0, 2, 3]\n";
    std::cout << "It is:    ";
    print_order(TopologicalSort::sort(dag2));
    std::cout << "\n\n";

    // Test 3: Cycle
    // 0 -> 1 -> 2 -> 0
    Graph cycle = {
        {1},
        {2},
        {0}};

    std::cout << "Test 3 (Cycle)\n";
    std::cout << "Should be: nullopt\n";
    std::cout << "It is:    ";
    print_order(TopologicalSort::sort(cycle));
    std::cout << "\n";

    return 0;
}
