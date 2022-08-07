#include "common.h"

#ifdef TEST2

#include <queue>

template<typename E>  // E is the element type.
class Queue {
public:
    Queue() = default;

    ~Queue() = default;

    void Enqueue(const E &element) {
        q.push(element);
    }

    E *Dequeue() {
        if (q.empty()) {
            return nullptr;
        } else {
            return &(q.front());
        };
    };  // Returns NULL if the queue is empty.
    size_t size() const { return q.size(); }

private:
    std::queue<E> q;
};

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(3);
    }

    // void TearDown() override {}

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_EQ(q0_.size(), 0);
}

TEST_F(QueueTest, DequeueWorks) {
    int *n = q0_.Dequeue();
    EXPECT_EQ(n, nullptr);

    n = q1_.Dequeue();
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(*n, 1);
//    EXPECT_EQ(q1_.size(), 0);
    EXPECT_EQ(q1_.size(), 1);
    n = nullptr;
    delete n;

    n = q2_.Dequeue();
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(*n, 2);
//    EXPECT_EQ(q2_.size(), 1);
    EXPECT_EQ(q2_.size(), 2);
    n = nullptr;
    delete n;
}

#endif