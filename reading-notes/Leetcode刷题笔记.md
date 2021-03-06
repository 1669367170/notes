参考链接：https://github.com/youngyangyang04/leetcode-master

## 数组

### 1. 题目分类大纲

#### 二分查找

该类型题目：704

暴力解法时间复杂度：O(n)；二分法时间复杂度：O(log(n))。

> 使用二分查找的前提：**1）数组为有序数组**；2）一般数组中无重复元素，否则查找的结果不唯一。

> 边界条件处理：区间定义一般为两种，左闭右闭即`[left, right]`，左闭右开即`[left, right)`。**循环不变量原则，在循环中坚持对区间的定义。**
>
> 1）左闭右闭区间， `while(left <= right)`，要使用<=，因为`left == right`是有意义的（`target`在`[left, right]`区间）；同时`right`要赋值`middle-1`；
>
> 2）左闭右开区间，`while(left < right)`，要使用<，因为`left == right`是没有意义的（`target`在`[left, right)`区间）；同时`right`要赋值`middle`。

#### 双指针法

该类型题目：27，977

暴力解法时间复杂度：O(n^2)；双指针法时间复杂度：O(n)。

> 双指针法（快慢指针法）：**通过一个快指针和慢指针在一个for循环下完成两个for循环的工作。**时间复杂度从O(n^2)->O(n)。常用于数组、链表、字符串等操作的题中。

#### 滑动窗口法

该类型题目：209题

暴力解法时间复杂度：O(n^2)；滑动窗口法时间复杂度：O(n)。

> 滑动窗口法：不断地调整子序列地起始位置和终止位置，从而得到我们想要的结果。（**也可以理解成双指针的法的一种**）
>
> 要实现滑动窗口，主要确定如下三点：
>
> - 窗口是什么？
> - 如何移动窗口的起始位置？
> - 如何移动窗口的结束位置？

![img](https://camo.githubusercontent.com/97d746e877876898e216a451d20a4abd607a8ab20f31886a4ab7379fb7cd2214/68747470733a2f2f636f64652d7468696e6b696e672d313235333835353039332e66696c652e6d7971636c6f75642e636f6d2f706963732f2545362539352542302545372542422538342545362538302542422545372542422539332e706e67)

### 2. 具体题目和代码实现

#### [第704题. 二分查找](https://leetcode-cn.com/problems/binary-search/)

给定一个n个元素有序的（升序）整型数组`nums`和一个目标值`target`，写一个函数搜索`nums`中的`target`，如果目标值存在返回下标，否则返回-1。

示例1：

输入：`nums = [-1, 0, 3, 5, 9, 12]`，`target = 9`

输出：4

示例2：

输入：`nums = [-1, 0, 3, 5, 9, 12], target = 2`

输出：-1（解释：2不存在`nums`中，因此返回-1）

【代码实现】

```c++
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
    };
}
```

#### [第27题. 移除元素](https://leetcode-cn.com/problems/remove-element/)

给你一个数组`nums`和一个值`val`，你需要原地移除所有数值等于`val`的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用O(1)额外空间并原地修改输入数组。

元素的顺序可以改变，你不需要考虑数组中超出新长度后面的元素。

示例1：

输入：`nums = [3, 2, 2, 3]，val = 3`

输出：`2，nums = [2, 2]`

【代码实现】 思路：双指针

```c++
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
    };
}
```

#### [第977题. 有序数组的平方](https://leetcode.cn/problems/squares-of-a-sorted-array/)

给你一个按非递减顺序排序的整数数组nums，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

示例1：

输入：nums = [-4, -1, 0, 3, 10]

输出：[0, 1, 9, 16, 100]

【代码实现】思路：双指针，O(n)时间复杂度

```c++
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
    };
}
```

#### [第209题. 长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/)

给你一个含有n个正整数的数组和一个正整数target。找出该数组中满足其和>=target的长度最小的连续子数组，并返回其长度。如果不存在符合条件的子数组，返回0。

示例1：

输入：target = 7，nums = [2, 3, 1, 2, 4, 3]

输出：2

解释：子数组[4, 3]是该条件下的长度最小的子数组

【代码实现】思路：滑动窗口

```c++
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
            // 自己的初版解法
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
```

[第59题. 螺旋矩阵Ⅱ](https://leetcode.cn/problems/spiral-matrix-ii/)

给你一个正整数n，生成一个包含1到n^2所有元素，且元素按顺时针顺序螺旋排列的n*n正方形矩阵matrix。

示例1：

输入：n = 3

输出：[[1, 2, 3], [8, 9, 4], [7, 6, 5]

【代码实现】

```c++
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
    };
}
```

## 回溯法

### 1. 回溯法介绍

> - 什么是回溯：回溯是递归的副产品，只要有递归就会有回溯。是一种回溯搜索的方式。
>
> - 效率：回溯的本质是穷举，穷举所有可能，并不是什么高效算法。若要高效一些，可以加一些剪枝操作。
>
> - 如何理解：
>
>   回溯解决的问题可以抽象为树形结构。在集合中递归查找子集，集合的大小就构成了树的宽度，递归的深度，都构成了树的深度。递归要有终止条件，所以必然是一棵高度有限的树（N叉树）。

### 2. 回溯法模板

#### 1）回溯函数模板返回值以及参数

```c++
void backtracking(参数)
```

#### 2）回溯函数终止条件

什么时候达到了终止条件，树中就可以看出，一般来说搜到叶子节点了，也就找到了满足条件的一条答案，把这个答案存放起来，并结束本层递归。

```c++
if (终止条件) {
    存放结果;
    return;
}
```

#### 3）回溯搜索的遍历过程

回溯法一般是在集合中递归搜索，**集合的大小构成了树的宽度，递归的深度构成的树的深度**。

for循环横向遍历，backtracking（递归）就是纵向遍历。

```c++
for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
    处理节点;
    backtracking(路径，选择列表); // 递归
    回溯，撤销处理结果
}
```

完整模板：

```c++
void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
```

### 3. 题目分类大纲

> - 组合：N个数中按一定规则，找k个数的集合

> - 分割：一个字符串按一定规则，有几种切割方式

> - 子集：一个N个数的集合里，有多少符合条件的子集

> - 排列：N个数按一定规则全排列，有几种排列方式

> - 棋盘问题：N皇后、解数独等

### 4. 具体题目和代码实现

#### [第77题. 组合](https://leetcode-cn.com/problems/combinations/)

给定两个整数n和k，返回范围中[1, n]中所有可能的k个数的组合。可以按任何顺序返回答案。

示例1：

输入：n = 4, k = 2

输出：

```c++
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

【代码实现】

```c++
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

    private:
        std::vector<std::vector<int>> res;
    };
}
```
