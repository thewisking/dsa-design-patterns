#pragma once

class AvlTree;

class TreeNode {
    friend class AvlTree;

  private:
    int value{};
    int height{1};

    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode *parent = nullptr;

  public:
    TreeNode(int v) : value(v) {}
};
