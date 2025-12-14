#include "ford_fulkerson.h"
#include <iostream>
#include <vector>

int main() {
    FordFulkersonMaxFlow mf(6);

    struct E {
        int u, v;
        long long cap;
    };
    std::vector<E> edges = {
        {0, 1, 16}, {0, 2, 13}, {1, 2, 10}, {2, 1, 4}, {1, 3, 12}, {2, 4, 14}, {3, 2, 9}, {4, 3, 7}, {3, 5, 20}, {4, 5, 4}};

    for (auto &e : edges)
        mf.add_edge(e.u, e.v, e.cap);

    long long flow = mf.max_flow(0, 5);
    std::cout << "Computed max flow = " << flow << "\n";
    std::cout << "Expected max flow = 23\n\n";

    const auto &g = mf.graph();

    std::cout << "Flow on edges (u -> v):\n";
    for (auto &e : edges) {
        long long used = 0;

        for (const auto &ed : g[e.u]) {
            if (ed.to == e.v) {
                used = g[e.v][ed.rev].cap;
                break;
            }
        }

        std::cout << "  " << e.u << " -> " << e.v
                  << "  used " << used << " / " << e.cap << "\n";
    }

    return 0;
}
