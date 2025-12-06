#pragma once

#include "tree_node.h"
#include <iostream>

class RedBlackTree {
  private:
    TreeNode *m_root;

    bool is_left_child(TreeNode *node, TreeNode *parent) {
        return parent && parent->left == node;
    }

    void rotate_left(TreeNode *node) {
        if (!node || !node->right) {
            return;
        }

        TreeNode *right_child = node->right;

        node->right = right_child->left;
        if (right_child->left) {
            right_child->left->parent = node;
        }

        right_child->parent = node->parent;
        if (!node->parent) {
            m_root = right_child;
        } else if (is_left_child(node, node->parent)) {
            node->parent->left = right_child;
        } else {
            node->parent->right = right_child;
        }

        right_child->left = node;
        node->parent = right_child;
    }

    void rotate_right(TreeNode *node) {
        if (!node || !node->left) {
            return;
        }

        TreeNode *left_child = node->left;

        node->left = left_child->right;
        if (left_child->right) {
            left_child->right->parent = node;
        }

        left_child->parent = node->parent;
        if (!node->parent) {
            m_root = left_child;
        } else if (is_left_child(node, node->parent)) {
            node->parent->left = left_child;
        } else {
            node->parent->right = left_child;
        }

        left_child->right = node;
        node->parent = left_child;
    }

    void insert_impl(TreeNode *&node, TreeNode *parent, int value) {
        if (node == nullptr) {
            node = new TreeNode(value);
            node->parent = parent;
            insert_fix(node);
            return;
        }

        if (value < node->value) {
            insert_impl(node->left, node, value);
        } else if (value > node->value) {
            insert_impl(node->right, node, value);
        }
    }

    void insert_fix(TreeNode *node) {
        if (!node) {
            return;
        }

        if (node == m_root) {
            node->m_colour = BLACK;
            return;
        }

        TreeNode *parent = node->parent;
        if (!parent) {
            return;
        }

        if (parent->m_colour == BLACK) {
            return;
        }

        TreeNode *uncle = get_uncle(node);
        if (uncle && uncle->m_colour == RED) {
            fix_red_uncle(parent, uncle);
            return;
        }

        fix_black_uncle(node, parent);
    }

    TreeNode *get_uncle(TreeNode *node) {
        TreeNode *parent = node ? node->parent : nullptr;
        if (!parent) {
            return nullptr;
        }

        TreeNode *grand_parent = parent->parent;
        if (!grand_parent) {
            return nullptr;
        }

        if (grand_parent->left == parent) {
            return grand_parent->right;
        } else {
            return grand_parent->left;
        }
    }

    void fix_black_uncle(TreeNode *node, TreeNode *parent) {
        TreeNode *grand_parent = parent ? parent->parent : nullptr;
        if (!grand_parent) {
            return;
        }

        if (is_left_child(parent, grand_parent)) {
            if (!is_left_child(node, parent)) {
                rotate_left(parent);
                node = parent;
                parent = node->parent;
            }

            parent->m_colour = BLACK;
            grand_parent->m_colour = RED;
            rotate_right(grand_parent);
        } else {
            if (is_left_child(node, parent)) {
                rotate_right(parent);
                node = parent;
                parent = node->parent;
            }

            parent->m_colour = BLACK;
            grand_parent->m_colour = RED;
            rotate_left(grand_parent);
        }
    }

    void fix_red_uncle(TreeNode *parent, TreeNode *uncle) {
        TreeNode *grand_parent = parent ? parent->parent : nullptr;

        if (!grand_parent) {
            parent->m_colour = BLACK;
            return;
        }

        parent->m_colour = BLACK;
        uncle->m_colour = BLACK;
        grand_parent->m_colour = RED;

        insert_fix(grand_parent);
    }

    bool contains_impl(TreeNode *node, int value) const {
        if (!node) {
            return false;
        }

        if (value < node->value) {
            return contains_impl(node->left, value);
        } else if (value > node->value) {
            return contains_impl(node->right, value);
        } else {
            return true;
        }
    }

    void printInOrder_impl(TreeNode *node) const {
        if (!node) {
            return;
        }

        printInOrder_impl(node->left);
        std::cout << node->value << " ";
        printInOrder_impl(node->right);
    }

    void destroy(TreeNode *node) {
        if (!node) {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

  public:
    RedBlackTree() : m_root(nullptr) {}

    ~RedBlackTree() {
        destroy(m_root);
        m_root = nullptr;
    }

    void insert(int value) {
        insert_impl(m_root, nullptr, value);
    }

    bool contains(int value) const {
        return contains_impl(m_root, value);
    }

    void printInOrder() const {
        printInOrder_impl(m_root);
        std::cout << std::endl;
    }
};
