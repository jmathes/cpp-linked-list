#include "src/linked_list.h"
#include "src/node.h"
#include <gtest/gtest.h>
#include <vector>
#include <stdexcept>

#define TESTING 1

TEST(LinkedList, Constructor)
{
    // This will be a utility method primarily for test readability.
    LinkedList<int> list;
    EXPECT_EQ(nullptr, list.testGetHead());
    EXPECT_EQ(nullptr, list.testGetTail());
}

TEST(LinkedList, Append)
{
    LinkedList<int> list;
    list.append(1);
    EXPECT_EQ(1, list.testGetHead()->value);
    EXPECT_EQ(1, list.testGetTail()->value);
    list.append(2);
    EXPECT_EQ(1, list.testGetHead()->value);
    EXPECT_EQ(2, list.testGetTail()->value);
}

TEST(LinkedList, Prepend)
{
    LinkedList<int> list;
    list.prepend(1);
    EXPECT_EQ(1, list.testGetHead()->value);
    EXPECT_EQ(1, list.testGetTail()->value);
    list.prepend(2);
    EXPECT_EQ(2, list.testGetHead()->value);
    EXPECT_EQ(1, list.testGetTail()->value);
}

TEST(LinkedList, GetLength)
{
    LinkedList<int> list;
    EXPECT_EQ(0, list.getLength());
    list.append(1);
    EXPECT_EQ(1, list.getLength());
    list.append(2);
    EXPECT_EQ(2, list.getLength());
    list.append(3);
    EXPECT_EQ(3, list.getLength());
}

TEST(LinkedList, DifferentTypes)
{
    LinkedList<std::string> list;
    list.append("hello");
    EXPECT_EQ("hello", list.testGetHead()->value);
    EXPECT_EQ("hello", list.testGetTail()->value);
    list.append("world");
    EXPECT_EQ("hello", list.testGetHead()->value);
    EXPECT_EQ("world", list.testGetTail()->value);
}

TEST(LinkedList, FromVector)
{
    std::vector<int> vec = {1, 2, 3};
    LinkedList<int> list = LinkedList<int>::fromVector(vec);
    EXPECT_EQ(1, list.testGetHead()->value);
    EXPECT_EQ(3, list.testGetTail()->value);
    EXPECT_EQ(3, list.getLength());
}

TEST(LinkedList, EqualsOperator)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    LinkedList<int> list2 = LinkedList<int>::fromVector({1, 2, 3});
    EXPECT_TRUE(list == list2);
    list2.append(4);
    EXPECT_FALSE(list == list2);
}

TEST(LinkedList, AssignmentOperator)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    LinkedList<int> list2 = list;
    EXPECT_TRUE(list == list2);
    EXPECT_NE(list.testGetHead(), list2.testGetHead());
    EXPECT_NE(list.testGetTail(), list2.testGetTail());
}

TEST(LinkedList, MoveConstructor)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    LinkedList<int> list2 = LinkedList<int>(std::move(list));
    EXPECT_EQ(0, list.getLength());
    EXPECT_EQ(3, list2.getLength());
}

TEST(LinkedList, CopyConstructor)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    LinkedList<int> list2 = LinkedList<int>(list);
    EXPECT_TRUE(list == list2);
    list.append(4);
    EXPECT_NE(list.testGetHead(), list2.testGetHead());
    EXPECT_NE(list.testGetTail(), list2.testGetTail());
}

TEST(LinkedList, MoveAssignmentOperator)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    LinkedList<int> list2;
    list2 = std::move(list);
    EXPECT_EQ(0, list.getLength());
    EXPECT_EQ(3, list2.getLength());
}

TEST(LinkedList, GetFromIndex)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(2, list[1]);
    EXPECT_EQ(3, list[2]);
}

TEST(LinkedList, GetFromIndexOutOfBounds)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    EXPECT_THROW(list[3], std::out_of_range);
    EXPECT_THROW(list[-1], std::out_of_range);
}

TEST(LinkedList, Reverse)
{
    LinkedList<int> list = LinkedList<int>::fromVector({1, 2, 3});
    LinkedList<int> backwardsList = LinkedList<int>::fromVector({3, 2, 1});
    EXPECT_FALSE(list == backwardsList);
    list.reverse();
    EXPECT_TRUE(list == backwardsList);
}

TEST(LinkedList, ReverseEmptyList)
{
    LinkedList<int> list;
    list.reverse();
    EXPECT_EQ(0, list.getLength());
}

TEST(LinkedList, RemoveByPosition)
{
    LinkedList<char> list = LinkedList<char>::fromVector({'a', 'b', 'c'});
    EXPECT_TRUE(list == LinkedList<char>::fromVector({'a', 'b', 'c'}));
    list.removePosition(1);
    EXPECT_TRUE(list == LinkedList<char>::fromVector({'a', 'c'}));
}

TEST(LinkedList, RemoveByPositionOutOfBounds)
{
    LinkedList<int> list = LinkedList<int>::fromVector({'a', 'b', 'c'});
    EXPECT_THROW(list.removePosition(3), std::out_of_range);
    EXPECT_THROW(list.removePosition(-1), std::out_of_range);
}

TEST(LinkedList, RemoveByValue)
{
    LinkedList<int> list = LinkedList<int>::fromVector({'a', 'b', 'c'});
    EXPECT_TRUE(list == LinkedList<int>::fromVector({'a', 'b', 'c'}));
    list.removeValue('b');
    EXPECT_TRUE(list == LinkedList<int>::fromVector({'a', 'c'}));
}

TEST(LinkedList, removeByValueNotFound)
{
    LinkedList<int> list = LinkedList<int>::fromVector({'a', 'b', 'c'});
    EXPECT_TRUE(list == LinkedList<int>::fromVector({'a', 'b', 'c'}));
    list.removeValue('d');
    EXPECT_TRUE(list == LinkedList<int>::fromVector({'a', 'b', 'c'}));
}