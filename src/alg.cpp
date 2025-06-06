// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <algorithm>
#include <vector>

PMNode::~PMNode() {
    for (PMNode* child : children) {
        delete child;
    }
}
PMTree::PMTree(const std::vector<char>& in) : n(in.size()) {
    root = new PMNode('\0');
    std::vector<char> sorted_in = in;
    std::sort(sorted_in.begin(), sorted_in.end());
    buildTree(root, sorted_in);
}
PMTree::~PMTree() {
    delete root;
}
void PMTree::buildTree(PMNode* parent, const std::vector<char>& elements) {
    for (char c : elements) {
        PMNode* child = new PMNode(c);
        parent->children.push_back(child);
        std::vector<char> next_elements;
        for (char x : elements) {
            if (x != c) {
                next_elements.push_back(x);
            }
        }
        if (!next_elements.empty()) {
            buildTree(child, next_elements);
        }
    }
}
void getAllPermsHelper(PMNode* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
    current.push_back(node->value);
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (PMNode* child : node->children) {
            getAllPermsHelper(child, current, result);
        }
    }
    current.pop_back();
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    PMNode* root = tree.getRoot();
    if (root->children.empty()) {
        if (tree.size() == 0) {
            result.push_back({});
        }
        return result;
    }
    std::vector<char> current;
    for (PMNode* child : root->children) {
        getAllPermsHelper(child, current, result);
    }
    return result;
}
std::vector<char> getPerm1(PMTree& tree, unsigned long long num) {
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num < 1 || num > all.size()) {
        return {};
    }
    return all[num - 1];
}
std::vector<char> getPerm2Helper(PMNode* node, unsigned long long num,const std::vector<unsigned long long>& factorials) {
    int k = node->children.size();
    if (k == 0) {
        if (num == 1) {
            return {node->value};
        } else {
            return {};
        }
    }
    unsigned long long fact_child = factorials[k - 1];
    unsigned long long total_in_node = fact_child * k;
    if (num > total_in_node) {
        return {};
    }
    unsigned long long index = (num - 1) / fact_child;
    unsigned long long rem = (num - 1) % fact_child + 1;
    if (index >= node->children.size()) {
        return {};
    }
    PMNode* child_node = node->children[index];
    std::vector<char> suffix = getPerm2Helper(child_node, rem, factorials);
    if (suffix.empty()) {
        return {};
    }
    std::vector<char> result;
    result.push_back(node->value);
    result.insert(result.end(), suffix.begin(), suffix.end());
    return result;
}
std::vector<char> getPerm2(PMTree& tree, unsigned long long num) {
    int n = tree.size();
    if (n == 0) {
        if (num == 1) {
            return {};
        } else {
            return {};
        }
    }
    std::vector<unsigned long long> factorials(n + 1);
    factorials[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }
    if (num < 1 || num > factorials[n]) {
        return {};
    }
    PMNode* root = tree.getRoot();
    int k = root->children.size();
    if (k == 0) {
        return {};
    }
    unsigned long long fact_child = factorials[n - 1];
    unsigned long long index = (num - 1) / fact_child;
    unsigned long long rem = (num - 1) % fact_child + 1;
    if (index >= root->children.size()) {
        return {};
    }
    PMNode* child = root->children[index];
    return getPerm2Helper(child, rem, factorials);
}
