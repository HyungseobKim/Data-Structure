#ifndef HEAP_H
#define HEAP_H
/*------------------------------------------------------------------------
File Name: Heap.h
Purpose: Declaration for Heap class.
Author: Kim Hyungseob
Created: 5/24
------------------------------------------------------------------------*/

template<typename T>
class Heap
{
public:
	Heap(bool LargestInFront = true) : m_LargestInFront(LargestInFront) {}
	~Heap();
	void Print() const;

	void Insert(T value);
	void Remove(unsigned int index);
	void Heapify();
	void Sort();
	void Reverse();
	void SetArray(const T* data, size_t size);

private:
	void Heapify(T* data, size_t size);
	void SwapLargestAtFront(T* data, size_t size, unsigned int index);
	void SwapSmallestAtFront(T* data, size_t size, unsigned int index);
	void Grow();

private:
	void Swap(T* data, unsigned int index1, unsigned int index2);

	unsigned int GetLeft(unsigned int index) const;
	unsigned int GetParent(unsigned int index) const;

private:
	T* m_data = new T[2];

	size_t m_size = 0;
	size_t m_capacity = 2;

	bool m_LargestInFront;
};

#include "Heap.hpp"

#endif