// tests/run_single_test.h
#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Sorter is a template<class T> class with void sort(std::vector<T>&)
template <template <typename> class Sorter, typename T>
bool run_single_test(const std::string &label, const std::vector<T> &input) {
    std::vector<T> sorted = input;
    Sorter<T> sorter;
    sorter.sort(sorted);

    std::vector<T> expected = input;
    std::sort(expected.begin(), expected.end());

    bool ok = (sorted == expected);

    std::cout << label << " test: " << (ok ? "PASS" : "FAIL") << "\n";
    return ok;
}
