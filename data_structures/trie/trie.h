#pragma once
#include "node.h"
#include <stdexcept>
#include <string>

class Trie {
  private:
    Node *m_root;

    void destroy(Node *to_kill) {
        if (!to_kill) {
            return;
        }
        for (Node *child : to_kill->children) {
            destroy(child);
        }
        delete to_kill;
    }

  public:
    Trie() { m_root = new Node; }

    bool trie_insert(const std::string &word) {
        Node *current = m_root;

        try { // there's probably a better way to do this i cba
            for (char letter : word) {

                std::size_t index = Node::index_from_char(letter);

                if (!current->children[index]) {
                    current->children[index] = new Node;
                }

                current = current->children[index];
            }
        } catch (const std::invalid_argument &e) {
            return false;
        }

        current->end_of_word = true;
        return true;
    }

    bool starts_with(const std::string &word) {
        Node *current = m_root;

        for (char letter : word) {

            std::size_t index = Node::index_from_char(letter);

            if (!current->children[index]) {
                return false;
            }

            current = current->children[index];
        }
        return true;
    }

    bool search(const std::string &word) {
        Node *current = m_root;

        for (char letter : word) {

            std::size_t index = Node::index_from_char(letter);

            if (!current->children[index]) {
                return false;
            }

            current = current->children[index];
        }
        return current->end_of_word;
    }

    ~Trie() { destroy(m_root); }
};
