#pragma once

class RedBlackTree;

enum Colour {
    RED,
    BLACK,
};

class TreeNode {
    friend class RedBlackTree;

  private:
    int value;

    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode *parent = nullptr;

    Colour m_colour = RED;

  public:
    TreeNode(int v) : value(v) {}
};
