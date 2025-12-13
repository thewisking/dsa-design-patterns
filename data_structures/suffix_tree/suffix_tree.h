#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class SuffixTreeSimple {
  public:
    SuffixTreeSimple() = default;
    explicit SuffixTreeSimple(std::string_view s, char terminal = '$') { build(s, terminal); }

    void build(std::string_view s, char terminal = '$') {
        if (s.find(terminal) != std::string_view::npos) {
            throw std::invalid_argument("terminal character appears in input");
        }
        clear();
        m_text.assign(s);
        m_text.push_back(terminal);
        m_nodes.push_back(Node{});

        for (std::size_t i{}; i < m_text.size(); i++) {
            insert_suffix(i);
        }
    }
    void clear() {
        m_text.clear();
        m_nodes.clear();
    }

    bool contains(std::string_view pattern) const {
        if (pattern.empty())
            return true;

        int node = 0;
        std::size_t p = 0;

        while (p < pattern.size()) {
            auto it = m_nodes[node].next.find(pattern[p]);
            if (it == m_nodes[node].next.end())
                return false;

            const Edge &e = it->second;

            std::size_t j = 0;
            while (e.start + j < e.end && p < pattern.size()) {
                if (m_text[e.start + j] != pattern[p])
                    return false;
                ++j;
                ++p;
            }

            if (p == pattern.size())
                return true;
            node = e.to;
        }
        return true;
    }

    std::vector<std::size_t> occurrences(std::string_view pattern) const {
        std::vector<std::size_t> out;

        if (m_text.empty())
            return out;

        const std::size_t original_len = m_text.size() - 1;

        if (pattern.empty()) {
            out.reserve(original_len);
            for (std::size_t i = 0; i < original_len; ++i)
                out.push_back(i);
            return out;
        }

        int node = 0;
        std::size_t p = 0;

        while (p < pattern.size()) {
            auto it = m_nodes[node].next.find(pattern[p]);
            if (it == m_nodes[node].next.end())
                return {};

            const Edge &e = it->second;

            std::size_t j = 0;
            while (e.start + j < e.end && p < pattern.size()) {
                if (m_text[e.start + j] != pattern[p])
                    return {};
                ++j;
                ++p;
            }

            if (p == pattern.size()) {
                collect_leaves(e.to, out);
                break;
            }

            node = e.to;
        }

        out.erase(std::remove_if(out.begin(), out.end(),
                                 [&](std::size_t x) { return x >= original_len; }),
                  out.end());

        std::sort(out.begin(), out.end());
        return out;
    }

    std::string_view text() const { return m_text; }
    std::size_t node_count() const { return m_nodes.size(); }

  private:
    struct Edge {
        int to = -1;
        std::size_t start = 0;
        std::size_t end = 0;
    };

    struct Node {
        std::unordered_map<char, Edge> next;
        std::size_t suffix_start = npos;
    };

    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    std::string m_text;
    std::vector<Node> m_nodes;

    int new_node() {
        m_nodes.push_back(Node{});
        return static_cast<int>(m_nodes.size() - 1);
    }

    // Insert suffix starting at position i (naive O(n) per suffix).
    void insert_suffix(std::size_t i) {
        int node = 0;
        std::size_t pos = i;

        while (pos < m_text.size()) {
            char c = m_text[pos];

            auto it = m_nodes[node].next.find(c);
            if (it == m_nodes[node].next.end()) {
                int leaf = new_node();
                m_nodes[leaf].suffix_start = i;

                m_nodes[node].next.emplace(c, Edge{leaf, pos, m_text.size()});
                return;
            }

            Edge &e = it->second;

            std::size_t k = 0;
            while (e.start + k < e.end &&
                   pos + k < m_text.size() &&
                   m_text[e.start + k] == m_text[pos + k]) {
                ++k;
            }

            if (e.start + k == e.end) {
                node = e.to;
                pos += k;
                continue;
            }

            const int old_child = e.to;
            const std::size_t old_start = e.start;
            const std::size_t old_end = e.end;

            int mid = new_node();

            e.to = mid;
            e.end = old_start + k;

            m_nodes[mid].next.emplace(
                m_text[old_start + k],
                Edge{old_child, old_start + k, old_end});

            int leaf = new_node();
            m_nodes[leaf].suffix_start = i;

            m_nodes[mid].next.emplace(
                m_text[pos + k],
                Edge{leaf, pos + k, m_text.size()});

            return;
        }
    }

    int follow(std::string_view pattern) const;

    void collect_leaves(int node, std::vector<std::size_t> &out) const {
        if (m_nodes[node].suffix_start != npos) {
            out.push_back(m_nodes[node].suffix_start);
            return;
        }
        for (const auto &kv : m_nodes[node].next) {
            collect_leaves(kv.second.to, out);
        }
    }
};
