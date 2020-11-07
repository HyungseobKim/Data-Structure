/*------------------------------------------------------------------------
File Name: RopeTree.h
Purpose: Class declaration for RopeTree.
Author: Kim Hyungseob
Created: 5/10
------------------------------------------------------------------------*/
#include <string>
#include <iostream>

class RopeTree
{
public:
	RopeTree(std::string text);
	~RopeTree();

	char operator[](int index) const;
	RopeTree& operator+=(RopeTree& tree);
	RopeTree& operator+=(RopeTree&& tree);

	friend std::ostream& operator<<(std::ostream& os, const RopeTree& tree);

	unsigned int Size() const;
	void Clear();

private:
	struct RopeNode
	{
		RopeNode(std::string text);
		RopeNode(unsigned int weight);
		~RopeNode();

		char Find(unsigned int index) const;

		unsigned int m_weight = 0;
		std::string m_text;

		RopeNode* m_left = nullptr;
		RopeNode* m_right = nullptr;
	};

private:
	RopeNode* m_root = nullptr;
};