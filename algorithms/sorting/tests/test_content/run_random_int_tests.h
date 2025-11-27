// tests/run_random_int_tests.h
#pragma once

#include <cstddef>
#include <random>
#include <string>
#include <vector>

#include "run_single_test.h"

template <template <typename> class Sorter>
void run_random_int_tests(std::size_t num_tests, std::mt19937 &rng) {
    std::uniform_int_distribution<int> value_dist(-100, 100);
    std::uniform_int_distribution<int> size_dist(0, 100); // sizes up to 100

    for (std::size_t i = 0; i < num_tests; ++i) {
        int size = size_dist(rng);
        std::vector<int> data;
        data.reserve(size);

        for (int j = 0; j < size; ++j) {
            data.push_back(value_dist(rng));
        }

        std::string label = "Random int #" + std::to_string(i + 1);
        run_single_test<Sorter, int>(label, data);
    }
}
