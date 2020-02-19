#include "ArrayStack.h"

template <typename E>
int ArrayStack<E>::size()
{
    return arr.getSize();
}

template <typename E>
E ArrayStack<E>::top()
{
    return arr.getLast();
}

template <typename E>
void ArrayStack<E>::push(const E &e)
{
    arr.addLast(e);
}

template <typename E>
E ArrayStack<E>::pop()
{
    E e = arr.getLast();
    arr.removeLast();
    return e;
}

template <typename E>
void ArrayStack<E>::printAll()
{
    arr.printAll();
}