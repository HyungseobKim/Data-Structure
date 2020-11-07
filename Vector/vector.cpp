/* -------------------------------------------------------------
File Name: vector.cpp
Purpose: Function implements for vector class and vector proxy class.
Platform: gcc 5.4.0, No hardware requirements, All operating systems
Author: Hyungseob Kim
Creation date: 10/13/2018
----------------------------------------------------------------*/

#include "vector.h"

namespace CS225
{
	/* this is the only place where dimension is used */
	std::ostream& operator<<(std::ostream &out, const SparseVector &v) {
		int i,last_pos=-1; 
		ElementNode* p_e=v.pHead; 
		while (p_e) { 
			for (i=last_pos+1;i<p_e->pos;++i) out << " " << "0"; 
			out << " " << p_e->data; 
			last_pos=p_e->pos; 
			p_e = p_e->next; 
		} 
		for (i=last_pos+1;i<v.dimension;++i) out << " " << "0"; 

		return out; 
	}

	SparseVector::SparseVector()
		: pHead(nullptr), dimension(0)
	{
	}
	
	SparseVector::SparseVector(const SparseVector& v)
		: pHead(nullptr), dimension(0)
	{
		ElementNode* head = v.pHead;
		while (head)
		{
			Insert(head->data, head->pos);
			head = head->next;
		}
	}
	
	SparseVector::~SparseVector()
	{
		DeleteAll();
	}
	
	void SparseVector::DeleteAll()
	{
		while (pHead)
		{
			ElementNode* next = pHead->next;
			delete pHead;
			pHead = next;
		}
	}
	
	int SparseVector::Get(long pos) const
	{
		if (!pHead)
			return 0;
		
		if (pos == pHead->pos)
			return pHead->data;
		else if (pos < pHead->pos)
			return 0;
		
		ElementNode* head = pHead;
		
		while (head->next)
		{
			ElementNode* next = head->next;
			
			if (pos == next->pos)
				return next->data;
			else if (pos < next->pos)
				return 0;
			
			head = next;
		}
		
		return 0;
	}

	void SparseVector::Insert(int val, long pos) {
		
		if (!val) 
		{ 
			Delete(pos); 
			return; 
		}
		
		if (pos >= dimension)
			dimension = pos+1;
		
		ElementNode* head = pHead;
		
		if (!head)
		{
			pHead = new ElementNode;
			pHead->pos = pos;
			pHead->data = val;
			pHead->next = 0;
			
			return;
		}
		
		if (pos == head->pos)
		{
			head->data = val;
			return;
		}
		else if (pos < head->pos)
		{
			pHead = new ElementNode;
			pHead->pos = pos;
			pHead->data = val;
			pHead->next = head;
			
			return;
		}
		
		while (head->next)
		{
			ElementNode* next = head->next;
			
			if (pos == next->pos)
			{
				next->data = val;
				return;
			}
			else if (pos < next->pos)
			{
				head->next = new ElementNode;
				head->next->pos = pos;
				head->next->data = val;
				head->next->next = next;
				
				return;
			}
			
			head = next;
		}
		
		head->next = new ElementNode;
		head->next->pos = pos;
		head->next->data = val;
		head->next->next = 0;
	}

	void SparseVector::Delete(long pos) {
		
		if (!pHead)
			return;
		
		if (pos == pHead->pos)
		{
			ElementNode* next = pHead->next;
			delete pHead;
			pHead = next;
			
			return;
		}
		else if (pos < pHead->pos)
			return;
		
		ElementNode* head = pHead;
		while (head->next)
		{
			ElementNode* next = head->next;
			
			if (pos == next->pos)
			{
				head->next = next->next;
				delete next;
				return;
			}
			else if (pos < next->pos)
				return;
			
			head = next;
		}
	}
	
	ElementProxy SparseVector::operator[](long pos)
	{
		return ElementProxy(*this, pos);
	}
	
	int SparseVector::operator[](long pos) const
	{
		return Get(pos);
	}
	
	SparseVector SparseVector::operator+(const SparseVector& v) const
	{
		SparseVector result;
		ElementNode* head = pHead;
		ElementNode* rhsHead = v.pHead;
		
		while (head || rhsHead)
		{
			if (!rhsHead)
			{
				result.Insert(head->data, head->pos);
				head = head->next;
			}
			else if (!head)
			{
				result.Insert(rhsHead->data, rhsHead->pos);
				rhsHead = rhsHead->next;
			}
			else if (head->pos == rhsHead->pos)
			{
				result.Insert(head->data + rhsHead->data, head->pos);
				head = head->next;
				rhsHead = rhsHead->next;
			}
			else if (head->pos < rhsHead->pos)
			{
				result.Insert(head->data, head->pos);
				head = head->next;
			}
			else if (head->pos > rhsHead->pos)
			{
				result.Insert(rhsHead->data, rhsHead->pos);
				rhsHead = rhsHead->next;
			}
		}
		
		return result;
	}
	
	SparseVector SparseVector::operator*(int val) const
	{
		SparseVector result;
		ElementNode* head = pHead;
		
		while (head)
		{
			result.Insert(head->data * val, head->pos);
			head = head->next;
		}
		
		return result;
	}
	
	SparseVector operator*(int val, SparseVector v)
	{
		return v*val;
	}
	
	int SparseVector::operator*(SparseVector v) const
	{
		int result = 0;
		ElementNode* head = pHead;
		
		while (head)
		{
			result += head->data * v.Get(head->pos);
			head = head->next;
		}
		
		return result;
	}
	
	SparseVector& SparseVector::operator=(const SparseVector& v)
	{
		if (pHead == v.pHead)
			return *this;
		
		DeleteAll();
		ElementNode* head = v.pHead;
		
		while (head)
		{
			Insert(head->data, head->pos);
			head = head->next;
		}
		
		return *this;
	}
	
	/***************** Methods for proxy ******************/
	
	ElementProxy::ElementProxy(SparseVector& v, long pos)
		: v_(v), pos_(pos)
	{
	}
	
	ElementProxy::operator int() const
	{
		return v_.Get(pos_);
	}
	
	ElementProxy& ElementProxy::operator=(int val)
	{
		v_.Insert(val, pos_);
		return *this;
	}
	
	ElementProxy& ElementProxy::operator=(const ElementProxy& p)
	{
		v_.Insert(p, pos_);
		return *this;
	}
	
	ElementProxy& ElementProxy::operator+=(int val)
	{
		v_.Insert(v_.Get(pos_) + val, pos_);
		return *this;
	}
	
	ElementProxy& ElementProxy::operator-=(int val)
	{
		v_.Insert(v_.Get(pos_) - val, pos_);
		return *this;
	}
}