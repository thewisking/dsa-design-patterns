// main_bubble.cpp
#include <random>

#include "../bubble_sort.cpp"
#include "../bubble_sort.h"
#include "test_content/run_all_tests.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests<BubbleSort>(rng);

    return 0;
}
