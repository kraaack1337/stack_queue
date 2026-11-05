#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "queue.h"

TEST(QueueTest, default_constructor_creates_empty_queue) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_FALSE(q.full());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, push_and_pop_maintains_fifo_order) {
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 30);

    q.pop();
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 20);

    q.pop();
    EXPECT_EQ(q.front(), 30);

    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, accessors_and_pop_throw_on_empty_queue) {
    Queue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
    EXPECT_THROW(q.front(), std::out_of_range);
    EXPECT_THROW(q.back(), std::out_of_range);

    q.push(1);
    q.pop();

    EXPECT_THROW(q.pop(), std::out_of_range);
    EXPECT_THROW(q.front(), std::out_of_range);
    EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, circular_wrap_around_maintains_elements_order) {
    Queue<int> q;
    for (int i = 0; i < 20; ++i) {
        q.push(i);
        EXPECT_EQ(q.front(), i);
        EXPECT_EQ(q.back(), i);
        q.pop();
        EXPECT_TRUE(q.empty());
    }
}

TEST(QueueTest, reallocate_preserves_elements_and_straightens_buffer) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.pop();

    q.push(3);
    q.push(4);
    q.push(5);

    q.push(6);

    EXPECT_EQ(q.size(), 5);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 6);

    int expected[] = {2, 3, 4, 5, 6};
    for (int val : expected) {
        ASSERT_FALSE(q.empty());
        EXPECT_EQ(q.front(), val);
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, push_rvalue_moves_object) {
    Queue<std::string> q;
    std::string str = "long_string_to_avoid_sso_allocation_optimization";
    q.push(std::move(str));

    EXPECT_EQ(q.front(), "long_string_to_avoid_sso_allocation_optimization");
    EXPECT_TRUE(str.empty());
}

TEST(QueueTest, copy_constructor_creates_deep_copy) {
    Queue<int> q1;
    q1.push(100);
    q1.push(200);

    Queue<int> q2(q1);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 100);
    EXPECT_EQ(q2.back(), 200);

    q1.pop();
    EXPECT_EQ(q1.size(), 1);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 100);
}

TEST(QueueTest, copy_assignment_operator_creates_deep_copy) {
    Queue<int> q1;
    q1.push(100);
    q1.push(200);

    Queue<int> q2;
    q2.push(999);
    q2 = q1;

    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 100);
    EXPECT_EQ(q2.back(), 200);

    q1.pop();
    EXPECT_EQ(q1.size(), 1);
    EXPECT_EQ(q2.size(), 2);
}

TEST(QueueTest, move_constructor_transfers_ownership_and_resets_source) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);

    Queue<int> q2(std::move(q1));
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 1);
    EXPECT_TRUE(q1.empty());
    EXPECT_EQ(q1.size(), 0);
}

TEST(QueueTest, move_assignment_operator_transfers_ownership_and_resets_source) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);

    Queue<int> q2;
    q2.push(99);
    q2 = std::move(q1);

    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 1);
    EXPECT_TRUE(q1.empty());
    EXPECT_EQ(q1.size(), 0);
}