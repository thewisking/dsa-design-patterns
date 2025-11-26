// test_bubble_sort.cpp

#include "bubble_sort.cpp"
#include "bubble_sort.h"
#include <iostream>
#include <string>
#include <vector>

// Small helper to hold a test case
template <typename T>
struct TestCase {
    std::string label;
    std::vector<T> data;
};

template <typename T>
void print_vector(const std::vector<T> &v, const std::string &prefix) {
    std::cout << prefix << ": [ ";
    for (const auto &x : v) {
        std::cout << x << " ";
    }
    std::cout << "]\n";
}

template <typename T>
void run_tests(const std::vector<TestCase<T>> &tests) {
    BubbleSort<T> sorter;

    for (const auto &test : tests) {
        std::cout << "=== " << test.label << " ===\n";

        // Before
        print_vector(test.data, "Before");

        // Make a copy to sort so we keep the original if needed
        std::vector<T> sorted = test.data;
        sorter.sort(sorted);

        // After
        print_vector(sorted, "After");

        std::cout << "\n";
    }
}

int main() {
    // Int test cases
    std::vector<TestCase<int>> int_tests = {
        {"Basic ints", {5, 3, 8, 1, 2}},
        {"Already sorted", {1, 2, 3, 4, 5}},
        {"Reverse order", {5, 4, 3, 2, 1}},
        {"With duplicates", {4, 2, 2, 4, 1, 1}},
        {"Single element", {42}},
        {"Empty vector", {}}};

    // String test cases
    std::vector<TestCase<std::string>> string_tests = {
        {"Basic strings", {"orange", "apple", "banana", "apple"}},
        {"Already sorted", {"apple", "banana", "orange"}},
        {"Reverse order", {"zulu", "echo", "alpha"}}};

    std::cout << "--- INT TESTS ---\n\n";
    run_tests(int_tests);

    std::cout << "--- STRING TESTS ---\n\n";
    run_tests(string_tests);

    return 0;
}
