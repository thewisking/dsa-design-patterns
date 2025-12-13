#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

class UnionFind {
  public:
    using Index = std::size_t;

  private:
    std::vector<Index> m_size;
    std::vector<Index> m_parent;
    std::size_t m_components = 0;

    void check_index(Index x) const {
        if (x >= m_parent.size() || x >= m_size.size())
            throw std::out_of_range("UnionFind: index out of range");
    }

  public:
    UnionFind() = default;
    explicit UnionFind(std::size_t n) { reset(n); }

    void reset(std::size_t n) {
        m_parent.resize(n);
        m_size.assign(n, 1);
        m_components = n;

        for (Index i = 0; i < n; ++i) {
            m_parent[i] = i;
        }
    }

    std::size_t size() const { return m_parent.size(); }
    std::size_t components() const { return m_components; }

    Index find(Index x) {
        check_index(x);
        if (m_parent[x] == x)
            return x;
        m_parent[x] = find(m_parent[x]);
        return m_parent[x];
    }

    bool unite(Index a, Index b) {
        Index root_a = find(a);
        Index root_b = find(b);

        if (root_a == root_b)
            return false;

        if (m_size[root_a] < m_size[root_b]) {
            std::swap(root_a, root_b);
        }

        m_parent[root_b] = root_a;
        m_size[root_a] += m_size[root_b];
        --m_components;
        return true;
    }

    bool connected(Index a, Index b) { return find(a) == find(b); }
    std::size_t set_size(Index x) {
        check_index(x);
        return m_size[find(x)];
    }
};
