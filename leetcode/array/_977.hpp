#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include "../src/common_utils.h"

namespace _977 {
    class Solution {
    public:
        std::vector<int> sortedSquares(std::vector<int> &nums) {
            // 复杂度O(n)解法
            int n = nums.size();
            std::vector<int> res(n);
            int pos = n - 1;
            for (int i = 0, j = n - 1; pos >= 0 && i <= j;) {
                // 输入数组已排好序，考虑双指针，将绝对值大的数的平方放在新数组末尾
                if (nums[i] * nums[i] > nums[j] * nums[j]) {
                    res[pos] = nums[i] * nums[i];
                    i++;
                } else {
                    res[pos] = nums[j] * nums[j];
                    j--;
                }
                pos--;
            }
            return res;
        }

        void test() {
            std::vector<int> v{-4, -1, 0, 3, 10};
            PrintVec(sortedSquares(v));
            std::cout << "--------------------------------" << std::endl;

            std::vector<int> v1{-7, -3, 2, 3, 11};
            PrintVec(sortedSquares(v1));
            std::cout << "--------------------------------" << std::endl;
        }
    };
}