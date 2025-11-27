// main_bubble.cpp
#include <random>

#include "../insertion_sort.cpp"
#include "../insertion_sort.h"
#include "test_content/run_all_tests.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests<InsertionSort>(rng);

    return 0;
}
