// astar.h
#pragma once

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

struct AStarEdge {
    int to;
    double cost;
};

class AStar {
  public:
    using Graph = std::vector<std::vector<AStarEdge>>;
    using Heuristic = std::function<double(int node, int goal)>;
    using PQElement = std::pair<double, int>; // cost, node

    explicit AStar(const Graph &graph) : m_graph(graph) {}

    std::vector<int> find_path(int start, int goal, Heuristic h) const {
        // f = g + h  h:heuristic g:cost f: the sum
        std::priority_queue<
            PQElement,               // cost, node
            std::vector<PQElement>,  // vector of cost, node
            std::greater<PQElement>> // min heap
            priority_queue;

        std::vector<double> g_score(m_graph.size(), std::numeric_limits<double>::infinity());
        g_score[start] = 0.0;
        std::vector<int> previous(m_graph.size(), -1);

        double f = g_score[start] + h(start, goal);
        priority_queue.emplace(f, start);

        while (!priority_queue.empty()) {
            auto [f, current] = priority_queue.top();
            priority_queue.pop();

            if (current == goal) {
                std::vector<int> path;

                for (int node = goal; node != -1; node = previous[node]) {
                    path.push_back(node);
                }
                std::reverse(path.begin(), path.end());

                return path;
            }

            for (const auto &edge : m_graph[current]) {
                int neighbour = edge.to;
                double current_g = g_score[current] + edge.cost;

                if (current_g < g_score[neighbour]) {
                    g_score[neighbour] = current_g;
                    previous[neighbour] = current;

                    double f_neighbour = current_g + h(neighbour, goal);
                    priority_queue.emplace(f_neighbour, neighbour);
                }
            }
        }
        return {};
    }

  private:
    const Graph &m_graph;
};
