// main_bubble.cpp
#include <random>

#include "../bogo_sort.cpp"
#include "../bogo_sort.h"
#include "test_content/run_all_tests.h"

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    run_all_tests<BogoSort>(rng);

    return 0;
}
