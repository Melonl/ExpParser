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
    int size();
    E top();
    void push(const E &e);
    E pop();
    void printAll();
};
#endif
