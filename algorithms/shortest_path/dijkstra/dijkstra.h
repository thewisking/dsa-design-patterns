#pragma once

#include "../../../data_structures/indexed_priority_queue/indexed_priority_queue.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

// This is a greedy single source shortest path algorithm for nono-negative edge weights.
// in other words, this is a graph algorithm that returns the shortest path from one node to all other nodes
// assuming a weighted non-negative graph.
// O( E log(V) )
template <typename T>
class Dijkstra {
  private:
  public:
    struct Edge {
        int to;
        T cost;
    };

    using Graph = std::vector<std::vector<Edge>>;

    static bool is_reachable(const std::vector<T> &distance, int node) {
        if (node < 0 || static_cast<std::size_t>(node) >= distance.size())
            return false;

        return distance[node] != std::numeric_limits<T>::max();
    }

    std::vector<int> reconstruct_path(const std::vector<int> &prev, const std::vector<T> &distance, int end) {
        if (end < 0)
            return {};

        std::size_t n = distance.size();
        if (static_cast<std::size_t>(end) >= n)
            return {};

        if (prev.size() != n)
            return {};

        if (distance[end] == std::numeric_limits<T>::max())
            return {};

        std::vector<int> path;
        int cur = end;

        while (cur != -1) {
            if (static_cast<std::size_t>(cur) >= n)
                return {};

            path.push_back(cur);
            cur = prev[cur];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    std::pair<std::vector<T>, std::vector<int>> lazy_shortest_paths(const Graph &graph, int start) {
        std::size_t size = graph.size();

        if (start < 0 || static_cast<std::size_t>(start) >= size)
            return {{}, {}}; // lol just average c++ magic - return an empty pair of two empty vectors

        std::vector<bool> visited(size, false);

        std::vector<int> previous(size, -1);

        std::priority_queue<
            std::pair<T, int>,
            std::vector<std::pair<T, int>>,
            std::greater<std::pair<T, int>>>
            priority_queue;

        std::vector<T> distance(size, std::numeric_limits<T>::max());
        distance[start] = 0;

        priority_queue.push({distance[start], start});

        while (!priority_queue.empty()) {
            auto [current_distance, node] = priority_queue.top();
            priority_queue.pop();

            if (visited[node])
                continue;

            if (distance[node] < current_distance)
                continue;

            visited[node] = true;

            for (const auto &edge : graph[node]) {
                if (visited[edge.to])
                    continue;

                T newDistance = current_distance + edge.cost;
                if (newDistance < distance[edge.to]) {
                    previous[edge.to] = node;
                    distance[edge.to] = newDistance;
                    priority_queue.push({newDistance, edge.to});
                }
            }
        }
        return {distance, previous};
    }

    std::vector<int> lazy_shortest_path_to(const Graph &graph, int start, int end) {
        std::size_t size = graph.size();

        if (start < 0 || static_cast<std::size_t>(start) >= size)
            return {};
        if (end < 0 || static_cast<std::size_t>(end) >= size)
            return {};

        std::vector<bool> visited(size, false);

        std::vector<int> previous(size, -1);

        std::priority_queue<
            std::pair<T, int>,
            std::vector<std::pair<T, int>>,
            std::greater<std::pair<T, int>>>
            priority_queue;

        std::vector<T> distance(size, std::numeric_limits<T>::max());
        distance[start] = 0;

        priority_queue.push({distance[start], start});

        while (!priority_queue.empty()) {
            auto [current_distance, node] = priority_queue.top();
            priority_queue.pop();

            if (visited[node])
                continue;

            if (distance[node] < current_distance)
                continue;

            visited[node] = true;

            for (const auto &edge : graph[node]) {
                if (visited[edge.to])
                    continue;

                T newDistance = current_distance + edge.cost;
                if (newDistance < distance[edge.to]) {
                    previous[edge.to] = node;
                    distance[edge.to] = newDistance;
                    priority_queue.push({newDistance, edge.to});
                }
            }
            if (node == end) {
                return reconstruct_path(previous, distance, end);
            }
        }
        return reconstruct_path(previous, distance, end);
    }

    std::pair<std::vector<T>, std::vector<int>> eager_shortest_paths(const Graph &graph, int start) {
        std::size_t n = graph.size();
        if (n == 0)
            return {{}, {}};

        if (start < 0 || static_cast<std::size_t>(start) >= n)
            return {{}, {}};

        std::vector<T> distance(n, std::numeric_limits<T>::max());
        std::vector<int> previous(n, -1);
        std::vector<bool> visited(n, false);

        IndexedPriorityQueue<T> pq(n);

        distance[start] = T{0};
        pq.insert(start, distance[start]);

        while (!pq.empty()) {
            int u = pq.pop_min();
            if (u == -1)
                break;

            if (visited[u])
                continue;
            visited[u] = true;

            for (const auto &edge : graph[u]) {
                int v = edge.to;
                if (v < 0 || static_cast<std::size_t>(v) >= n)
                    continue;
                if (visited[v])
                    continue;

                T newDist = distance[u] + edge.cost;
                if (newDist < distance[v]) {
                    distance[v] = newDist;
                    previous[v] = u;

                    if (pq.contains(v)) {
                        pq.decrease_key(v, newDist);
                    } else {
                        pq.insert(v, newDist);
                    }
                }
            }
        }

        return {distance, previous};
    }

    std::vector<int> eager_shortest_path_to(const Graph &graph, int start, int end) {
        std::size_t n = graph.size();
        if (n == 0)
            return {};

        if (start < 0 || static_cast<std::size_t>(start) >= n)
            return {};
        if (end < 0 || static_cast<std::size_t>(end) >= n)
            return {};

        std::vector<T> distance(n, std::numeric_limits<T>::max());
        std::vector<int> previous(n, -1);
        std::vector<bool> visited(n, false);

        IndexedPriorityQueue<T> pq(n);

        distance[start] = T{0};
        pq.insert(start, distance[start]);

        while (!pq.empty()) {
            int u = pq.pop_min();
            if (u == -1)
                break;

            if (visited[u])
                continue;
            visited[u] = true;

            if (u == end) {
                return reconstruct_path(previous, distance, end);
            }

            for (const auto &edge : graph[u]) {
                int v = edge.to;
                if (v < 0 || static_cast<std::size_t>(v) >= n)
                    continue;
                if (visited[v])
                    continue;

                T newDist = distance[u] + edge.cost;
                if (newDist < distance[v]) {
                    distance[v] = newDist;
                    previous[v] = u;

                    if (pq.contains(v)) {
                        pq.decrease_key(v, newDist);
                    } else {
                        pq.insert(v, newDist);
                    }
                }
            }
        }

        return reconstruct_path(previous, distance, end);
    }

    // TODO: make an indexed priority queue then link it here and do the eager implementation.
};