#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>

class FordFulkersonMaxFlow {
  public:
    using Cap = long long;

    struct Edge {
        int to;
        int rev;
        Cap cap;
    };

    explicit FordFulkersonMaxFlow(int n = 0) { reset(n); }

    void reset(int n) {
        m_n = n;
        m_g.assign(static_cast<std::size_t>(n), {});
        m_used.assign(static_cast<std::size_t>(n), false);
    }

    int size() const { return m_n; }

    void add_edge(int u, int v, Cap cap) {
        Edge fwd{v, static_cast<int>(m_g[static_cast<std::size_t>(v)].size()), cap};
        Edge rev{u, static_cast<int>(m_g[static_cast<std::size_t>(u)].size()), 0};
        m_g[static_cast<std::size_t>(u)].push_back(fwd);
        m_g[static_cast<std::size_t>(v)].push_back(rev);
    }

    Cap max_flow(int s, int t) {
        Cap flow = 0;

        while (true) {
            std::fill(m_used.begin(), m_used.end(), false);
            Cap pushed = dfs(s, t, std::numeric_limits<Cap>::max());
            if (pushed == 0)
                break;
            flow += pushed;
        }

        return flow;
    }

    const std::vector<std::vector<Edge>> &graph() const { return m_g; }

  private:
    int m_n = 0;
    std::vector<std::vector<Edge>> m_g;
    std::vector<bool> m_used;

    Cap dfs(int v, int t, Cap f) {
        if (v == t)
            return f;
        m_used[static_cast<std::size_t>(v)] = true;

        for (auto &e : m_g[static_cast<std::size_t>(v)]) {
            if (e.cap <= 0)
                continue;
            if (m_used[static_cast<std::size_t>(e.to)])
                continue;

            Cap pushed = dfs(e.to, t, std::min(f, e.cap));
            if (pushed > 0) {
                e.cap -= pushed;
                m_g[static_cast<std::size_t>(e.to)][static_cast<std::size_t>(e.rev)].cap += pushed;
                return pushed;
            }
        }
        return 0;
    }
};
