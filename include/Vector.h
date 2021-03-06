#ifndef VECTOR_H
#define VECTOR_H
#include<initializer_list>

template<typename T>
class Vector {
private:
	T* data;
	unsigned int size;
	unsigned int capacity;

	void copy(const Vector<T>&);
	void deleteInternals();
	void reserve();
public:
	Vector(const unsigned int& = 1);
	Vector(const Vector<T>&);
	Vector(std::initializer_list<T>);
	~Vector();
	Vector<T>& operator=(const Vector<T>&);

	T& operator[](const unsigned int&);
	const T& operator[](const unsigned int&) const;

	bool pushBack(const T&);
	bool popBack();
	bool isFull() const;
	bool isEmpty() const;

	int indexOf(const T&) const;

	unsigned int getSize() const;
	unsigned int getCapacity() const;

	void print() const;
};

#endif