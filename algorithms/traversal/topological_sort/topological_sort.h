#pragma once

#include <cstddef>
#include <optional>
#include <queue>
#include <vector>

class TopologicalSort {
  public:
    using AdjacencyList = std::vector<std::vector<std::size_t>>;
    using Order = std::vector<std::size_t>;

    // Returns a topological ordering if the graph is a DAG.
    // If the graph contains a cycle, returns std::nullopt.
    static std::optional<Order> sort(const AdjacencyList &graph) {
        const std::size_t size = graph.size();
        std::vector<std::size_t> indeg(size, 0);

        // get the degree of every vertex in indeg
        for (std::size_t i = 0; i < size; i++) {
            for (std::size_t v : graph[i]) {
                ++indeg[v];
            }
        }

        std::queue<std::size_t> queue;
        for (std::size_t i = 0; i < size; i++) {
            if (indeg[i] == 0) {
                queue.push(i);
            }
        }

        Order order;
        order.reserve(size);
        while (!queue.empty()) {
            std::size_t u = queue.front();
            queue.pop();

            order.push_back(u);

            for (std::size_t v : graph[u]) {
                if (--indeg[v] == 0) {
                    queue.push(v);
                }
            }
        }

        if (order.size() != size)
            return std::nullopt;
        return order;
    }
};
