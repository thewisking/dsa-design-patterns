#include "trie.h"
#include <iostream>

int main() {
    Trie words;
    if (words.trie_insert("ALPHABET")) {
        std::cout << "worked \n";
    } else {
        std::cout << "didnt work \n";
    }

    if (words.search("ALPHABET")) {
        std::cout << "found \n";

    } else {
        std::cout << "not found \n";
    }
}
