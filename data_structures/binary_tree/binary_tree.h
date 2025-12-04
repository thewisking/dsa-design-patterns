#pragma once

#include "tree_node.h"
#include <iostream>

class BinaryTree {
  private:
    TreeNode *m_root;

    void insert_impl(TreeNode *&node, int value) {
        if (node == nullptr) {
            node = new TreeNode(value);
            return;
        }

        if (value < node->value) {
            insert_impl(node->left, value);
        } else if (value > node->value) {
            insert_impl(node->right, value);
        }
    }

    bool contains_impl(TreeNode *node, int value) const {
        if (node == nullptr) {
            return false;
        }

        if (value == node->value) {
            return true;
        } else if (value < node->value) {
            return contains_impl(node->left, value);
        } else {
            return contains_impl(node->right, value);
        }
    }

    void print_inorder_impl(TreeNode *node) const {
        if (node == nullptr) {
            return;
        }

        print_inorder_impl(node->left);
        std::cout << node->value << " ";
        print_inorder_impl(node->right);
    }

    void clear(TreeNode *node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

  public:
    BinaryTree() : m_root(nullptr) {}

    ~BinaryTree() { clear(m_root); }

    void insert(int value) { insert_impl(m_root, value); }

    bool contains(int value) const { return contains_impl(m_root, value); }

    void printInOrder() const {
        print_inorder_impl(m_root);
        std::cout << "\n";
    }
};