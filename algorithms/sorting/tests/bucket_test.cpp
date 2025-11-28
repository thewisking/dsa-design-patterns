// bucket_test.cpp
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../bucket_sort.cpp"
#include "../bucket_sort.h"

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
    BucketSort<T> sorter;

    std::vector<T> data = input;
    std::vector<T> expect = input;

    sorter.sort(data);
    std::sort(expect.begin(), expect.end());

    assert(data.size() == expect.size());
    assert(data == expect);
    assert(is_sorted(data));
}

int main() {
    run_case<int>({});
    run_case<int>({5});
    run_case<int>({3, 1, 2});
    run_case<int>({4, 4, 4, 4});
    run_case<int>({0, 1, 2, 3, 4});
    run_case<int>({5, 4, 3, 2, 1});
    run_case<int>({10, 0, 10, 5, 2, 8, 3});

    std::mt19937 rng(123456);
    std::uniform_int_distribution<int> dist(0, 100);

    for (int t = 0; t < 50; ++t) {
        std::size_t n = 1 + (t % 100);

        std::vector<int> v;
        v.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            v.push_back(dist(rng));
        }
        run_case<int>(v);
    }

    std::cout << "All bucket sort tests passed.\n";
    return 0;
}
