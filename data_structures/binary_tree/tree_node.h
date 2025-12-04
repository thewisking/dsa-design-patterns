#pragma once

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v)
        : value(v), left(nullptr), right(nullptr) {}
};