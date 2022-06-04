#pragma once

#include <vector>
#include "../src/common_utils.h"

namespace _209 {
    class Solution {
    public:
        int minSubArrayLen(int target, std::vector<int> &nums) {
            int minLen = INT_MAX;
            int left = 0, sum = 0;
            for (int right = 0; right < nums.size(); ++right) {
                sum += nums[right];
                // 滑动窗口，每次更新left(起始位置)，并不断判断子序列是否符合条件
                while (sum >= target) {
                    minLen = std::min(minLen, right - left + 1);
                    sum -= nums[left++];
                }
            }
            return minLen == INT_MAX ? 0 : minLen;
#if 0
            if (nums.empty()) {
                return 0;
            }
            int left = 0, right = 1, minLen = INT_MAX;
            int sum = nums[left];
            while (left <= right) {
                if (sum >= target) {
                    minLen = std::min(minLen, right - left);
                    sum -= nums[left]; // 去掉最左边元素
                    left++;
                    continue;
                }
                if (right <= nums.size() - 1) { // right到头了
                    sum += nums[right];
                    ++right;
                } else {
                    ++left;
                }
            }
            return minLen == INT_MAX ? 0 : minLen;
#endif
        }

        void test() {
            std::vector<int> nums1{2, 3, 1, 2, 4, 3};
            std::cout << minSubArrayLen(7, nums1) << std::endl;

            std::vector<int> nums2{1, 4, 4};
            std::cout << minSubArrayLen(1, nums2) << std::endl;

            std::vector<int> nums3{1, 1, 1, 1, 1, 1, 1, 1};
            std::cout << minSubArrayLen(11, nums3) << std::endl;
        }
    };
}