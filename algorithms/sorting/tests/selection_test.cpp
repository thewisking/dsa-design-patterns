// main_bubble.cpp
#include <random>

#include "../selection_sort.cpp"
#include "../selection_sort.h"
#include "test_content/run_all_tests.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests<SelectionSort>(rng);

    return 0;
}
