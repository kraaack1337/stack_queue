#include <gtest/gtest.h>
#include <string>
#include "stack.h"

TEST(StackTest, default_constructor_creates_empty_stack) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.get_size(), 0);
}

TEST(StackTest, push_increases_size_and_updates_top) {
    Stack<int> s;
    s.push(10);
    
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.get_size(), 1);
    EXPECT_EQ(s.top(), 10);

    s.push(20);
    EXPECT_EQ(s.get_size(), 2);
    EXPECT_EQ(s.top(), 20);
}

TEST(StackTest, pop_decreases_size_and_removes_top_element) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    
    s.pop();
    EXPECT_EQ(s.get_size(), 2);
    EXPECT_EQ(s.top(), 20);

    s.pop();
    EXPECT_EQ(s.get_size(), 1);
    EXPECT_EQ(s.top(), 10);

    s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.get_size(), 0);
}

TEST(StackTest, pop_on_empty_stack_does_not_throw_and_keeps_size_zero) {
    Stack<int> s;
    s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.get_size(), 0);
}

TEST(StackTest, clear_removes_all_elements_and_resets_size) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.get_size(), 0);
}

