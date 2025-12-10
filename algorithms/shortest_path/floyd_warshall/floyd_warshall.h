#pragma once
#include <cstddef>
#include <limits>
#include <vector>

class FloydWarshall {
  public:
    using Weight = long long;
    using Matrix = std::vector<std::vector<Weight>>;

  private:
    Matrix m_dist;
    std::size_t m_n;
    bool m_has_negative_cycle;
    static constexpr Weight INF_VALUE = std::numeric_limits<Weight>::max() / 4;

  public:
    explicit FloydWarshall(const Matrix &adjacency)
        : m_dist(adjacency),
          m_n(adjacency.size()),
          m_has_negative_cycle(false) {
        run();
    }

    const Matrix &distances() const {
        return m_dist;
    }

    bool has_negative_cycle() const {
        return m_has_negative_cycle;
    }

    static Weight inf() {
        return INF_VALUE;
    }

  private:
    void run() {
        for (std::size_t i = 0; i < m_n; ++i) {
            if (m_dist[i][i] < 0) {
                m_has_negative_cycle = true;
                return;
            }
        }

        bool any_change = false;

        for (std::size_t k = 0; k < m_n; ++k) {
            for (std::size_t i = 0; i < m_n; ++i) {
                Weight dik = m_dist[i][k];
                if (dik == INF_VALUE)
                    continue;
                for (std::size_t j = 0; j < m_n; ++j) {
                    Weight dkj = m_dist[k][j];
                    if (dkj == INF_VALUE)
                        continue;
                    Weight through_k = dik + dkj;
                    if (through_k < m_dist[i][j]) {
                        m_dist[i][j] = through_k;
                        any_change = true;
                        if (i == j && m_dist[i][i] < 0) {
                            m_has_negative_cycle = true;
                            return;
                        }
                    }
                }
            }
        }

        if (!any_change) {
            m_has_negative_cycle = false;
            return;
        }

        m_has_negative_cycle = false;
    }
};
