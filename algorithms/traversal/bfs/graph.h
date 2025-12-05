#pragma once

#include "node.h"
#include <iostream>
#include <list>
#include <queue>
#include <vector>

class Graph {
  private:
    std::vector<std::list<Node>> m_list;

    bool bfs_helper(std::size_t source, std::size_t destination, std::vector<bool> &visited, int &traversalCount) {
        std::queue<std::size_t> queue;

        visited[source] = true;
        queue.push(source);

        while (!queue.empty()) {
            std::size_t current = queue.front();
            queue.pop();

            if (current == destination) {
                return true;
            }
            for (const Node &neighbour : m_list[current]) {
                std::size_t value = static_cast<std::size_t>(neighbour.id);
                if (value >= m_list.size()) {
                    continue;
                }
                if (!visited[value]) {
                    // std::cout << neighbour.id << "   "; :>  
                    ++traversalCount;
                    visited[value] = true;
                    if (value == destination) {
                        return true;
                    }
                    queue.push(value);
                }
            }
        }
        return false;
    }

  public:
    Graph(std::size_t numVerticies) : m_list(numVerticies) {}

    void addNode(Node node) {
        if (node.id < 0) {
            return;
        }

        std::size_t index = static_cast<std::size_t>(node.id);

        if (index >= m_list.size()) {
            m_list.resize(index + 1);
        }
    }
    void addEdge(int source, int destination) {
        if (source < 0 || destination < 0) {
            return;
        }
        std::size_t casted_source = static_cast<std::size_t>(source);
        std::size_t casted_destination = static_cast<std::size_t>(destination);

        if (casted_source >= m_list.size() || casted_destination >= m_list.size()) {
            return;
        }

        m_list[casted_source].push_back(Node(casted_destination));
    }
    bool checkEdge(int source, int destination) {
        if (source < 0 || destination < 0) {
            return false;
        }
        std::size_t casted_source = static_cast<std::size_t>(source);
        std::size_t casted_destination = static_cast<std::size_t>(destination);

        if (casted_source >= m_list.size() || casted_destination >= m_list.size()) {
        }

        for (const Node &neighbour : m_list[casted_source]) {
            if (neighbour.id == destination) {
                return true;
            }
        }
        return false;
    }
    void print() const {
        for (std::size_t i = 0; i < m_list.size(); ++i) {
            std::cout << i << ": ";

            for (const Node &neighbour : m_list[i]) {
                std::cout << neighbour.id << " ";
            }

            std::cout << "\n";
        }
    }

    int bfs(int source_index, int destination_index) {
        if (source_index < 0 || destination_index < 0) {
            return -1;
        }

        std::size_t source = static_cast<size_t>(source_index);
        std::size_t destination = static_cast<size_t>(destination_index);

        if (source >= m_list.size() || destination >= m_list.size()) {
            return -1;
        }

        std::vector<bool> visited(m_list.size(), false);
        int traversalCount = 0;
        bool found = bfs_helper(source, destination, visited, traversalCount);
        if (!found) {
            return -1;
        }
        return traversalCount;
    }
};