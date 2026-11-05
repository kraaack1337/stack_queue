#include <gtest/gtest.h>
#include "forwardlist.h"

TEST(ForwardListTest, default_constructor_creates_empty_list) {
    ForwardList<int> fl;
    EXPECT_TRUE(fl.empty());
}

TEST(ForwardListTest, fill_constructor_creates_n_identical_elements) {
    ForwardList<int> fl(3, 42);
    EXPECT_FALSE(fl.empty());
    
    EXPECT_EQ(fl.front(), 42);
    fl.pop_front();
    EXPECT_EQ(fl.front(), 42);
    fl.pop_front();
    EXPECT_EQ(fl.front(), 42);
    fl.pop_front();
    
    EXPECT_TRUE(fl.empty());
}

TEST(ForwardListTest, push_front_adds_element_to_beginning) {
    ForwardList<int> fl;
    fl.push_front(10);
    EXPECT_EQ(fl.front(), 10);
    
    fl.push_front(20);
    EXPECT_EQ(fl.front(), 20);
}

TEST(ForwardListTest, pop_front_removes_first_element) {
    ForwardList<int> fl;
    fl.push_front(10);
    fl.push_front(20);
    
    fl.pop_front();
    EXPECT_EQ(fl.front(), 10);
    
    fl.pop_front();
    EXPECT_TRUE(fl.empty());
}

TEST(ForwardListTest, pop_front_on_empty_list_does_not_crash) {
    ForwardList<int> fl;
    fl.pop_front();
    EXPECT_TRUE(fl.empty());
}

TEST(ForwardListTest, clear_removes_all_elements) {
    ForwardList<int> fl;
    fl.push_front(1);
    fl.push_front(2);
    fl.push_front(3);
    
    fl.clear();
    EXPECT_TRUE(fl.empty());
}

TEST(ForwardListTest, copy_constructor_creates_deep_copy) {
    ForwardList<int> fl1;
    fl1.push_front(30);
    fl1.push_front(20);
    fl1.push_front(10);

    ForwardList<int> fl2(fl1);
    
    EXPECT_EQ(fl2.front(), 10);
    fl2.pop_front();
    EXPECT_EQ(fl2.front(), 20);
    
    EXPECT_EQ(fl1.front(), 10);
}

TEST(ForwardListTest, copy_assignment_operator_creates_deep_copy) {
    ForwardList<int> fl1;
    fl1.push_front(100);
    fl1.push_front(50);

    ForwardList<int> fl2;
    fl2.push_front(999); 
    
    fl2 = fl1;
    
    EXPECT_EQ(fl2.front(), 50);
    fl2.pop_front();
    EXPECT_EQ(fl2.front(), 100);
    fl2.pop_front();
    EXPECT_TRUE(fl2.empty());
    
    EXPECT_EQ(fl1.front(), 50);
}

TEST(ForwardListTest, move_constructor_transfers_ownership) {
    ForwardList<int> fl1;
    fl1.push_front(5);
    fl1.push_front(15);

    ForwardList<int> fl2(std::move(fl1));
    
    EXPECT_EQ(fl2.front(), 15);
    EXPECT_TRUE(fl1.empty());
}