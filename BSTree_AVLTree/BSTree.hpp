/*------------------------------------------------------------------------
File Name: BSTree.cpp
Purpose: Implementation for Binary Search tree.
Author: Kim Hyungseob
Created: 5/10
------------------------------------------------------------------------*/
#include <string>
#include <queue>

#include "BSTree.h"

const char *ReadableType(const char *name) {
	if(std::strstr(name, "AVL"))
		return "AVLTree";
	else
		return "BSTree";
}

template<typename T>
void BSTree<T>::DebugPrint(bool showCounts) const {
	std::vector<BinTreeNode*> printQueue;

	if(root != nullptr) {
		std::cout << "type: " << ReadableType(typeid(T).name( )) << ", height: " << root->Height( );
		std::cout << ", nodes: " << root->count << std::endl;

		// Populate printQueue
		unsigned int queueIndex;
		unsigned int offset = 0;

		unsigned int width = 1;
		const unsigned int height = root->Height();

		printQueue.push_back(root);

		for (unsigned int row = 0; row < height; row++)
		{
			for (queueIndex = 0; queueIndex < width; queueIndex++)
			{
				if (!printQueue[offset + queueIndex])
				{
					printQueue.push_back(nullptr);
					printQueue.push_back(nullptr);
					continue;
				}

				if (BinTreeNode* left = printQueue[offset + queueIndex]->left) printQueue.push_back(left);
				else printQueue.push_back(nullptr);

				if (BinTreeNode* right = printQueue[offset + queueIndex]->right) printQueue.push_back(right);
				else printQueue.push_back(nullptr);
			}

			offset += width;
			width *= 2;
		}

		int nodeRowCount = 0;
		int nodeRowTarget = 1;
		int coutWidth = 2 << root->Height( );
		std::cout.width(coutWidth / 2);
		std::cout << ' ';
		// first node of each row should have a 1/2 width offset
		for(queueIndex = 0; queueIndex < printQueue.size( ); queueIndex++) {
			if(printQueue[queueIndex] != nullptr) {
				std::cout << printQueue[queueIndex]->data;
				std::cout.width(coutWidth - 1);
				std::cout << ' ';
			} else {
				std::cout << "X";
				std::cout.width(coutWidth - 1);
				std::cout << ' ';
			}

			if(++nodeRowCount == nodeRowTarget) {
				std::cout << std::endl;
				nodeRowTarget *= 2;
				coutWidth /= 2;
				nodeRowCount = 0;
				std::cout.width(coutWidth / 2);
				std::cout << ' ';
				// first node of each row should have a 1/2 width offset
			}
		}
		if(showCounts) {
			for(queueIndex = 0; queueIndex < printQueue.size( ); queueIndex++) {
				if(printQueue[queueIndex] != nullptr) {
					std::cout << printQueue[queueIndex]->data << "(" << printQueue[queueIndex]->count << ")  ";
				}
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	} else {
		std::cout << "Tree is Empty" << std::endl;
	}
}

template<typename T>
inline BSTree<T>::BSTree() : root(nullptr) {
}

template<typename T>
BSTree<T>::BSTree(const BSTree & rhs) : root(nullptr) {
	root = CopyTree(rhs.root);
}

template<typename T>
BSTree<T>::~BSTree( ) {
	Clear();
}

template<typename T>
BSTree<T> & BSTree<T>::operator=(const BSTree & rhs) {
	root = rhs.root;
	return *this;
}

template<typename T>
void BSTree<T>::Insert(const T & value) {
	if (root)
	{
		root->Insert(value);
		return;
	}
	root = new BinTreeNode(value);
}

template<typename T>
void BSTree<T>::Remove(const T & value) {
	if (!Find(value)) return;
	if (value == root->data)
	{
		if (root->count == 1)
		{
			delete root;
			root = nullptr;
			return;
		}

		BinTreeNode* left = root->left;
		BinTreeNode* right = root->right;

		if (!right)
		{
			delete root;
			root = left;

			return;
		}

		if (!left)
		{
			delete root;
			root = right;

			return;
		}

		T copy = left->IndexOf(left->count - 1).data;
		RemoveRecurs(root, copy);
		root->data = copy;
		return;
	}
	RemoveRecurs(root, value);
}


template<typename T>
void BSTree<T>::Clear( ) {
	if (!root) return;

	root->FreeTree();
	delete root;
	root = nullptr;
}

template<typename T>
bool BSTree<T>::Empty(void) const {
	return root == nullptr;
}

template<typename T>
unsigned int BSTree<T>::Size( ) const {
	if (!root) return 0;
	return root->count;
}

template<typename T>
int BSTree<T>::Height(void) const {
	if (!root) return 0;
	return root->Height();
}

template<typename T>
bool BSTree<T>::Find(const T & value) const {
	if (!root) return false;
	return root->Find(value);
}

template<typename T>
bool BSTree<T>::RemoveRecurs(BSTree<T>::BinTreeNode *&treePtr, const T & value) {
	--treePtr->count;

	if (BinTreeNode* left = treePtr->left)
	{
		if (value == left->data)
		{
			if (left->count == 1)
			{
				delete left;
				treePtr->left = nullptr;
				return true;
			}

			if (!left->right)
			{
				treePtr->left = left->left;
				delete left;
				return true;
			}

			if (!left->left)
			{
				treePtr->left = left->right;
				delete left;
				return true;
			}

			T copy = left->left->IndexOf(left->left->count - 1).data;
			RemoveRecurs(left, copy);
			left->data = copy;
			return true;
		}

		if (value < treePtr->data)
		{
			RemoveRecurs(left, value);
			return true;
		}
	}

	BinTreeNode* right = treePtr->right;

	if (value == right->data)
	{
		if (right->count == 1)
		{
			delete right;
			treePtr->right = nullptr;
			return true;
		}

		if (!right->right)
		{
			treePtr->right = right->left;
			delete right;
			return true;
		}

		if (!right->left)
		{
			treePtr->right = right->right;
			delete right;
			return true;
		}

		T copy = right->left->IndexOf(right->left->count - 1).data;
		RemoveRecurs(right, copy);
		right->data = copy;
		return true;
	}

	if(RemoveRecurs(right, value)) return true;
	return false;
}

template<typename T>
const typename BSTree<T>::BinTreeNode& BSTree<T>::operator[](int index) const {
	return root->IndexOf(index);
}

template<typename T>
typename BSTree<T>::BinTreeNode * BSTree<T>::CopyTree(BSTree<T>::BinTreeNode * source) {
	if (source == root) return root;
	Clear();
	
	std::queue<BinTreeNode*> queue;
	queue.push(source);
	
	while (!queue.empty())
	{
		BinTreeNode* curr = queue.front();
		queue.pop();

		Insert(curr->data);

		if (BinTreeNode* left = curr->left) queue.push(left);
		if (BinTreeNode* right = curr->right) queue.push(right);
	}

	return root;
}

// Node methods
template<typename T>
void BSTree<T>::BinTreeNode::FreeTree() {
	if (left)
	{
		left->FreeTree();
		delete left;
		left = nullptr;
	}
	if (right)
	{
		right->FreeTree();
		delete right;
		right = nullptr;
	}
}

template<typename T>
const typename BSTree<T>::BinTreeNode& BSTree<T>::BinTreeNode::IndexOf(int index) const {

	if (left)
	{
		const int count = static_cast<int>(left->count);

		if (index == count) return *this;
		if (index < count) return left->IndexOf(index);
		return right->IndexOf(index - count - 1);
	}
	else
	{
		if (index == 0) return *this;
	}

	return right->IndexOf(index - 1);
}

template <typename T>
void BSTree<T>::BinTreeNode::Insert(const T &value) {
	if (value == data) return;
	++count;

	if (value < data)
	{
		if (!left)
		{
			left = new BinTreeNode(value);
			return;
		}
		left->Insert(value);
	}
	else
	{
		if (!right)
		{
			right = new BinTreeNode(value);
			return;
		}
		right->Insert(value);
	}
}

template <typename T>
int BSTree<T>::BinTreeNode::Height() const {
	if (!left && !right) return 0;

	int result = 0;

	if (left) result = left->Height();
	if (right && right->Height() > result) result = right->Height();

	return result + 1;
}

template<typename T>
inline bool BSTree<T>::BinTreeNode::Find(const T & value) {
	if (value == data) return true;
	
	if (value < data)
	{
		if (!left) return false;
		if (left->Find(value)) return true;
	}
	else
	{
		if (!right) return false;
		if (right->Find(value)) return true;
	}

	return false;
}