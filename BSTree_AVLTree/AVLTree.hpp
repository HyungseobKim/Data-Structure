/*------------------------------------------------------------------------
File Name: AVLTree.hpp
Purpose: Implementation for AVL tree.
Author: Kim Hyungseob
Created: 5/10
------------------------------------------------------------------------*/
#include <string>
#include <stack>

#include "BSTree.h"
#include "AVLTree.h"

template<typename T>
inline AVLTree<T>::AVLTree(void) : BSTree<T>::BSTree() {
}

template<typename T>
AVLTree<T>::~AVLTree() {
}

template<typename T>
void AVLTree<T>::Insert(const T & value) {
	if (BSTree<T>::Find(value)) return;

	if (!BSTree<T>::root)
	{
		BSTree<T>::root = new typename BSTree<T>::BinTreeNode(value);
		return;
	}

	if (!BSTree<T>::root->left && value < BSTree<T>::root->data)
	{
		++BSTree<T>::root->count;
		BSTree<T>::root->left = new typename BSTree<T>::BinTreeNode(value);
		return;
	}

	if (!BSTree<T>::root->right && value > BSTree<T>::root->data)
	{
		++BSTree<T>::root->count;
		BSTree<T>::root->right = new typename BSTree<T>::BinTreeNode(value);
		return;
	}

	std::stack<typename BSTree<T>::BinTreeNode**> stack;
	stack.push(&(BSTree<T>::root));

	while (true)
	{
		typename BSTree<T>::BinTreeNode*& curr = *stack.top();
		
		++curr->count;

		if (value < curr->data)
		{
			typename BSTree<T>::BinTreeNode*& left = curr->left;

			if (!left)
			{
				Insert(curr, value, stack);
				return;
			}

			stack.push(&curr->left);
			continue;
		}

		typename BSTree<T>::BinTreeNode*& right = curr->right;

		if (!right)
		{
			Insert(curr, value, stack);
			return;
		}

		stack.push(&curr->right);
	}
}

template<typename T>
void AVLTree<T>::Remove(const T & value) {
	if (!BSTree<T>::Find(value)) return;

	std::stack<typename BSTree<T>::BinTreeNode**> stack;
	stack.push(&(BSTree<T>::root));

	if (value == BSTree<T>::root->data)
	{
		if (BSTree<T>::root->count == 1)
		{
			delete BSTree<T>::root;
			BSTree<T>::root = nullptr;
			return;
		}

		typename BSTree<T>::BinTreeNode* left = BSTree<T>::root->left;
		typename BSTree<T>::BinTreeNode* right = BSTree<T>::root->right;

		if (!right)
		{
			delete BSTree<T>::root;
			BSTree<T>::root = left;
			return;
		}

		if (!left)
		{
			delete BSTree<T>::root;
			BSTree<T>::root = right;
			return;
		}

		if (!left->right)
		{
			BSTree<T>::root->data = left->data;
			typename BSTree<T>::BinTreeNode* temp = left->left;
			delete BSTree<T>::root->left;
			BSTree<T>::root->left = temp;
		}
		else
		{
			stack.push(&BSTree<T>::root->left);

			while (true)
			{
				typename BSTree<T>::BinTreeNode*& target = *stack.top();

				if (!target->right->right)
					break;
				else
					stack.push(&target->right);
			}

			typename BSTree<T>::BinTreeNode*& target = *stack.top();
			BSTree<T>::root->data = target->right->data;
			Remove(target, target->right->data, stack);
			return;
		}
	}

	while (true)
	{
		typename BSTree<T>::BinTreeNode*& curr = *stack.top();
		
		if (value < curr->data)
		{
			typename BSTree<T>::BinTreeNode*& left = curr->left;

			if (value == left->data)
			{
				Remove(curr, value, stack);
				return;
			}

			stack.push(&left);
			continue;
		}

		typename BSTree<T>::BinTreeNode*& right = curr->right;

		if (value == right->data)
		{
			Remove(curr, value, stack);
			return;
		}

		stack.push(&right);
	}
}

template <typename T>
void AVLTree<T>::Insert(typename BSTree<T>::BinTreeNode *&tree, const T& value, std::stack<typename BSTree<T>::BinTreeNode**>& nodes) {
	if (value < tree->data)
		tree->left = new typename BSTree<T>::BinTreeNode(value);
	else
		tree->right = new typename BSTree<T>::BinTreeNode(value);

	while (!nodes.empty())
	{
		typename BSTree<T>::BinTreeNode*& curr = *nodes.top();

		typename BSTree<T>::BinTreeNode* left = curr->left;
		typename BSTree<T>::BinTreeNode* right = curr->right;

		if (!left && !right) return;

		if ((!left && right->Height() > 0) || (left && right && right->Height() > left->Height() + 1))
		{
			if (right && right->left && (!right->right || right->right->Height() < right->left->Height()))
			{
				nodes.push(&curr->right);
				Balance(nodes, false);
			}
			else
				Balance(nodes, true);

			return;
		}
		if ((!right && left->Height() > 0) || (left && right && left->Height() > right->Height() + 1))
		{
			if (left && left->right && (!left->left || left->left->Height() < left->right->Height()))
			{
				nodes.push(&curr->left);
				Balance(nodes, false);
			}
			else
				Balance(nodes, true);

			return;
		}

		nodes.pop();
	}
}

template <typename T>
void AVLTree<T>::Remove(typename BSTree<T>::BinTreeNode *&treePtr, const T& value, std::stack<typename BSTree<T>::BinTreeNode **>& nodes) {
	
	if (treePtr->left && treePtr->left->data == value)
	{
		typename BSTree<T>::BinTreeNode* left = treePtr->left;

		if (left->count == 1)
		{
			delete left;
			treePtr->left = nullptr;
		}
		else if (!left->right)
		{
			treePtr->left = left->left;
			delete left;
		}
		else if (!left->left)
		{
			treePtr->left = left->right;
			delete left;
		}
		else
		{
			nodes.push(&treePtr->left);

			if (!left->left->right)
			{
				typename BSTree<T>::BinTreeNode* temp = left->left->left;
				left->data = left->left->data;
				delete left->left;
				left->left = temp;
			}
			else
			{
				nodes.push(&treePtr->left->left);

				while (true)
				{
					typename BSTree<T>::BinTreeNode*& target = *nodes.top();

					if (!target->right->right)
						break;
					else
						nodes.push(&target->right);
				}

				typename BSTree<T>::BinTreeNode*& target = *nodes.top();

				typename BSTree<T>::BinTreeNode* temp = target->right->left;
				left->data = target->right->data;
				delete target->right;
				target->right = temp;
			}
		}
	}
	else
	{
		typename BSTree<T>::BinTreeNode* right = treePtr->right;

		if (right->count == 1)
		{
			delete right;
			treePtr->right = nullptr;
		}
		else if (!right->right)
		{
			treePtr->right = right->left;
			delete right;
		}
		else if (!right->left)
		{
			treePtr->right = right->right;
			delete right;
		}
		else
		{
			nodes.push(&treePtr->right);

			if (!right->left->right)
			{
				typename BSTree<T>::BinTreeNode* temp = right->left->left;
				right->data = right->left->data;
				delete right->left;
				right->left = temp;
			}
			else
			{
				nodes.push(&treePtr->right->left);

				while (true)
				{
					typename BSTree<T>::BinTreeNode*& target = *nodes.top();

					if (!target->right->right)
						break;
					else
						nodes.push(&target->right);
				}

				typename BSTree<T>::BinTreeNode*& target = *nodes.top();

				typename BSTree<T>::BinTreeNode* temp = target->right->left;
				right->data = target->right->data;
				delete target->right;
				target->right = temp;
			}
		}
	}


	while (!nodes.empty())
	{
		typename BSTree<T>::BinTreeNode*& curr = *nodes.top();
		--curr->count;

		typename BSTree<T>::BinTreeNode*& left = curr->left;
		typename BSTree<T>::BinTreeNode*& right = curr->right;

		if (!left && !right)
		{
			nodes.pop();
			continue;
		}

		if ((!left && right->Height() > 0) || (left && right && right->Height() > left->Height() + 1))
		{
			if (right && right->left && (!right->right || right->right->Height() < right->left->Height()))
			{
				nodes.push(&right);
				Balance(nodes, false);
			}
			else
				Balance(nodes, true);
		}
		else if ((!right && left->Height() > 0) || (left && right && left->Height() > right->Height() + 1))
		{
			if (left && left->right && (!left->left || left->left->Height() < left->right->Height()))
			{
				nodes.push(&left);
				Balance(nodes, false);
			}
			else
				Balance(nodes, true);
		}

		nodes.pop();
	}
}

template <typename T>
void AVLTree<T>::Balance(std::stack<typename BSTree<T>::BinTreeNode **>& nodes, bool once) {
	typename BSTree<T>::BinTreeNode** child = nullptr;

	if (!once)
	{
		child = nodes.top();
		nodes.pop();
	}

	typename BSTree<T>::BinTreeNode** curr = nodes.top();

	typename BSTree<T>::BinTreeNode* left = (*curr)->left;
	typename BSTree<T>::BinTreeNode* right = (*curr)->right;

	if (!left || (right && right->Height() > left->Height() + 1))
	{
		if (!once)
			RotateRight(*child);
		RotateLeft(*curr);
	}
	else if (!right || (left && left->Height() > right->Height() + 1))
	{
		if (!once)
			RotateLeft(*child);
		RotateRight(*curr);
	}
}

template <typename T>
void AVLTree<T>::RotateLeft(typename BSTree<T>::BinTreeNode *&tree) {
	typename BSTree<T>::BinTreeNode* curr = tree;
	
	if (!tree->right) return;

	tree = tree->right;
	curr->right = tree->left;
	tree->left = curr;

	tree->count = curr->count;

	curr->count = 1;
	if (typename BSTree<T>::BinTreeNode* left = curr->left)
		curr->count += left->count;
	if (typename BSTree<T>::BinTreeNode* right = curr->right)
		curr->count += right->count;
}

template <typename T>
void AVLTree<T>::RotateRight(typename BSTree<T>::BinTreeNode *&tree) {
	typename BSTree<T>::BinTreeNode* curr = tree;

	if (!tree->left) return;

	tree = tree->left;
	curr->left = tree->right;
	tree->right = curr;

	tree->count = curr->count;
	
	curr->count = 1;
	if (typename BSTree<T>::BinTreeNode* left = curr->left)
		curr->count += left->count;
	if (typename BSTree<T>::BinTreeNode* right = curr->right)
		curr->count += right->count;
}
