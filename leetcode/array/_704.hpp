#pragma once

#include <vector>
#include "../src/common_utils.h"

namespace _704 {
    class Solution {
    public:
        int search(std::vector<int> &nums, int target) {
            int left = 0, right = nums.size() - 1; // 左闭右闭区间 [left, right]
            while (left <= right) { // left == right依然有效，所以<=
                int mid = (right - left) / 2 + left;
                if (nums[mid] > target) {
                    right = mid - 1;
                } else if (nums[mid] < target) {
                    left = mid + 1;
                } else {
                    return mid;
                }
            }
            return -1;
        }

        void test() {
            std::vector<int> nums1{-1, 0, 3, 5, 9, 12};
            int target1 = 9;
            std::cout << search(nums1, target1) << std::endl;
            int target2 = 2;
            std::cout << search(nums1, target2) << std::endl;
            std::vector<int> nums3{5};
            std::cout << search(nums3, -5) << std::endl;
            std::cout << "--------------------------------" << std::endl;
        }
    };
}
