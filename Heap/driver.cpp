/*------------------------------------------------------------------------
File Name: driver.cpp
Purpose: Tests for heap.
Author: Kim Hyungseob
Created: 5/24
------------------------------------------------------------------------*/
#include <iostream>
#include <time.h>

#include "Heap.h"

// heapifying an array (largest in front)
void Test1()
{
	std::cout << "================= Test1 =================" << std::endl;

	std::cout << std::endl << "[Array with random numbers]" << std::endl;
	int data[10] = { 5, 3, 2, 6, 9, 1, 7, 0, 8, 4 };

	Heap<int> heap;

	heap.SetArray(data, 10);
	heap.Print();
	std::cout << std::endl;

	std::cout << "[Heapifying an array : Largest in front]" << std::endl;
	heap.Heapify();
	heap.Print();
	std::cout << std::endl;
}

// reverse heapifying an array (smallest in front)
void Test2()
{
	std::cout << "================= Test2 =================" << std::endl;

	std::cout << std::endl << "[Array with random numbers]" << std::endl;
	int data[10] = { 8, 1, 2, 7, 0, 5, 4, 6, 3, 9 };

	Heap<int> heap(false);

	heap.SetArray(data, 10);
	heap.Print();
	std::cout << std::endl;

	std::cout << "[Heapifying an array : Smallest in front]" << std::endl;
	heap.Heapify();
	heap.Print();
	std::cout << std::endl;
}

// heap sort an array
void Test3()
{
	std::cout << "================= Test3 =================" << std::endl;

	std::cout << std::endl << "[Array with random numbers]" << std::endl;
	int data[10] = { 7, 1, 5, 0, 6, 3, 8, 4, 9, 2 };

	Heap<int> heap;

	heap.SetArray(data, 10);
	heap.Print();
	std::cout << std::endl;

	std::cout << "[Sorting an array : Largest in front]" << std::endl;
	heap.Sort();
	heap.Print();
	std::cout << std::endl;
}

// heap sort an array using the reverse heap
void Test4()
{
	std::cout << "================= Test4 =================" << std::endl;

	std::cout << std::endl << "[Array with random numbers]" << std::endl;
	int data[10] = { 4, 1, 7, 9, 3, 0, 6, 2, 5, 8 };

	Heap<int> heap(false);

	heap.SetArray(data, 10);
	heap.Print();
	std::cout << std::endl;

	std::cout << "[Sorting an array : Smallest in front]" << std::endl;
	heap.Sort();
	heap.Print();
	std::cout << std::endl;
}

// heapify from a reverse heap to a standard heap
void Test5()
{
	std::cout << "================= Test5 =================" << std::endl;

	Heap<int> heap(false);

	std::cout << "[Make reverse heap]" << std::endl;
	for (int i = 9; i >= 0; i--)
		heap.Insert(i);

	heap.Print();
	std::cout << std::endl;

	std::cout << "[Heapify to a standard heap]" << std::endl;
	heap.Reverse();
	heap.Print();
	std::cout << std::endl;
}

// Insert an item into heap
void Test6()
{
	std::cout << "================= Test6 =================" << std::endl;

	Heap<int> heap;

	for (int i = 0; i < 10; i++)
	{
		std::cout << "[Insert " << i << "]" << std::endl;
		heap.Insert(i);
		heap.Print();
		std::cout << std::endl;
	}
}

// Remove an item from heap
void Test7()
{
	std::cout << "================= Test7 =================" << std::endl;

	Heap<int> heap;

	for (int i = 0; i < 10; i++)
		heap.Insert(i);

	heap.Print();
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		unsigned int index = rand() % 10;

		std::cout << "[Remove " << index << "]" << std::endl;
		heap.Remove(index);
		heap.Print();
		std::cout << std::endl;
	}
}

// Insert an item into reverse heap
void Test8()
{
	std::cout << "================= Test8 =================" << std::endl;

	Heap<int> heap(false);

	for (int i = 9; i >= 0; i--)
	{
		std::cout << "[Insert " << i << "]" << std::endl;
		heap.Insert(i);
		heap.Print();
		std::cout << std::endl;
	}
}

// Remove an item from reverse heap
void Test9()
{
	std::cout << "================= Test9 =================" << std::endl;

	Heap<int> heap(false);

	for (int i = 9; i >= 0; i--)
		heap.Insert(i);

	heap.Print();
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		unsigned int index = rand() % 10;

		std::cout << "[Remove " << index << "]" << std::endl;
		heap.Remove(index);
		heap.Print();
		std::cout << std::endl;
	}
}

// heapify from a standard heap to a reverse heap
void Test10()
{
	std::cout << "================= Test10 =================" << std::endl;

	Heap<int> heap;

	std::cout << "[Make standard heap]" << std::endl;
	for (int i = 0; i < 10; i++)
		heap.Insert(i);

	heap.Print();
	std::cout << std::endl;

	std::cout << "[Heapify to a reverse heap]" << std::endl;
	heap.Reverse();
	heap.Print();
	std::cout << std::endl;
}

// Insert Duplicate
void Test11()
{
	std::cout << "================= Test11 =================" << std::endl;

	Heap<int> heap;

	for (int i = 0; i < 10; i++)
		heap.Insert(i);

	heap.Print();
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::cout << "[Insert " << i << "]" << std::endl;
		heap.Insert(i);
		heap.Print();
		std::cout << std::endl;
	}
}

// Insert char into heap
void Test12()
{
	std::cout << "================= Test12 =================" << std::endl;

	Heap<char> heap;

	for (char i = 'A'; i <= 'Z'; i++)
	{
		std::cout << "[Insert " << i << "]" << std::endl;
		heap.Insert(i);
		heap.Print();
		std::cout << std::endl;
	}
}

// Insert double into reverse heap
void Test13()
{
	std::cout << "================= Test13 =================" << std::endl;

	Heap<double> heap(false);

	for (double i = 9.9; i >= 0; i -= 1.1)
	{
		std::cout << "[Insert " << i << "]" << std::endl;
		heap.Insert(i);
		heap.Print();
		std::cout << std::endl;
	}
}

// Struct for test 14
struct Weapon
{
	static int new_id;
	int m_id;
	int m_power;

	Weapon() : m_id(0), m_power(0) {}
	Weapon(int power)
		: m_id(new_id), m_power(power)
	{
		++new_id;
	}

	friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);
	bool operator<(const Weapon& weapon)
	{
		return m_power < weapon.m_power;
	}
	bool operator>(const Weapon& weapon)
	{
		return m_power > weapon.m_power;
	}
	bool operator<=(const Weapon& weapon)
	{
		return m_power <= weapon.m_power;
	}
	bool operator>=(const Weapon& weapon)
	{
		return m_power >= weapon.m_power;
	}
	Weapon& operator=(const Weapon& weapon)
	{
		m_id = weapon.m_id;
		m_power = weapon.m_power;
		return *this;
	}
};

std::ostream& operator<<(std::ostream& os, const Weapon& weapon)
{
	os << "(" << weapon.m_id << "," << weapon.m_power << ")";
	return os;
}

int Weapon::new_id = 0;

// Insert custom type to heap
void Test14()
{
	std::cout << "================= Test14 =================" << std::endl;

	srand(static_cast<unsigned int>(time(NULL)));
	constexpr int Max_Power = 100;

	Heap<Weapon> heap;

	for (int i = 0; i < 10; i++)
	{
		int power = rand() % Max_Power;

		std::cout << "[Insert " << power << "]" << std::endl;
		heap.Insert(Weapon(power));
		heap.Print();
		std::cout << std::endl;
	}
}

// Many many
void Test15()
{
	std::cout << "================= Test15 =================" << std::endl;

	Heap<int> heap;

	for (int i = 0; i < 100; i++)
		heap.Insert(i);

	heap.Print();
	std::cout << std::endl;

	for (int i = 0; i < 100; i++)
		heap.Remove(0);

	heap.Print();
	std::cout << std::endl;
}

int main(void)
{
	int test = 0;

	switch (test)
	{
	case 1:
		Test1();
		break;

	case 2:
		Test2();
		break;

	case 3:
		Test3();
		break;

	case 4:
		Test4();
		break;

	case 5:
		Test5();
		break;

	case 6:
		Test6();
		break;

	case 7:
		Test7();
		break;

	case 8:
		Test8();
		break;

	case 9:
		Test9();
		break;

	case 10:
		Test10();
		break;

	case 11:
		Test11();
		break;

	case 12:
		Test12();
		break;

	case 13:
		Test13();
		break;

	case 14:
		Test14();
		break;

	case 15:
		Test15();
		break;

	default:
		Test1();
		Test2();
		Test3();
		Test4();
		Test5();
		Test6();
		Test7();
		Test8();
		Test9();
		Test10();
		Test11();
		Test12();
		Test13();
		Test14();
		Test15();
	}

	system("pause");

	return 0;
}