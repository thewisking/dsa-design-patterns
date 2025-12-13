#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "kruskal.h"

static void line() { std::cout << "----------------------------------------\n"; }

static void show_i64(const std::string &name, std::int64_t expected, std::int64_t got) {
    std::cout << name << "\n";
    std::cout << "  expected: " << expected << "\n";
    std::cout << "  got     : " << got << "\n";
}

static void show_sz(const std::string &name, std::size_t expected, std::size_t got) {
    std::cout << name << "\n";
    std::cout << "  expected: " << expected << "\n";
    std::cout << "  got     : " << got << "\n";
}

static void show_bool(const std::string &name, bool expected, bool got) {
    std::cout << name << "\n";
    std::cout << "  expected: " << (expected ? "true" : "false") << "\n";
    std::cout << "  got     : " << (got ? "true" : "false") << "\n";
}

static void dump_result(const KruskalResult &r) {
    std::cout << "chosen edges:\n";
    if (r.chosen.empty()) {
        std::cout << "  (none)\n";
        return;
    }
    for (const auto &e : r.chosen) {
        std::cout << "  (" << e.u << ", " << e.v << ", " << e.w << ")\n";
    }
}

static void run_case(const std::string &title,
                     std::size_t n,
                     std::vector<KruskalEdge> edges,
                     std::int64_t exp_weight,
                     std::size_t exp_edges,
                     std::size_t exp_components,
                     bool exp_spanning) {
    line();
    std::cout << title << "\n";
    line();

    KruskalResult r = Kruskal::run(n, std::move(edges));

    show_i64("total_weight", exp_weight, r.total_weight);
    show_sz("chosen.size()", exp_edges, r.chosen.size());
    show_sz("components_after", exp_components, r.components_after);
    show_bool("is_spanning_tree", exp_spanning, r.is_spanning_tree);

    std::cout << "\n";
    dump_result(r);
    std::cout << "\n";
}

int main() {
    std::cout << "\nKRUSKAL TESTS\n\n";

    run_case("case 1: connected graph (n=4)",
             4,
             {
                 {0, 1, 1},
                 {1, 2, 2},
                 {2, 3, 3},
                 {0, 2, 4},
                 {1, 3, 5},
             },
             6,
             3,
             1,
             true);

    run_case("case 2: disconnected graph (n=4)",
             4,
             {
                 {0, 1, 1},
                 {2, 3, 2},
             },
             3,
             2,
             2,
             false);

    run_case("case 3: has an invalid edge (ignored) (n=3)",
             3,
             {
                 {0, 99, -100},
                 {0, 1, 5},
                 {1, 2, 7},
                 {0, 2, 20},
             },
             12,
             2,
             1,
             true);

    return 0;
}