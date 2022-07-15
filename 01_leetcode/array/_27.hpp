#pragma once

#include <vector>

namespace _27 {
    class Solution {
    public:
        int removeElement(std::vector<int> &nums, int val) {
            int slow = 0, fast = 0;
            for (; fast < nums.size(); ++fast) {
                if (nums[fast] != val) {
                    nums[slow++] = nums[fast];
                }
            }
            return slow;
#if 0
            // 自己的初版解法
            int left = 0, right = nums.size() - 1;
            while (left <= right) {
                // 从前往后，找元素值等于val的位置
                while (left <= right && nums[left] != val) {
                    left++;
                }
                // 从后往前，找元素等于val
                while (left <= right && nums[right] == val) {
                    right--;
                }
                if (left > right) {
                    return left;
                }
                std::swap(nums[left], nums[right]);
            }
            return left;
#endif
        }

        void test() {
            std::vector<int> nums1{3, 2, 2, 3};
            int val1 = 3;
            std::cout << removeElement(nums1, val1) << std::endl;
//            PrintVec(nums1);

            std::vector<int> nums2{0, 1, 2, 2, 3, 0, 4, 2};
            int val2 = 2;
            std::cout << removeElement(nums2, val2) << std::endl;
//            PrintVec(nums2);

            std::vector<int> nums3{2};
            int val3 = 3;
            std::cout << removeElement(nums3, val3) << std::endl;
            std::cout << "--------------------------------" << std::endl;
        }
    };
}