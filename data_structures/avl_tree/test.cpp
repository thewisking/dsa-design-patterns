#include "avl_tree.h"
#include <iostream>

int main() {
    AvlTree tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(50);

    std::cout << "Inorder after inserts (should be sorted): ";
    tree.print_inorder();

    std::cout << "\nErasing 20...\n";
    tree.erase(20);
    std::cout << "Inorder after erasing 20: ";
    tree.print_inorder();

    std::cout << "\nErasing 30...\n";
    tree.erase(30);
    std::cout << "Inorder after erasing 30: ";
    tree.print_inorder();

    return 0;
}
