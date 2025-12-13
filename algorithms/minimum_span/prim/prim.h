#pragma once

#include <cstddef>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

class PrimsAlgorithm {
  public:
    using Vertex = std::size_t;
    using Weight = long long;
    using AdjList = std::vector<std::vector<std::pair<Vertex, Weight>>>;
    using Edge = std::tuple<Weight, Vertex, Vertex>; // cost 3, from node 0, to node 1  (3,0,1)
    using EdgeGreater = std::greater<Edge>;
    struct Result {
        std::vector<Edge> mst_edges;
        Weight total_weight = 0;
        bool is_connected = true;
    };

    explicit PrimsAlgorithm(const AdjList &graph) : m_graph(graph) {}

    // Builds MST starting from 'start'
    Result run(Vertex start = 0) const {
        Result result;

        std::size_t size = m_graph.size();
        std::vector<bool> visited(size, false);
        std::priority_queue<Edge, std::vector<Edge>, EdgeGreater> priority_queue;

        if (size == 0) {
            result.is_connected = true;
            return result;
        }
        if (start >= size) {
            result.is_connected = false;
            return result;
        }

        priority_queue.push({0, start, start});
        std::size_t visited_count = 0;

        result.mst_edges.reserve(size > 0 ? size - 1 : 0);

        while (!priority_queue.empty()) {
            auto [cost, from, to] = priority_queue.top();
            priority_queue.pop();

            if (visited[to])
                continue;

            visited[to] = true;
            ++visited_count;

            if (from != to) {
                result.mst_edges.push_back({cost, from, to});
                result.total_weight += cost;
            }

            for (auto [neighbour, neighbour_cost] : m_graph[to]) {
                if (neighbour >= size)
                    continue;
                if (!visited[neighbour]) {
                    priority_queue.push({neighbour_cost, to, neighbour});
                }
            }
        }

        result.is_connected = (visited_count == size);
        return result;
    }

  private:
    const AdjList &m_graph;
};
