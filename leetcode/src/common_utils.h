#pragma once

#include <vector>
#include <iostream>

template<typename T>
void PrintVec(const std::vector<T> &vec) {
    for (const auto &item : vec) {
        std::cout << item << "," << std::endl;
    }
}

template<typename T>
void PrintVec(const std::vector<std::vector<T>> &vecs) {
    for (const auto &vec : vecs) {
        for (const auto &item : vec) {
            std::cout << item << ",";
        }
        std::cout << "\n";
    }
}