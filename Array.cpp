#include "Array.h"
#include <iostream>
#include <string>

using namespace std;

template <class E>
Array<E>::Array(int capacity)
{
	data = new E[capacity];
	this->capacity = capacity;
	size = 0;
}

template <class E>
Array<E>::Array(const Array<E> &arr)
{
	data = new E[arr.getSize()];
	*data = *arr.data;
}

template <class E>
Array<E>::Array(Array<E> &&arr)
{
	data = arr.data;
	arr.data = nullptr;
}

template <class E>
Array<E>::~Array()
{
	delete[] data;
	data = NULL;
}

template <class E>
int Array<E>::getSize()
{
	return size;
}

template <class E>
int Array<E>::getCapacity()
{
	return this->capacity;
}

template <class E>
bool Array<E>::isEmpty()
{
	return size == 0;
}

template <class E>
void Array<E>::resize(int newCapacity)
{
	cout << newCapacity << ",";
	E *newData = new E[newCapacity];
	capacity = newCapacity;
	for (int i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}

template <class E>
void Array<E>::add(int index, E &e)
{
	//cout << getCapacity() << endl;
	if (index < 0 || index > size)
	{
		throw "add failed.index is illegal.";
	}

	if (size == getCapacity())
	{
		resize(getCapacity() * 1.5);
	}

	for (int i = size - 1; i >= index; i--)
	{
		data[i + 1] = data[i];
	}
	data[index] = e;
	size++;
}

template <class E>
void Array<E>::addLast(E &e)
{
	add(size, e);
}

template <class E>
void Array<E>::addLast(E &&e)
{
	add(size, e);
}

template <class E>
void Array<E>::addFirst(E &e)
{
	add(0, e);
}

template <class E>
E Array<E>::get(int index)
{
	if (index < 0 || index > size)
	{
		throw "get failed.index is illegal.";
	}

	return data[index];
}

template <class E>
E Array<E>::getFirst()
{
	return get(0);
}

template <class E>
E Array<E>::getLast()
{
	return get(size - 1);
}

template <class E>
int Array<E>::find(E &e)
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == e)
		{
			return i;
		}
	}

	return -1;
}

template <class E>
bool Array<E>::contains(E &e)
{
	int res = find(e);
	if (res == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template <class E>
void Array<E>::set(int index, E &e)
{
	if (index < 0 || index > size)
	{
		throw "set failed.index is illegal.";
	}

	data[index] = e;
}

template <class E>
E Array<E>::remove(int index)
{
	if (index < 0 || index > size)
	{
		throw "remove failed.index is illegal.";
	}
	E res = get(index);
	for (int i = index; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
	if (size <= getCapacity() / 4 && getCapacity() / 2 != 0 && size >= 10)
	{
		resize(getCapacity() / 2);
	}
	return res;
}

template <class E>
E Array<E>::removeFirst()
{
	return remove(0);
}

template <class E>
E Array<E>::removeLast()
{
	return remove(size - 1);
}

template <class E>
int Array<E>::removeElement(E &e)
{
	int res = find(e);
	if (res != -1)
	{
		remove(res);
	}
	return res;
}

template <class E>
E &Array<E>::operator[](int index)
{
	if (index < 0 || (size != 0 && index >= size))
	{
		cout << size << endl;
		cout << "operator[int] index illegal." << endl;
	}
	return data[index];
}

template <class E>
void Array<E>::printAll()
{
	string str;

	str.append("size = ");
	str.append(to_string(size));
	str.append(",capacity = ");
	str.append(to_string(getCapacity()));
	str.append("\n[");
	for (int i = 0; i < size; i++)
	{
		//string ss = to_string(data[i]);
		str.append(data[i]);
		if (i != size - 1)
		{
			str.append(", ");
		}
	}
	str.append("]");
	cout << str.c_str() << endl;
}
