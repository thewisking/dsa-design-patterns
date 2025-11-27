// test_sort.cpp

#include "bubble_sort.cpp"
#include "bubble_sort.h"

#include "selection_sort.cpp"
#include "selection_sort.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <typename T>
using CurrentSorter = SelectionSort<T>;

template <typename T>
struct TestCase {
    std::string label;
    std::vector<T> data;
};

template <typename T>
bool run_single_test(const std::string &label, const std::vector<T> &input) {
    std::vector<T> sorted = input;
    CurrentSorter<T> sorter;
    sorter.sort(sorted);

    std::vector<T> expected = input;
    std::sort(expected.begin(), expected.end());

    bool ok = (sorted == expected);

    std::cout << label << " test: " << (ok ? "PASS" : "FAIL") << "\n";
    return ok;
}

template <typename T>
void run_fixed_tests(const std::vector<TestCase<T>> &tests) {
    for (const auto &test : tests) {
        run_single_test<T>(test.label, test.data);
    }
}

// Randomised int tests compared against std::sort
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
        run_single_test<int>(label, data);
    }
}

// =======================
// STABILITY TEST
// =======================

struct StableItem {
    int key;            // value used for sorting
    int original_index; // track original position
};

// comparator by key only (used by std::stable_sort)
struct StableItemKeyLess {
    bool operator()(const StableItem &a, const StableItem &b) const {
        return a.key < b.key;
    }
};

// define equality so std::vector<StableItem>::operator== works
inline bool operator==(const StableItem &a, const StableItem &b) {
    return a.key == b.key && a.original_index == b.original_index;
}

// operator< / > so your sort can compare StableItem
inline bool operator<(const StableItem &a, const StableItem &b) {
    return a.key < b.key;
}

inline bool operator>(const StableItem &a, const StableItem &b) {
    return a.key > b.key;
}

// Run several random stability trials and compare to std::stable_sort
bool run_stability_trials(std::size_t trials, std::mt19937 &rng) {
    std::uniform_int_distribution<int> size_dist(5, 50); // always at least 5
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
        CurrentSorter<StableItem> sorter;
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

// =======================
// TOP-LEVEL TEST RUNNER
// =======================

void run_all_tests(std::mt19937 &rng) {
    // Int fixed test cases
    std::vector<TestCase<int>> int_tests = {
        {"Basic ints", {5, 3, 8, 1, 2}},
        {"Already sorted", {1, 2, 3, 4, 5}},
        {"Reverse order", {5, 4, 3, 2, 1}},
        {"With duplicates", {4, 2, 2, 4, 1, 1}},
        {"Single element", {42}},
        {"Empty vector", {}},
        {"All equal", {7, 7, 7, 7, 7}},
        {"Negatives", {-5, -1, -3, -2, -4}},
        {"Mixed sign", {-10, 0, 5, -3, 8, 0, -1}}};

    // String fixed test cases
    std::vector<TestCase<std::string>> string_tests = {
        {"Basic strings", {"orange", "apple", "banana", "apple"}},
        {"Already sorted", {"apple", "banana", "orange"}},
        {"Reverse order", {"zulu", "echo", "alpha"}},
        {"All equal strings", {"x", "x", "x", "x"}}};

    std::cout << "--- FIXED INT TESTS ---\n";
    run_fixed_tests(int_tests);

    std::cout << "\n--- FIXED STRING TESTS ---\n";
    run_fixed_tests(string_tests);

    std::cout << "\n--- RANDOM INT TESTS ---\n";
    run_random_int_tests(10, rng); // 10 random test cases

    std::cout << "\n--- STABILITY CHECK ---\n";
    run_stability_trials(10, rng); // 10 random stability trials
}

// =======================
// MINIMAL MAIN
// =======================

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests(rng);

    return 0;
}
