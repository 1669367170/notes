#pragma once

#include <vector>
#include "../src/common_utils.h"

namespace _59 {
    class Solution {
    public:
        std::vector<std::vector<int>> generateMatrix(int n) {
            // TODO 跟二分法一样要坚持循环不变原则！ 比如左闭右开
            std::vector<std::vector<int>> ret(n, std::vector<int>(n, 0));
            int left = 0, right = n - 1, up = 0, down = n - 1, num = 1;
            while (num <= n * n) {
                // 左->右
                for (int i = left; i <= right; ++i) { ret[up][i] = num++; }
                ++up;
                // 上->下
                for (int j = up; j <= down; ++j) { ret[j][right] = num++; }
                --right;
                // 右->左
                for (int k = right; k >= left; --k) { ret[down][k] = num++; }
                --down;
                // 下->上
                for (int p = down; p >= up; --p) { ret[p][left] = num++; }
                ++left;
            }
            return ret;
#if 0
            // 自己的初版解法
            std::vector<std::vector<int>> res;
            res.resize(n, std::vector<int>(n, 0));
            int leftIdx = 0, rightIdx = n - 1, topIdx = 0, bottomIdx = n - 1;
            int row = 0, col = 0;
            // 下一个元素顺序方向，左右上下
            bool left = false, right = true, up = false, down = false;
            for (int i = 1; i <= n * n; ++i) {
                if (right) {
                    res[row][col++] = i;
                    if (col == rightIdx) {
                        right = false;
                        down = true;
                        topIdx += 1;
                    }
                } else if (down) {
                    res[row++][col] = i;
                    if (row == bottomIdx) {
                        down = false;
                        left = true;
                        rightIdx -= 1;
                    }
                } else if (left) {
                    res[row][col--] = i;
                    if (col == leftIdx) {
                        left = false;
                        up = true;
                        bottomIdx -= 1;
                    }
                } else if (up) {
                    res[row--][col] = i;
                    if (row == topIdx) {
                        up = false;
                        right = true;
                        leftIdx += 1;
                    }
                }
            }
            return res;
#endif
        }

        void test() {
            auto res = generateMatrix(3);
            PrintVec(res);

            auto res1 = generateMatrix(5);
            PrintVec(res1);
        }
    };
}