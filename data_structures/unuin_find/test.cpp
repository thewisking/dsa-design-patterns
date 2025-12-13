#include "union_find.h" // change to your actual header filename
#include <iostream>
#include <string>
#include <windows.h>

template <typename T>
void expect_eq(const std::string &label, const T &expected, const T &actual) {
    std::cout << label << "\n"
              << "  expected: " << expected << "\n"
              << "  actual:   " << actual << "\n"
              << (expected == actual ? "  ✅ PASS\n\n" : "  ❌ FAIL\n\n");
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== UnionFind / DSU basic tests ===\n\n";

    UnionFind uf(6); // {0},{1},{2},{3},{4},{5}

    expect_eq("Initial size()", std::size_t{6}, uf.size());
    expect_eq("Initial components()", std::size_t{6}, uf.components());
    expect_eq("Initial connected(0,1)", false, uf.connected(0, 1));
    expect_eq("Initial set_size(3)", std::size_t{1}, uf.set_size(3));

    // unite 0-1
    expect_eq("unite(0,1) returns", true, uf.unite(0, 1));
    expect_eq("connected(0,1)", true, uf.connected(0, 1));
    expect_eq("components() after unite(0,1)", std::size_t{5}, uf.components());
    expect_eq("set_size(0) after unite(0,1)", std::size_t{2}, uf.set_size(0));
    expect_eq("set_size(1) after unite(0,1)", std::size_t{2}, uf.set_size(1));

    // unite 1-2 (should merge {0,1} with {2})
    expect_eq("unite(1,2) returns", true, uf.unite(1, 2));
    expect_eq("connected(0,2)", true, uf.connected(0, 2));
    expect_eq("components() after unite(1,2)", std::size_t{4}, uf.components());
    expect_eq("set_size(2) after unite(1,2)", std::size_t{3}, uf.set_size(2));

    // unite 3-4
    expect_eq("unite(3,4) returns", true, uf.unite(3, 4));
    expect_eq("connected(3,4)", true, uf.connected(3, 4));
    expect_eq("components() after unite(3,4)", std::size_t{3}, uf.components());
    expect_eq("set_size(3) after unite(3,4)", std::size_t{2}, uf.set_size(3));

    // unite 4-5 (merge {3,4} with {5})
    expect_eq("unite(4,5) returns", true, uf.unite(4, 5));
    expect_eq("connected(3,5)", true, uf.connected(3, 5));
    expect_eq("components() after unite(4,5)", std::size_t{2}, uf.components());
    expect_eq("set_size(5) after unite(4,5)", std::size_t{3}, uf.set_size(5));

    // try to unite within same set (should be false, no component change)
    expect_eq("unite(0,2) returns (already connected)", false, uf.unite(0, 2));
    expect_eq("components() after unite(0,2) no-op", std::size_t{2}, uf.components());

    // merge the two big sets: {0,1,2} and {3,4,5}
    expect_eq("unite(2,3) returns", true, uf.unite(2, 3));
    expect_eq("connected(0,5)", true, uf.connected(0, 5));
    expect_eq("components() after unite(2,3)", std::size_t{1}, uf.components());
    expect_eq("set_size(0) after final merge", std::size_t{6}, uf.set_size(0));
    expect_eq("set_size(5) after final merge", std::size_t{6}, uf.set_size(5));

    std::cout << "=== Done ===\n";
    return 0;
}
