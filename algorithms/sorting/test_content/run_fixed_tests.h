// tests/run_fixed_tests.h
#pragma once

#include <vector>

#include "run_single_test.h"
#include "test_case.h"

template <template <typename> class Sorter, typename T>
void run_fixed_tests(const std::vector<TestCase<T>> &tests) {
    for (const auto &test : tests) {
        run_single_test<Sorter, T>(test.label, test.data);
    }
}
