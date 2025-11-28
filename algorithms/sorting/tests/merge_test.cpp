// main_bubble.cpp
#include <random>

#include "../merge_sort.cpp"
#include "../merge_sort.h"
#include "test_content/run_all_tests.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests<MergeSort>(rng);

    return 0;
}
