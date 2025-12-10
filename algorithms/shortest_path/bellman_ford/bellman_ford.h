#pragma once

#include <cstddef>
#include <limits>
#include <vector>

class BellmanFord {
  public:
    struct Edge {
        std::size_t from;
        std::size_t to;
        long long weight;
    };

    explicit BellmanFord(std::size_t vertex_count)
        : m_vertex_count(vertex_count),
          m_distance(vertex_count, 0),
          m_predecessor(vertex_count, static_cast<std::size_t>(-1)) {} // I gotta cast -1 man all that just for -1 :v

    void add_edge(std::size_t from, std::size_t to, long long weight) { m_edges.push_back(Edge{from, to, weight}); }

    bool run(std::size_t source) {
        const long long INF = std::numeric_limits<long long>::max() / 4;

        if (source >= m_vertex_count) {
            return false;
        }

        m_distance.assign(m_vertex_count, INF);
        m_predecessor.assign(m_vertex_count, static_cast<std::size_t>(-1));
        m_distance[source] = 0;

        bool updated = false;

        for (std::size_t i = 1; i < m_vertex_count; ++i) {
            updated = false;
            for (const auto &e : m_edges) {
                if (m_distance[e.from] == INF) {
                    continue;
                }
                long long cand = m_distance[e.from] + e.weight;
                if (cand < m_distance[e.to]) {
                    m_distance[e.to] = cand;
                    m_predecessor[e.to] = e.from;
                    updated = true;
                }
            }
            if (!updated) {
                return true;
            }
        }

        for (const auto &e : m_edges) {
            if (m_distance[e.from] == INF) {
                continue;
            }
            if (m_distance[e.from] + e.weight < m_distance[e.to]) {
                return false;
            }
        }

        return true;
    }

    bool run_mark_negative_cycles(std::size_t source) {
        const long long INF = std::numeric_limits<long long>::max() / 4;
        const long long NEG_INF = std::numeric_limits<long long>::min() / 4;

        if (source >= m_vertex_count) {
            return false;
        }

        m_distance.assign(m_vertex_count, INF);
        m_predecessor.assign(m_vertex_count, static_cast<std::size_t>(-1));
        m_distance[source] = 0;

        bool updated = false;

        for (std::size_t i = 1; i < m_vertex_count; ++i) {
            updated = false;
            for (const auto &e : m_edges) {
                if (m_distance[e.from] == INF || m_distance[e.from] == NEG_INF) {
                    continue;
                }
                long long cand = m_distance[e.from] + e.weight;
                if (cand < m_distance[e.to]) {
                    m_distance[e.to] = cand;
                    m_predecessor[e.to] = e.from;
                    updated = true;
                }
            }
            if (!updated) {
                return true;
            }
        }

        for (std::size_t i = 0; i < m_vertex_count; ++i) {
            bool changed = false;
            for (const auto &e : m_edges) {
                if (m_distance[e.from] == INF) {
                    continue;
                }
                if (m_distance[e.from] == NEG_INF) {
                    if (m_distance[e.to] != NEG_INF) {
                        m_distance[e.to] = NEG_INF;
                        changed = true;
                    }
                } else {
                    long long cand = m_distance[e.from] + e.weight;
                    if (cand < m_distance[e.to]) {
                        m_distance[e.to] = NEG_INF;
                        changed = true;
                    }
                }
            }
            if (!changed) {
                break;
            }
        }

        return false;
    }

    const std::vector<long long> &distances() const { return m_distance; }

    const std::vector<std::size_t> &predecessors() const { return m_predecessor; }

  private:
    std::size_t m_vertex_count;
    std::vector<Edge> m_edges{};
    std::vector<long long> m_distance;
    std::vector<std::size_t> m_predecessor;
};
