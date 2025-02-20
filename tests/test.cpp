#include <gtest/gtest.h>
#include "../container/lookUpTable.hpp"
using namespace mgc;
#include <string>

TEST(LookupTableTest, EmptyTable) {
    LookupTable<std::string, int> table;
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(LookupTableTest, ReserveAndCapacity) {
    LookupTable<std::string, int> table;
    table.reserve(20);
    EXPECT_GE(table.capacity(), 20);
}

TEST(LookupTableTest, InsertAndEmplace) {
    LookupTable<std::string, int> table;
    table.reserve(2);
    table.insert("a", 1);
    table.emplace("b", 2);
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table[0].first, "a");
    EXPECT_EQ(table[1].first, "b");
}

TEST(LookupTableTest, AtAndOperatorBrackets) {
    LookupTable<std::string, int> table;
    table.insert("test", 100);
    EXPECT_EQ(table.at(0).first, "test");
    EXPECT_EQ(table[0].second, 100);
    EXPECT_THROW(table.at(1), std::out_of_range);
}

TEST(LookupTableTest, FrontAndBack) {
    LookupTable<std::string, int> table;
    table.insert("first", 10);
    table.insert("middle", 20);
    table.insert("last", 30);
    EXPECT_EQ(table.front().first, "first");
    EXPECT_EQ(table.back().first, "last");
    LookupTable<std::string, int> emptyTable;
    EXPECT_THROW(emptyTable.front(), std::out_of_range);
    EXPECT_THROW(emptyTable.back(), std::out_of_range);
}

TEST(LookupTableTest, DataMethod) {
    LookupTable<std::string, int> table;
    table.insert("data", 55);
    auto dataPtr = table.data();
    EXPECT_EQ(dataPtr[0].first, "data");
    EXPECT_EQ(dataPtr[0].second, 55);
}

TEST(LookupTableTest, IteratorOperators) {
    LookupTable<std::string, int> table;
    table.insert("x", 1);
    table.insert("y", 2);
    table.insert("z", 3);
    auto it = table.begin();
    EXPECT_EQ((*it).first, "x");
    EXPECT_EQ(it->second, 1);
    auto it2 = it++;
    EXPECT_EQ(it2->first, "x");
    EXPECT_EQ((*it).first, "y");
    ++it;
    EXPECT_EQ(it->first, "z");
}

TEST(LookupTableTest, IteratorEquality) {
    LookupTable<std::string, int> table;
    table.insert("1", 1);
    table.insert("2", 2);
    auto it1 = table.begin();
    auto it2 = table.begin();
    EXPECT_EQ(it1, it2);
    ++it1;
    EXPECT_NE(it1, it2);
}

TEST(LookupTableTest, ConstIteratorOperators) {
    LookupTable<std::string, int> table;
    table.insert("a", 10);
    table.insert("b", 20);
    const LookupTable<std::string, int>& ctable = table;
    auto cit = ctable.begin();
    EXPECT_EQ((*cit).first, "a");
    EXPECT_EQ(cit->second, 10);
    auto cit2 = cit++;
    EXPECT_EQ(cit2->first, "a");
    EXPECT_EQ((*cit).first, "b");
    ++cit;
    EXPECT_EQ(cit, ctable.end());
}

TEST(LookupTableTest, RangeBasedForLoop) {
    LookupTable<std::string, int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    std::string s;
    for (const auto &pair : table) {
        s += pair.first;
    }
    EXPECT_EQ(s, "onetwothree");
}

TEST(LookupTableTest, FindMethod) {
    LookupTable<std::string, int> table;
    table.insert("key1", 111);
    table.insert("key2", 222);
    table.insert("key3", 333);
    size_t idx = table.find("key2");
    EXPECT_NE(idx, table.size());
    EXPECT_EQ(table[idx].second, 222);
    idx = table.find("noKey");
    EXPECT_EQ(idx, table.size());
}

TEST(LookupTableTest, EraseByIndex) {
    LookupTable<std::string, int> table;
    table.insert("first", 1);
    table.insert("second", 2);
    table.insert("third", 3);
    table.erase(1);
    EXPECT_EQ(table.size(), 2);
    EXPECT_EQ(table[0].first, "first");
    EXPECT_EQ(table[1].first, "third");
    EXPECT_THROW(table.erase(5), std::out_of_range);
}

TEST(LookupTableTest, EraseByKey) {
    LookupTable<std::string, int> table;
    table.insert("alpha", 10);
    table.insert("beta", 20);
    table.insert("gamma", 30);
    bool erased = table.erase("beta");
    EXPECT_TRUE(erased);
    EXPECT_EQ(table.size(), 2);
    erased = table.erase("delta");
    EXPECT_FALSE(erased);
}

TEST(LookupTableTest, ClearMethod) {
    LookupTable<std::string, int> table;
    table.insert("item", 123);
    table.clear();
    EXPECT_EQ(table.size(), 0);
    EXPECT_TRUE(table.empty());
}

TEST(LookupTableTest, CopyConstructor) {
    LookupTable<std::string, int> table;
    table.insert("copy", 5);
    table.insert("construct", 6);
    LookupTable<std::string, int> copy(table);
    EXPECT_EQ(copy.size(), table.size());
    EXPECT_EQ(copy[0].first, table[0].first);
    EXPECT_EQ(copy[1].second, table[1].second);
}

TEST(LookupTableTest, CopyAssignment) {
    LookupTable<std::string, int> table;
    table.insert("assign", 50);
    table.insert("copy", 60);
    LookupTable<std::string, int> copy;
    copy = table;
    EXPECT_EQ(copy.size(), table.size());
    EXPECT_EQ(copy[0].first, table[0].first);
    EXPECT_EQ(copy[1].second, table[1].second);
}

TEST(LookupTableTest, MoveConstructor) {
    LookupTable<std::string, int> table;
    table.insert("move", 7);
    table.insert("ctor", 8);
    LookupTable<std::string, int> moved(std::move(table));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(table.empty());
}

TEST(LookupTableTest, MoveAssignment) {
    LookupTable<std::string, int> table;
    table.insert("move", 9);
    table.insert("assign", 10);
    LookupTable<std::string, int> moved;
    moved = std::move(table);
    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(table.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
