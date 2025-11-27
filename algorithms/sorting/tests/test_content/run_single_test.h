// test_content/run_single_test.h
#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "terminal_colors.h"

// Sorter is a template<class T> class with void sort(std::vector<T>&)
template <template <typename> class Sorter, typename T>
bool run_single_test(const std::string &label, const std::vector<T> &input) {
    std::vector<T> sorted = input;
    Sorter<T> sorter;
    sorter.sort(sorted);

    std::vector<T> expected = input;
    std::sort(expected.begin(), expected.end());

    bool ok = (sorted == expected);

    const char *color = ok ? COLOR_GREEN : COLOR_RED;
    const char *text = ok ? "PASS" : "FAIL";

    std::cout << label << " test: "
              << color << text << COLOR_RESET
              << "\n";

    return ok;
}
