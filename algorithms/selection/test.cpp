#include "quick_select.h"
#include <iostream>
#include <vector>

int main() {
    QuickSelect<std::size_t> quick_select;
    std::vector<std::size_t> data = {6, 1, 2, 2, 2, 3};
    std::size_t k = 5;
    std::size_t *result = quick_select.select_kth_smallest(data, k);

    if (result) {
        std::cout << k << "rd smallest: " << *result << '\n';
    } else {
        std::cout << "invalid k\n";
    }

    result = quick_select.select_kth_largest(data, k);

    if (result) {
        std::cout << k << "rd largest: " << *result << '\n';
    } else {
        std::cout << "invalid k\n";
    }
}
