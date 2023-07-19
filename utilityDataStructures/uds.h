#pragma once
#include <iostream>

namespace uds{

    template<typename T>
    class Iterator{
        public:
        virtual T getNext() = 0;
        virtual bool hasNext() = 0;
    };

    template<typename T>
    class Collection{
        protected:
        template<typename U>
            class Node{
            public:
            U value;
            Node* next;
            Node();
            Node(const U value, Node* next);
        };

        unsigned int size;
        void validateIndex(int index);
        virtual T* toArray() = 0;
        virtual Iterator<T>* getIterator() = 0;
    };

    template<typename T>
    class LinkedList: public Collection<T>{ 
        protected:
        typename Collection<T>::template Node<T>* head;
        void deleteNode(typename Collection<T>::template Node<T>* node);

        public:
        template<typename U>
        class LinkedListIterator: public Iterator<U>{
            private:
            typename Collection<U>::template Node<U>* current;

            public:
            LinkedListIterator(typename Collection<U>::template Node<U>* start);
            U getNext() override;
            virtual bool hasNext() override;
        };

        LinkedList();
        ~LinkedList();
        void add(const T value);
        void addAt(const T value, int index);
        void addAtFront(const T value);
        void addAtBack(const T value);
        void remove(int index);
        T get(int index);
        T getAndRemove(int index);
        int getSize();
        void clear();
        void reverse();
        void print();
        T* toArray() override;
        Iterator<T>* getIterator() override;
    };

    template<typename T>
    class Stack : protected LinkedList<T>{
        public:
        Stack();
        void push(const T value);
        T pop();
        T peek();
        int getSize();
    };
}

//#include "uds.tpp"
#include "Collection.tpp"
#include "LinkedList.tpp"
#include "Stack.tpp"