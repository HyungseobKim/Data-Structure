/* -------------------------------------------------------------
File Name: vector.h
Purpose: Header file for vector class and vector proxy class.
Platform: gcc 5.4.0, No hardware requirements, All operating systems
Author: Hyungseob Kim
Creation date: 10/13/2018
----------------------------------------------------------------*/

#include <iostream>

namespace CS225
{
	struct ElementNode {
		int data;
		int pos;
		struct ElementNode *next;
	};

	//forward declaration
	class ElementProxy;

	class SparseVector {
		
	public:
		// Constructor & Destructor
		SparseVector();
		SparseVector(const SparseVector& v);
		~SparseVector();
	
		// Basic functionallity
		int Get(long pos) const;
		void Insert(int val, long pos);
		void Delete(long pos);
		
		void PrintRaw () const {
			ElementNode* curr = pHead;
			
			std::cout << "Raw vector: ";
			while (curr) {
				std::cout << "(" << curr->data << ", " << curr->pos << ")";
				curr = curr->next;
			}
			std::cout << std::endl;
		}
		
		friend std::ostream& operator<<(std::ostream &out, const SparseVector&v);
		
		// Operator functions
		ElementProxy operator[](long pos);
		int operator[](long pos) const;
		
		SparseVector operator+(const SparseVector& v) const;
		
		SparseVector operator*(int val) const;
		int operator*(SparseVector v) const;
		
		SparseVector& operator=(const SparseVector& v);
	
	private:
		ElementNode* pHead;
		long dimension;
		
		void DeleteAll();
	};

	class ElementProxy {
		
	public:
		ElementProxy(SparseVector& v, long pos);
		operator int() const;
		
		ElementProxy& operator=(int val);
		ElementProxy& operator=(const ElementProxy& p);
		
		ElementProxy& operator+=(int val);
		ElementProxy& operator-=(int val);
		
	private:
		SparseVector &v_;
		long pos_;
	};
	
	SparseVector operator*(int val, SparseVector v);
}
