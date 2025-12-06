#include "binary_search_tree.h"
#include <iostream>

int main() {
    BinarySearchTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "In-order print (should be sorted): ";
    tree.printInOrder();

    int toFind1 = 4;
    int toFind2 = 10;

    if (tree.contains(toFind1)) {
        std::cout << "Tree contains " << toFind1 << "\n";
    } else {
        std::cout << "Tree does NOT contain " << toFind1 << "\n";
    }

    if (tree.contains(toFind2)) {
        std::cout << "Tree contains " << toFind2 << "\n";
    } else {
        std::cout << "Tree does NOT contain " << toFind2 << "\n";
    }

    return 0;
}
