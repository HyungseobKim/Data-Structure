#ifndef HEAP_HPP
#define HEAP_HPP
/*------------------------------------------------------------------------
File Name: Heap.hpp
Purpose: Implementation for methods of Heap class.
Author: Kim Hyungseob
Created: 5/24
------------------------------------------------------------------------*/
#include <iostream>

#include "Heap.h"

// ------------------------ Public methods ------------------------
template<typename T>
Heap<T>::~Heap()
{
	delete[] m_data;
}

template<typename T>
void Heap<T>::Print() const
{
	if (!m_size)
	{
		std::cout << "Heap is empty." << std::endl;
		return;
	}

	int coutWidth = 1;
	while (coutWidth <= m_size)
		coutWidth *= 2;

	std::cout.width(coutWidth/2);
	std::cout << ' ';

	unsigned int width = 1;

	for (unsigned int index = 0; index < m_size; index++)
	{
		std::cout << m_data[index];
		std::cout.width(coutWidth - 1);
		std::cout << ' ';

		if (index == width - 1)
		{
			std::cout << std::endl;
			width = width * 2 + 1;
			coutWidth /= 2;
			std::cout.width(coutWidth / 2);
			std::cout << ' ';
		}
	}

	std::cout << std::endl << "Number of items: " << m_size << std::endl;
}

template<typename T>
void Heap<T>::Insert(T value)
{
	if (m_size == m_capacity) Grow();

	m_data[m_size] = value;
	m_size++;

	Sort();
}

template<typename T>
void Heap<T>::Remove(unsigned int index)
{
	if (index >= m_size)
	{
		std::cout << "Invalid index" << std::endl;
		return;
	}

	m_size--;
	m_data[index] = m_data[m_size];

	if (m_LargestInFront)
		SwapLargestAtFront(m_data, m_size, index);
	else
		SwapSmallestAtFront(m_data, m_size, index);
}

template<typename T>
void Heap<T>::Heapify()
{
	Heapify(m_data, m_size);
}

template<typename T>
void Heap<T>::Sort()
{
	for (int offset = 0; offset < m_size - 1; offset++)
	{
		Heapify(m_data + offset, m_size - offset);
	}
}

template<typename T>
void Heap<T>::Reverse()
{
	m_LargestInFront = !m_LargestInFront;
	Heapify();
}

template<typename T>
void Heap<T>::SetArray(const T* data, size_t size)
{
	while (m_capacity < size) Grow();

	for (unsigned int index = 0; index < size; index++)
		m_data[index] = data[index];

	m_size = size;
}

// ------------------------ Private methods ------------------------
template<typename T>
void Heap<T>::Heapify(T* data, size_t size)
{
	if (size < 2) return;

	int curr = static_cast<int>(size) / 2 - 1;//GetParent(static_cast<unsigned int>(size) - 1);

	if (m_LargestInFront)
	{
		for (; curr >= 0; curr--)
			SwapLargestAtFront(data, size, curr);
	}
	else
	{
		for (; curr >= 0; curr--)
			SwapSmallestAtFront(data, size, curr);
	}
}

template<typename T>
void Heap<T>::SwapLargestAtFront(T* data, size_t size, unsigned int index)
{
	unsigned int left = GetLeft(index);
	if (left >= size) return;

	unsigned int right = left + 1;
	if (right >= size)
	{
		if (data[left] > data[index])
			Swap(data, index, left);
		return;
	}

	unsigned int larger = left;

	if (data[left] < data[right])
		larger = right;

	if (data[index] >= data[larger])
		return;

	Swap(data, index, larger);
	SwapLargestAtFront(data, size, larger);
}

template<typename T>
void Heap<T>::SwapSmallestAtFront(T* data, size_t size, unsigned int index)
{
	unsigned int left = GetLeft(index);
	if (left >= size) return;

	unsigned int right = left + 1;
	if (right >= size)
	{
		if (data[left] < data[index])
			Swap(data, index, left);
		return;
	}

	unsigned int smaller = left;

	if (data[left] > data[right])
		smaller = right;

	if (data[index] <= data[smaller])
		return;

	Swap(data, index, smaller);
	SwapSmallestAtFront(data, size, smaller);
}

template<typename T>
void Heap<T>::Grow()
{
	m_capacity *= 2;
	T* new_data = new T[m_capacity];

	for (int index = 0; index < m_size; index++)
		new_data[index] = m_data[index];

	delete[] m_data;
	m_data = new_data;
}

// ------------------------ Helper functions ------------------------
template<typename T>
void Heap<T>::Swap(T* data, unsigned int index1, unsigned int index2)
{
	T temp = data[index1];
	data[index1] = data[index2];
	data[index2] = temp;
}

template<typename T>
unsigned int Heap<T>::GetLeft(unsigned int index) const
{
	return index * 2 + 1;
}

template<typename T>
unsigned int Heap<T>::GetParent(unsigned int index) const
{
	return (index - 1) / 2;
}

#endif