/*
Sviridenko Elena st130482@student.spbu.ru
A template container that implements a STL-style.
It supports iterators, standard concepts, error handling, and standard operators
*/
#include <gtest/gtest.h>
#include "CyclicalList.h"


TEST(CyclicalListTest, PushBackAndFrontBackAccess) {
    CyclicalList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
    EXPECT_EQ(list.size(), 3);
}

TEST(CyclicalListTest, PushFront) {
    CyclicalList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    EXPECT_EQ(list.front(), 30);
    EXPECT_EQ(list.back(), 10);
    EXPECT_EQ(list.size(), 3);
}

TEST(CyclicalListTest, PopFrontAndBack) {
    CyclicalList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.size(), 2);

    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 1);
}

TEST(CyclicalListTest, IteratorTraversal) {
    CyclicalList<int> list;
    for (int i = 1; i <= 5; ++i) list.push_back(i);

    int expected = 1;
    for (int value : list) {
        EXPECT_EQ(value, expected++);
    }
}

TEST(CyclicalListTest, ConstIterator) {
    CyclicalList<int> list;
    list.push_back(1);
    list.push_back(2);

    const CyclicalList<int>& constList = list;
    auto it = constList.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(CyclicalListTest, IteratorEquality) {
    CyclicalList<int> list;
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);

    list.push_back(5);
    it1 = list.begin();
    it2 = list.begin();
    ++it2;
    EXPECT_NE(it1, it2);
}

TEST(CyclicalListTest, InsertAndErase) {
    CyclicalList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(4);

    auto it = list.begin();
    ++it;
    list.insert(it, 99);

    std::vector<int> expected = {1, 99, 2, 4};
    auto iter = list.begin();
    for (int val : expected) {
        EXPECT_EQ(*iter, val);
        ++iter;
    }

    it = list.begin();
    ++it;
    list.erase(it);

    expected = {1, 2, 4};
    iter = list.begin();
    for (int val : expected) {
        EXPECT_EQ(*iter, val);
        ++iter;
    }
}

TEST(CyclicalListTest, InsertIntoEmptyAtBegin) {
    CyclicalList<int> list;
    list.insert(list.begin(), 42);
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.size(), 1);
}

TEST(CyclicalListTest, InsertEndWorksCorrectly) {
    CyclicalList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.insert(list.end(), 3);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.size(), 3);
}

TEST(CyclicalListTest, ClearAndEmpty) {
    CyclicalList<std::string> list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");

    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(CyclicalListTest, CopyConstructor) {
    CyclicalList<int> list;
    list.push_back(1);
    list.push_back(2);

    CyclicalList<int> copy = list;

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 2);
}

TEST(CyclicalListTest, MoveConstructor) {
    CyclicalList<int> list;
    list.push_back(1);
    list.push_back(2);

    CyclicalList<int> moved = std::move(list);
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(list.empty());
}

TEST(CyclicalListTest, CopyAssignment) {
    CyclicalList<int> a;
    a.push_back(1);
    a.push_back(2);

    CyclicalList<int> b;
    b.push_back(3);
    b = a;

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.front(), 1);
    EXPECT_EQ(b.back(), 2);
}

TEST(CyclicalListTest, MoveAssignment) {
    CyclicalList<int> a;
    a.push_back(1);
    a.push_back(2);

    CyclicalList<int> b;
    b = std::move(a);

    EXPECT_EQ(b.size(), 2);
    EXPECT_TRUE(a.empty());
}

TEST(CyclicalListTest, AssignFunction) {
    CyclicalList<int> list;
    list.assign(4, 7);

    EXPECT_EQ(list.size(), 4);
    for (int val : list) {
        EXPECT_EQ(val, 7);
    }
}

TEST(CyclicalListTest, SwapFunction) {
    CyclicalList<int> a;
    a.push_back(1);
    a.push_back(2);

    CyclicalList<int> b;
    b.push_back(10);
    b.push_back(20);
    b.push_back(30);

    a.swap(b);

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(a.front(), 10);
    EXPECT_EQ(b.front(), 1);
}

TEST(CyclicalListTest, PopFrontEmptyThrows) {
    CyclicalList<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(CyclicalListTest, PopBackEmptyThrows) {
    CyclicalList<int> list;
    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TEST(CyclicalListTest, FrontOnEmptyThrows) {
    CyclicalList<int> list;
    EXPECT_THROW(list.front(), std::out_of_range);
}

TEST(CyclicalListTest, BackOnEmptyThrows) {
    CyclicalList<int> list;
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(CyclicalListTest, EraseBeginEndThrows) {
    CyclicalList<int> list;
    EXPECT_THROW(list.erase(list.end()), std::out_of_range);
}

TEST(CyclicalListTest, EqualityEmptyLists) {
    CyclicalList<int> list1;
    CyclicalList<int> list2;
    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(CyclicalListTest, EqualitySameElements) {
    CyclicalList<int> list1;
    CyclicalList<int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(CyclicalListTest, InequalityDifferentSizes) {
    CyclicalList<int> list1;
    CyclicalList<int> list2;

    list1.push_back(1);
    list1.push_back(2);

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    EXPECT_FALSE(list1 == list2);
    EXPECT_TRUE(list1 != list2);
}

TEST(CyclicalListTest, InequalityDifferentValues) {
    CyclicalList<int> list1;
    CyclicalList<int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    list2.push_back(1);
    list2.push_back(99);
    list2.push_back(3);

    EXPECT_FALSE(list1 == list2);
    EXPECT_TRUE(list1 != list2);
}

TEST(CyclicalListTest, EqualityAfterCopy) {
    CyclicalList<std::string> list1;
    list1.push_back("a");
    list1.push_back("b");

    CyclicalList<std::string> list2 = list1;

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(CyclicalListTest, EqualityAfterMove) {
    CyclicalList<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    CyclicalList<int> list2 = std::move(list1);

    CyclicalList<int> expected;
    expected.push_back(10);
    expected.push_back(20);

    EXPECT_TRUE(list2 == expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
