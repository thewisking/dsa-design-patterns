#include "dijkstra.h" // <- change this to your actual header filename
#include <iostream>
#include <limits>
#include <vector>

int main() {
    using Weight = int;
    Dijkstra<Weight> dijkstra;

    // Build graph:
    // 0 -> 1 (4), 0 -> 2 (1)
    // 1 -> 3 (1)
    // 2 -> 1 (2), 2 -> 3 (5)
    // 3 -> 4 (3)
    // 4 -> (no edges)
    // this example can be visualized at: https://www.youtube.com/watch?v=pSqmAO-m7Lk .com.mars.au

    Dijkstra<Weight>::Graph graph(5);

    graph[0].push_back({1, 4});
    graph[0].push_back({2, 1});

    graph[1].push_back({3, 1});

    graph[2].push_back({1, 2});
    graph[2].push_back({3, 5});

    graph[3].push_back({4, 3});

    int start = 0;
    int end = 4;

    // Test 1: all shortest paths
    auto [distance, previous] = dijkstra.lazy_shortest_paths(graph, start);

    std::cout << "Distances from node " << start << ":\n";
    for (std::size_t i = 0; i < distance.size(); ++i) {
        std::cout << "  dist[" << i << "] = ";
        if (distance[i] == std::numeric_limits<Weight>::max()) {
            std::cout << "INF";
        } else {
            std::cout << distance[i];
        }
        std::cout << '\n';
    }

    std::cout << "\nPrevious array:\n";
    for (std::size_t i = 0; i < previous.size(); ++i) {
        std::cout << "  prev[" << i << "] = " << previous[i] << '\n';
    }

    // Test 2: shortest path to a single node using lazy_shortest_path_to
    auto path_to = dijkstra.lazy_shortest_path_to(graph, start, end);

    std::cout << "\nPath from " << start << " to " << end
              << " using lazy_shortest_path_to:\n";

    if (path_to.empty()) {
        std::cout << "  No path found.\n";
    } else {
        std::cout << "  ";
        for (std::size_t i = 0; i < path_to.size(); ++i) {
            std::cout << path_to[i];
            if (i + 1 < path_to.size())
                std::cout << " -> ";
        }
        std::cout << '\n';
    }

    // Test 3: reconstruct_path using the full SSSP result-
    auto path_from_prev = dijkstra.reconstruct_path(previous, distance, end);

    std::cout << "\nPath from " << start << " to " << end
              << " using reconstruct_path(previous, distance, end):\n";

    if (path_from_prev.empty()) {
        std::cout << "  No path found.\n";
    } else {
        std::cout << "  ";
        for (std::size_t i = 0; i < path_from_prev.size(); ++i) {
            std::cout << path_from_prev[i];
            if (i + 1 < path_from_prev.size())
                std::cout << " -> ";
        }
        std::cout << '\n';
    }

    return 0;
}
