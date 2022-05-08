#pragma once

#include <vector>

#include "../src/common_utils.h"

namespace _77 {
    class Solution {
    public:
        std::vector<std::vector<int>> combine(int n, int k) {
            std::vector<int> path;
            backTracking2(path, n, k, 1);
            return res;
        }

        void backTracking(std::vector<int> &path, int n, int k, int start) {
            if (path.size() == k) {
                res.emplace_back(path);
                return;
            }
            for (int i = start; i <= n; ++i) {
                path.emplace_back(i);
                backTracking(path, n, k, i + 1);
                path.pop_back();
            }
        }

        void backTracking2(std::vector<int> &path, int n, int k, int start) {
            if (path.size() == k) {
                res.emplace_back(path);
                return;
            }
            // 剪枝方法
            // a.还需要元素个数：k - path.size(); b.至多可起始start的遍历位置：n - (k - path.size()) + 1
            for (int i = start; i <= n - (k - path.size()) + 1; ++i) {
                path.emplace_back(i); // 处理节点
                backTracking2(path, n, k, i + 1); // 递归
                path.pop_back(); // 回溯，撤销处理的节点
            }
        }

        void test() {
            int n = 4, k = 2;
            res = combine(n, k);
            PrintVec(res);
        }

    private:
        std::vector<std::vector<int>> res;
    };
}
