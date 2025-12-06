#include "red_black_tree.h"
#include <iostream>

int main() {
    RedBlackTree tree;

    int values[] = {10, 5, 15, 3, 7, 12, 18, 1, 4, 6, 8, 11, 13, 17, 20};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; ++i) {
        tree.insert(values[i]);
    }

    std::cout << "In-order traversal: ";
    tree.printInOrder();

    int tests[] = {7, 14, 1, 21};
    int tests_size = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < tests_size; ++i) {
        std::cout << "Contains " << tests[i] << ": "
                  << (tree.contains(tests[i]) ? "true" : "false") << std::endl;
    }

    return 0;
}
