#include<gtest/gtest.h>
#include<iostream>
#include"../utilityDataStructures/uds.h"

template<typename T>
bool compareArrays(T* array1, T* array2, int size){
    for (size_t i = 0; i < size; i++)
    {
        if(array1[i] != array2[i]){
            return false;
        }
    }
    return true;
}

TEST(LinkedListTest, IllegalAccessTest){
    uds::LinkedList<int> list;

    EXPECT_THROW({
    try
    {
        list.get(0);
    }
    catch( const std::out_of_range & e )
    {
        EXPECT_STREQ( "Attempt to acces index out of list range", e.what() );
        throw;
    }
    }, std::out_of_range );

    EXPECT_THROW({
    try
    {
        list.getAndRemove(0);
    }
    catch( const std::out_of_range & e )
    {
        EXPECT_STREQ( "Attempt to acces index out of list range", e.what() );
        throw;
    }
    }, std::out_of_range );

    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);

    EXPECT_THROW({
    try
    {
        list.get(4);
    }
    catch( const std::out_of_range & e )
    {
        EXPECT_STREQ( "Attempt to acces index out of list range", e.what() );
        throw;
    }
    }, std::out_of_range );

    EXPECT_THROW({
    try
    {
        list.getAndRemove(4);
    }
    catch( const std::out_of_range & e )
    {
        EXPECT_STREQ( "Attempt to acces index out of list range", e.what() );
        throw;
    }
    }, std::out_of_range );

    EXPECT_THROW({
    try
    {
        list.get(-1);
    }
    catch( const std::domain_error & e )
    {
        EXPECT_STREQ( "Provided negative number for a list index", e.what() );
        throw;
    }
    }, std::domain_error);

    EXPECT_THROW({
    try
    {
        list.getAndRemove(-1);
    }
    catch( const std::domain_error & e )
    {
        EXPECT_STREQ( "Provided negative number for a list index", e.what() );
        throw;
    }
    }, std::domain_error);
}

TEST(LinkedListTest, AddingGettingRemovingTest){
    uds::LinkedList<int> list;
    
    list.add(0);                        // list: [0]
    list.add(1);                        // list: [1,0]
    list.addAtBack(2);                  // list: [1,0,2]
    list.addAtBack(3);                  // list: [1,0,2,3]
    list.addAtFront(4);                 // list: [4,1,0,2,3]
    list.addAtFront(5);                 // list: [5,4,1,0,2,3]
    list.addAt(6, list.getSize()/2);    // list: [5,4,1,6,0,2,3]
    list.addAt(7, list.getSize()/2);    // list: [5,4,1,7,6,0,2,3]
    list.addAt(8, list.getSize()/2);    // list: [5,4,1,7,8,6,0,2,3]
    list.addAt(9, 0);                   // list: [9,5,4,1,7,8,6,0,2,3]
    list.addAt(10, list.getSize()-1);   // list: [9,5,4,1,7,8,6,0,2,10,3]

    EXPECT_EQ(list.get(0), 9);
    EXPECT_EQ(list.get(1), 5);
    EXPECT_EQ(list.get(2), 4);
    EXPECT_EQ(list.get(3), 1);
    EXPECT_EQ(list.get(4), 7);
    EXPECT_EQ(list.get(5), 8);
    EXPECT_EQ(list.get(6), 6);
    EXPECT_EQ(list.get(7), 0);
    EXPECT_EQ(list.get(8), 2);
    EXPECT_EQ(list.get(9), 10);
    EXPECT_EQ(list.get(10), 3);
}

TEST(LinkedListTest, LinkedListIteratorTest){
    uds::LinkedList<int> list;
    list.addAtFront(1);
    list.addAtFront(0);
    list.addAtBack(2);
    list.addAtBack(3);
    
    uds::Iterator<int> *iterator = list.getIterator();
    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(iterator->getNext(), 0);
    EXPECT_EQ(iterator->getNext(), 1);
    EXPECT_EQ(iterator->getNext(), 2);
    EXPECT_EQ(iterator->getNext(), 3);
    EXPECT_FALSE(iterator->hasNext());
}

TEST(LinkedListTest, LinkedListReverseTest){
    uds::LinkedList<int> list;
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5); // list: [5,4,3,2,1,0]

    list.reverse();

    EXPECT_EQ(list.get(0), 0);
    EXPECT_EQ(list.get(1), 1);
    EXPECT_EQ(list.get(2), 2);
    EXPECT_EQ(list.get(3), 3);
    EXPECT_EQ(list.get(4), 4);
    EXPECT_EQ(list.get(5), 5);
}

TEST(StackTest, StackPopWhileEmptyTest){
    uds::Stack<int> stack;

    EXPECT_THROW({
    try
    {
        stack.pop();
    }
    catch( const std::out_of_range & e )
    {
        EXPECT_STREQ( "Attempt to acces index out of list range", e.what() );
        throw;
    }
    }, std::out_of_range );
}

TEST(StackTest, StackPushPopPeekTest){
    uds::Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.getSize(), 3);

    EXPECT_EQ(stack.peek(), 3);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.peek(), 2);
    EXPECT_EQ(stack.pop(), 2);

    EXPECT_EQ(stack.getSize(), 1);

    stack.push(4);

    EXPECT_EQ(stack.peek(), 4);
    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.peek(), 1);
    EXPECT_EQ(stack.pop(), 1);
}
