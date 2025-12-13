#include "prim.h"

#include <iostream>
#include <tuple>
#include <vector>

using Vertex = PrimsAlgorithm::Vertex;
using Weight = PrimsAlgorithm::Weight;
using AdjList = PrimsAlgorithm::AdjList;
using Edge = PrimsAlgorithm::Edge;

static void add_edge(AdjList &g, Vertex a, Vertex b, Weight w) {
    g[a].push_back({b, w});
    g[b].push_back({a, w});
}

static void print_edges(const std::vector<Edge> &edges) {
    for (const auto &e : edges) {
        auto [cost, from, to] = e;
        std::cout << "  " << from << " -> " << to << " (cost " << cost << ")\n";
    }
}

static void run_case(const std::string &name,
                     const AdjList &g,
                     Vertex start,
                     bool expected_connected,
                     Weight expected_total,
                     const std::vector<Edge> &expected_edges) {
    std::cout << "===========================\n";
    std::cout << name << "\n\n";

    std::cout << "Expected:\n";
    std::cout << "is_connected = " << (expected_connected ? "true" : "false") << "\n";
    std::cout << "total_weight = " << expected_total << "\n";
    std::cout << "edges:\n";
    print_edges(expected_edges);

    PrimsAlgorithm prim(g);
    auto result = prim.run(start);

    std::cout << "\nGot:\n";
    std::cout << "is_connected = " << (result.is_connected ? "true" : "false") << "\n";
    std::cout << "total_weight = " << result.total_weight << "\n";
    std::cout << "edges:\n";
    print_edges(result.mst_edges);

    std::cout << "\n";
}

int main() {
    AdjList g1(5);
    add_edge(g1, 0, 1, 2);
    add_edge(g1, 0, 3, 6);
    add_edge(g1, 1, 2, 3);
    add_edge(g1, 1, 3, 8);
    add_edge(g1, 1, 4, 5);
    add_edge(g1, 2, 4, 7);
    add_edge(g1, 3, 4, 9);

    run_case("Case 1: connected graph",
             g1,
             0,
             true,
             16,
             {
                 {2, 0, 1},
                 {3, 1, 2},
                 {5, 1, 4},
                 {6, 0, 3},
             });

    AdjList g2(4);
    add_edge(g2, 0, 1, 1);
    add_edge(g2, 2, 3, 1);

    run_case("Case 2: disconnected graph",
             g2,
             0,
             false,
             1,
             {
                 {1, 0, 1},
             });

    AdjList g3(3);
    add_edge(g3, 0, 1, 4);
    add_edge(g3, 1, 2, 2);

    run_case("Case 3: invalid start index",
             g3,
             999,
             false,
             0,
             {});

    return 0;
}
