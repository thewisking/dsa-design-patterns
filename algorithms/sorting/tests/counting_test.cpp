// counting_test.cpp
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../counting_sort.cpp"
#include "../counting_sort.h"

template <typename T>
bool is_sorted(const std::vector<T> &v) {
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] < v[i - 1])
            return false;
    }
    return true;
}

template <typename T>
void run_case(const std::vector<T> &input) {
    CountingSort<T> sorter;

    std::vector<T> data = input;
    std::vector<T> expected = input;

    sorter.sort(data);
    std::sort(expected.begin(), expected.end());

    assert(data.size() == expected.size());
    assert(data == expected);
    assert(is_sorted(data));
}

int main() {
    run_case<int>({});
    run_case<int>({5});
    run_case<int>({3, 1, 2});
    run_case<int>({2, 2, 2, 2});
    run_case<int>({5, 4, 3, 2, 1});
    run_case<int>({-3, -1, -2, -5, 0, 4, 4});
    run_case<int>({0, 100, 50, 100, 0, 50});

    std::mt19937 rng(123456);
    std::uniform_int_distribution<int> dist(-50, 50);

    for (int t = 0; t < 50; ++t) {
        std::size_t n = 1 + (t % 100);

        std::vector<int> v;
        v.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            v.push_back(dist(rng));
        }
        run_case<int>(v);
    }

    std::cout << "All counting sort tests passed.\n";
    return 0;
}
