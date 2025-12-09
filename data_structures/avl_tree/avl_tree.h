#pragma once

#include "tree_node.h"
#include <iostream>

class AvlTree {
  private:
    TreeNode *m_root{nullptr};

    int height(const TreeNode *node) const { return node ? node->height : 0; }
    int balance_factor(const TreeNode *node) const {
        if (!node)
            return 0;
        int left_balance = height(node->left);
        int right_balance = height(node->right);

        return (left_balance - right_balance);
    }
    void update_height(TreeNode *node) {
        if (!node)
            return;

        int right_height = height(node->right);
        int left_height = height(node->left);

        node->height = 1 + (right_height > left_height ? right_height : left_height);
    }

    void clear_subtree(TreeNode *node) {
        if (!node)
            return;

        clear_subtree(node->left);
        clear_subtree(node->right);
        delete node;
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

        TreeNode *parent = node->parent;
        right_child->parent = node->parent;
        if (!node->parent) {
            m_root = right_child;
        } else if (parent && parent->left == node) {
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
        TreeNode *parent = node->parent;
        if (!node->parent) {
            m_root = left_child;
        } else if (parent && parent->left == node) {
            node->parent->left = left_child;
        } else {
            node->parent->right = left_child;
        }

        left_child->right = node;
        node->parent = left_child;
    }

    TreeNode *bst_insert(int value) {
        if (!m_root) {
            m_root = new TreeNode(value);
            return m_root;
        }

        TreeNode *current = m_root;
        TreeNode *parent = nullptr;

        while (current) {
            parent = current;

            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            } else {
                return current;
            }
        }

        TreeNode *new_node = new TreeNode(value);
        new_node->parent = parent;

        if (value < parent->value) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        return new_node;
    }
    TreeNode *find_node(int value) const {
        TreeNode *current = m_root;

        while (current) {
            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            } else {
                return current;
            }
        }

        return nullptr;
    }
    TreeNode *bst_find_min(TreeNode *node) const {
        if (!node) {
            return nullptr;
        }

        while (node->left) {
            node = node->left;
        }
        return node;
    }
    void transplant(TreeNode *u, TreeNode *v) {
        if (!u)
            return;

        if (!u->parent)
            m_root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v)
            v->parent = u->parent;
    }
    TreeNode *erase_node(TreeNode *node) {
        if (!node)
            return nullptr;

        TreeNode *rebalance_from = node->parent;

        // Case 1: no left child
        if (!node->left) {
            TreeNode *child = node->right;
            transplant(node, child);
            if (child)
                rebalance_from = child;
            delete node;
            return rebalance_from;
        }

        // Case 2: no right child
        if (!node->right) {
            TreeNode *child = node->left;
            transplant(node, child);
            if (child)
                rebalance_from = child;
            delete node;
            return rebalance_from;
        }

        // Case 3: two children
        TreeNode *y = bst_find_min(node->right);

        if (y->parent != node) {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }

        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;

        rebalance_from = y;
        delete node;
        return rebalance_from;
    }

    void rebalance_upwards(TreeNode *node) {
        while (node) {
            update_height(node);
            int node_balance = balance_factor(node);

            if (node_balance > 1) {
                if (balance_factor(node->left) < 0)
                    rotate_left(node->left);
                rotate_right(node);
            } else if (node_balance < -1) {
                if (balance_factor(node->right) > 0)
                    rotate_right(node->right);
                rotate_left(node);
            }
            node = node->parent;
        }
    }

  public:
    AvlTree() = default;
    ~AvlTree() { clear(); }

    void print_inorder_subtree(const TreeNode *node) const {
        if (!node) {
            return;
        }
        print_inorder_subtree(node->left);
        std::cout << node->value << " ";
        print_inorder_subtree(node->right);
    }

    inline void print_inorder() const {
        print_inorder_subtree(m_root);
        std::cout << '\n';
    }

    void insert(int value) {
        TreeNode *node = bst_insert(value);
        if (!node) {
            return;
        }
        rebalance_upwards(node);
    }
    bool erase(int value) {
        TreeNode *z = find_node(value);
        if (!z) {
            return false;
        }

        TreeNode *rebalance_from = erase_node(z);
        if (rebalance_from) {
            rebalance_upwards(rebalance_from);
        }
        return true;
    }
    bool contains(int value) const {
        TreeNode *current = m_root;

        while (current) {
            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            } else {
                return true;
            }
        }

        return false;
    }

    bool empty() const { return m_root == nullptr; }
    void clear() {
        clear_subtree(m_root);
        m_root = nullptr;
    }
};
