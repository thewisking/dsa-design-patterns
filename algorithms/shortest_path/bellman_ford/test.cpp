#include "bellman_ford.h"
#include <iostream>
#include <limits>

void print_result(const BellmanFord &bf, const std::string &label) {
    const long long INF = std::numeric_limits<long long>::max() / 4;
    const long long NEG_INF = std::numeric_limits<long long>::min() / 4;

    std::cout << label << "\n";
    const auto &dist = bf.distances();
    const auto &pred = bf.predecessors();

    for (std::size_t i = 0; i < dist.size(); ++i) {
        std::cout << "vertex " << i << ": ";
        if (dist[i] == INF) {
            std::cout << "INF";
        } else if (dist[i] == NEG_INF) {
            std::cout << "-INF";
        } else {
            std::cout << dist[i];
        }
        std::cout << ", pred=";
        if (pred[i] == static_cast<std::size_t>(-1)) {
            std::cout << "none";
        } else {
            std::cout << pred[i];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    {
        BellmanFord bf(5);
        bf.add_edge(0, 1, 6);
        bf.add_edge(0, 2, 7);
        bf.add_edge(1, 2, 8);
        bf.add_edge(1, 3, 5);
        bf.add_edge(1, 4, -4);
        bf.add_edge(2, 3, -3);
        bf.add_edge(2, 4, 9);
        bf.add_edge(3, 1, -2);
        bf.add_edge(4, 0, 2);
        bf.add_edge(4, 3, 7);

        bool ok = bf.run(0);
        std::cout << "Graph 1 (no negative cycle), run() returned: " << (ok ? "true" : "false") << "\n";
        print_result(bf, "Distances for Graph 1");
    }

    {
        BellmanFord bf(4);
        bf.add_edge(0, 1, 1);
        bf.add_edge(1, 2, 1);
        bf.add_edge(2, 1, -3);
        bf.add_edge(2, 3, 2);

        bool ok = bf.run_mark_negative_cycles(0);
        std::cout << "Graph 2 (negative cycle), run_mark_negative_cycles() returned: " << (ok ? "true" : "false") << "\n";
        print_result(bf, "Distances for Graph 2 (negative cycles marked)");
    }

    return 0;
}
