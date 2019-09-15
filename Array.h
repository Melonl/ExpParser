#ifndef ARRAY_H
#define ARRAY_H
template <class E>
class Array
{

private:
	E *data;
	int size;
	int capacity;

	void resize(int newCapacity);

public:
	Array(int capacity = 20);
	Array(const Array<E> &arr);
	Array(Array<E> &&arr);
	~Array();

	int getSize();
	int getCapacity();
	bool isEmpty();
	void add(int index, E &e);
	void addFirst(E &e);
	void addLast(E &e);
	void addLast(E &&e);
	E get(int index);
	E getFirst();
	E getLast();
	int find(E &e);
	bool contains(E &e);
	void set(int index, E &e);
	E remove(int index);
	E removeFirst();
	E removeLast();
	int removeElement(E &e);
	E &operator[](int index);

	void printAll();
};

#endif