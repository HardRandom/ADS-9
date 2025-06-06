// Copyright 2022 NNTU-CS
#include "tree.h"
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdint>

int main() {
    std::vector<char> input = {'1','2','3','4','5','6'};
    PMTree tree(input);
    auto start = std::chrono::high_resolution_clock::now();
    auto perms = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "getAllPerms time: "
              << std::chrono::duration<double, std::milli>(end - start).count() 
              << " ms\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int64_t> dist(1, perms.size());
    int64_t random_num = dist(gen);
    start = std::chrono::high_resolution_clock::now();
    auto perm1 = getPerm1(tree, random_num);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "getPerm1 time (perm #" << random_num << "): "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";
    start = std::chrono::high_resolution_clock::now();
    auto perm2 = getPerm2(tree, random_num);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "getPerm2 time (perm #" << random_num << "): "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";
    return 0;
}
