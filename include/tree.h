// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <cstdint>

struct PMNode {
    char value;
    std::vector<PMNode*> children;
    explicit PMNode(char v) : value(v) {}
    ~PMNode();
};
class PMTree {
 private:  // Fixed indentation
    PMNode* root;
    int n;
    void buildTree(PMNode* parent, const std::vector<char>& elements);
 public:  // Fixed indentation
    explicit PMTree(const std::vector<char>& in);
    ~PMTree();
    PMNode* getRoot() const { return root; }
    int size() const { return n; }
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int64_t num);
std::vector<char> getPerm2(PMTree& tree, int64_t num);

#endif  // INCLUDE_TREE_H_
