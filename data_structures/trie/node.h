#pragma once
#include <array>
#include <cctype>
#include <cstddef>
#include <stdexcept>

class Trie;
constexpr std::size_t ALPHABET_SIZE = 'z' - 'a' + 1; // could do 26, but change it here if u want smt else

class Node {
  private:
    friend class Trie;

    bool end_of_word = false;
    std::array<Node *, ALPHABET_SIZE> children{};

  public:
    Node() { children.fill(nullptr); }

    // if u change the values u can just change this
    static std::size_t index_from_char(char c) {

        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c + ('a' - 'A'));
        }
        if (c < 'a' || c > 'z') {
            throw std::invalid_argument("Unsupported character in trie");
        }
        return static_cast<std::size_t>(c - 'a');
    }
};