参考链接：https://github.com/youngyangyang04/leetcode-master

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

代码实现：

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
