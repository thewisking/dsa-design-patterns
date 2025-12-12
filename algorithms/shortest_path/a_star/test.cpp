// test.cpp
#include <cmath>
#include <iostream>
#include <vector>

#include "a_star.h"

int main() {
    // Graph with 5 nodes: 0, 1, 2, 3, 4
    //
    // Edges (undirected, but stored as two directed edges):
    // 0 --1--> 1
    // 1 --1--> 2
    // 2 --1--> 3
    // 3 --1--> 4
    // 0 --10-> 2   (expensive "shortcut" A* should avoid)
    //
    // Shortest path from 0 to 4 should be: 0 -> 1 -> 2 -> 3 -> 4
    // with total cost 4.0

    AStar::Graph graph(5);

    auto add_undirected_edge = [&](int u, int v, double cost) {
        graph[u].push_back(AStarEdge{v, cost});
        graph[v].push_back(AStarEdge{u, cost});
    };

    add_undirected_edge(0, 1, 1.0);
    add_undirected_edge(1, 2, 1.0);
    add_undirected_edge(2, 3, 1.0);
    add_undirected_edge(3, 4, 1.0);

    // Expensive edge 0 <-> 2 that should NOT be chosen
    add_undirected_edge(0, 2, 10.0);

    // Heuristic: treat nodes as positions on a line, distance = |goal - node|
    AStar::Heuristic heuristic = [](int node, int goal) {
        return static_cast<double>(std::abs(goal - node));
    };

    AStar astar(graph);

    int start = 0;
    int goal = 4;

    std::vector<int> path = astar.find_path(start, goal, heuristic);

    if (path.empty()) {
        std::cout << "No path found from " << start << " to " << goal << "\n";
        return 0;
    }

    std::cout << "Path from " << start << " to " << goal << ": ";
    for (std::size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.size()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";

    double total_cost = 0.0;
    for (std::size_t i = 0; i + 1 < path.size(); ++i) {
        int u = path[i];
        int v = path[i + 1];
        bool found = false;
        for (const auto &edge : graph[u]) {
            if (edge.to == v) {
                total_cost += edge.cost;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Warning: edge " << u << " -> " << v << " not found in graph!\n";
        }
    }

    std::cout << "Total path cost: " << total_cost << "\n";

    return 0;
}
