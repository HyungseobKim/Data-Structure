/*------------------------------------------------------------------------
File Name: RopeTree.cpp
Purpose: Implementation for RopeTree.
Author: Kim Hyungseob
Created: 5/10
------------------------------------------------------------------------*/
#include "RopeTree.h"

#define MAXIMUM 4

// Rope Tree methods
RopeTree::RopeTree(std::string text)
{
	m_root = new RopeNode(text.size());
	m_root->m_left = new RopeNode(text);
}

RopeTree::~RopeTree() { Clear(); }

char RopeTree::operator[](int index) const
{
	if (index >= m_root->m_weight) return ' ';
	return m_root->Find(index);
}

RopeTree& RopeTree::operator+=(RopeTree& tree)
{
	RopeNode* new_root = new RopeNode(Size() + tree.Size());

	m_root->m_right = tree.m_root;
	new_root->m_left = m_root;
	m_root = new_root;

	tree.m_root = nullptr;
	
	return *this;
}

RopeTree& RopeTree::operator+=(RopeTree&& tree)
{
	RopeNode* new_root = new RopeNode(Size() + tree.Size());

	m_root->m_right = tree.m_root;
	new_root->m_left = m_root;
	m_root = new_root;

	tree.m_root = nullptr;

	return *this;
}

unsigned int RopeTree::Size() const { return m_root->m_weight; }

void RopeTree::Clear() 
{
	if (m_root)
	{
		delete m_root;
		m_root = nullptr;
	}
}

// Rope Node methods
RopeTree::RopeNode::RopeNode(unsigned int weight) : m_weight(weight) {}

RopeTree::RopeNode::RopeNode(std::string text)
{
	const size_t size = text.size();
	if (size <= MAXIMUM)
	{
		m_text = text;
		return;
	}

	const size_t half = size / 2;
	m_weight = half;

	m_left = new RopeNode(text.substr(0, half));
	m_right = new RopeNode(text.substr(half, size - half));
}

RopeTree::RopeNode::~RopeNode()
{
	if (m_left)
	{
		delete m_left;
		m_left = nullptr;
	}
	if (m_right)
	{
		delete m_right;
		m_right = nullptr;
	}
}

char RopeTree::RopeNode::Find(unsigned int index) const
{
	if (!m_weight)
	{
		if (m_right) return m_right->Find(index);
		return m_text[index];
	}

	if (index < m_weight) return m_left->Find(index);

	return m_right->Find(index - m_weight);
}

// Friend method
std::ostream& operator<<(std::ostream& os, const RopeTree& tree)
{
	const unsigned int size = tree.Size();

	for (unsigned int index = 0; index < size; index++)
		os << tree[index];
	return os;
}