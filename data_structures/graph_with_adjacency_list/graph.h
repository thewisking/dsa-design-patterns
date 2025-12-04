#pragma once

#include "node.h"
#include <iostream>
#include <list>
#include <vector>

class Graph {
  private:
    std::vector<std::list<Node>> m_list;

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
};