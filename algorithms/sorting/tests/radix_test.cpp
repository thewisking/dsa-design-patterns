// radix_test.cpp
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../radix_sort.cpp"
#include "../radix_sort.h"

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
    RadixSort<T> sorter;
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
    run_case<int>({7, 7, 7, 7});
    run_case<int>({0, 1, 2, 3, 4, 5});
    run_case<int>({5, 4, 3, 2, 1, 0});
    run_case<int>({15, 0, 255, 16, 31, 32, 1});
    run_case<int>({0xF, 0x10, 0x1F, 0x2A, 0xFF, 0x100, 0x101});

    std::mt19937 rng(123456);
    std::uniform_int_distribution<int> dist(0, 1'000'000);

    for (int t = 0; t < 100; ++t) {
        std::size_t n = 1 + (t % 200);
        std::vector<int> v;
        v.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            v.push_back(dist(rng));
        }
        run_case<int>(v);
    }

    std::cout << "All radix sort tests passed.\n";
    return 0;
}
