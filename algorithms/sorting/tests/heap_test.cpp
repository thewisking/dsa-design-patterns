// main_bubble.cpp
#include <random>

#include "../heap_sort.cpp"
#include "../heap_sort.h"
#include "test_content/run_all_tests.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests<HeapSort>(rng);

    return 0;
}
