// tests/run_stability_trials.h
#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "stable_item.h"

template <template <typename> class Sorter>
bool run_stability_trials(std::size_t trials, std::mt19937 &rng) {
    std::uniform_int_distribution<int> size_dist(5, 50); // at least 5
    std::uniform_int_distribution<int> key_dist(0, 4);   // lots of duplicates

    bool all_stable = true;

    for (std::size_t t = 0; t < trials; ++t) {
        int size = size_dist(rng);

        std::vector<StableItem> data(size);
        for (int i = 0; i < size; ++i) {
            data[i].key = key_dist(rng);
            data[i].original_index = i;
        }

        std::vector<StableItem> expected = data;
        std::stable_sort(expected.begin(), expected.end(), StableItemKeyLess{});

        std::vector<StableItem> sorted = data;
        Sorter<StableItem> sorter;
        sorter.sort(sorted);

        bool stable_here = (sorted == expected);
        if (!stable_here) {
            all_stable = false;
        }
    }

    std::cout << "Stability test ("
              << trials
              << " random trials vs std::stable_sort): "
              << (all_stable ? "PASS" : "FAIL")
              << "\n";

    return all_stable;
}
