// tests/test_case.h
#pragma once

#include <string>
#include <vector>

template <typename T>
struct TestCase {
    std::string label;
    std::vector<T> data;
};
