#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "Array.h"
#include "Array.cpp"
#include "iostream"

using namespace std;

template <typename E>
class ArrayStack
{

private:
    Array<E> arr;

public:
    int size()
    {
        return arr.getSize();
    }

    E top()
    {
        return arr.getLast();
    }

    void push(E e)
    {
        arr.addLast(e);
    }

    E pop()
    {
        E e = arr.getLast();
        arr.removeLast();
        return e;
    }

    void printAll()
    {
        arr.printAll();
    }
};
#endif
