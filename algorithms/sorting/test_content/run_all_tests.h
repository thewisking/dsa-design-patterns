// tests/run_all_tests.h
#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "run_fixed_tests.h"
#include "run_random_int_tests.h"
#include "run_stability_trials.h"
#include "test_case.h"

template <template <typename> class Sorter>
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
    run_fixed_tests<Sorter, int>(int_tests);

    std::cout << "\n--- FIXED STRING TESTS ---\n";
    run_fixed_tests<Sorter, std::string>(string_tests);

    std::cout << "\n--- RANDOM INT TESTS ---\n";
    run_random_int_tests<Sorter>(10, rng); // 10 random cases

    std::cout << "\n--- STABILITY CHECK ---\n";
    run_stability_trials<Sorter>(10, rng); // 10 stability trials
}
