#include "src/common_utils.h"
#include <vector>
#include <gtest/gtest.h>

// 选择排序 (一次遍历后，将最小的元素放到最前)
void SelectionSort(std::vector<int> &a) {
    if (a.size() < 2) {
        return;
    }
    for (int i = 0; i < a.size(); ++i) { // i ~ n-1
        int minIndex = i;
        for (int j = i + 1; j < a.size(); ++j) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
//        a[i] = a[i] ^ a[minIndex];
//        a[minIndex] = a[i] ^ a[minIndex];
//        a[i] = a[i] ^ a[minIndex];
        std::swap(a[i], a[minIndex]);
    }
}

// 冒泡排序 (遍历0~n-1的元素，两两比较，一次遍历后将最大的元素放到最后)
void BubbleSort(std::vector<int> &a) {
    if (a.size() < 2) {
        return;
    }
    for (int end = a.size() - 1; end > 0; --end) {
        for (int i = 0; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
            }
        }
    }

//    for (int i = 0; i < a.size(); ++i) {
//        for (int j = 1; j < a.size() - i; ++j) {
//            if (a[j - 1] > a[j]) {
//                std::swap(a[j - 1], a[j]);
//            }
//        }
//    }
}

// 插入排序 (遍历0~i的元素，若i-1位置的元素>i位置元素，则交换，一次遍历后保证0~i有序)
void InsertSort(std::vector<int> &a) {
    if (a.size() < 2) {
        return;
    }
    // 0~0有序
    // 0~i想有序
    for (int i = 1; i < a.size(); ++i) { // 0 ~ i做到有序
        for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; --j) { // 往前找
            std::swap(a[j], a[j + 1]);
        }
    }
}

class TestArray {
public:
    TestArray() = default;
    ~TestArray() = default;

    std::vector<int> truth;
    std::vector<int> input;
};

class SortTest : public ::testing::Test {
protected:
    void SetUp() override {
        testArray.truth = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        testArray.input = {2, 3, 1, 4, 6, 8, 9, 7, 5};
    }

    // void TearDown() override {}
    TestArray testArray;
};


TEST_F(SortTest, Selection) {
    PrintVec(testArray.input);
    SelectionSort(testArray.input);
    EXPECT_EQ(testArray.input, testArray.truth);
}

TEST_F(SortTest, Bubble) {
    PrintVec(testArray.input);
    BubbleSort(testArray.input);
    EXPECT_EQ(testArray.input, testArray.truth);
}

TEST_F(SortTest, Insert) {
    PrintVec(testArray.input);
    InsertSort(testArray.input);
    EXPECT_EQ(testArray.input, testArray.truth);
}