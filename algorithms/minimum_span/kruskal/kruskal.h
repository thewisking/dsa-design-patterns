#pragma once

#include "../../../data_structures/union_find/union_find.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

struct KruskalEdge {
    std::size_t u = 0;
    std::size_t v = 0;
    std::int64_t w = 0;

    KruskalEdge() = default;
    KruskalEdge(std::size_t uu, std::size_t vv, std::int64_t ww) : u(uu), v(vv), w(ww) {}
};

struct KruskalResult {
    std::int64_t total_weight = 0;
    std::vector<KruskalEdge> chosen;
    std::size_t components_after = 0;
    bool is_spanning_tree = false;
};

class Kruskal {
  public:
    static KruskalResult run(std::size_t num_vertices, std::vector<KruskalEdge> edges) {
        std::sort(edges.begin(), edges.end(), [](const KruskalEdge &a, const KruskalEdge &b) { return a.w < b.w; });

        KruskalResult result;
        UnionFind uf(num_vertices);
        const std::size_t target_edges = (num_vertices >= 2) ? (num_vertices - 1) : 0;

        result.chosen.reserve(target_edges);

        for (KruskalEdge &edge : edges) {
            if (edge.u >= num_vertices || edge.v >= num_vertices) {
                continue;
            }

            if (uf.unite(edge.u, edge.v)) {
                result.chosen.push_back(edge);
                result.total_weight += edge.w;

                if (result.chosen.size() == target_edges)
                    break;
            }
        }

        result.components_after = uf.components();
        result.is_spanning_tree = (num_vertices <= 1) ? true : (result.components_after == 1);

        return result;
    }
};
