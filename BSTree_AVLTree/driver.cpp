#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <sstream>
#include <cstring>
#include <stack>

#include "BSTree.h"
#include "AVLTree.h"
#include "PRNG.h"

#define SHOW_COUNTS

//*********************************************************************
// End Printing/Debugging
//*********************************************************************

int RandomInt(int low, int high) {
  //return std::rand() % (high - low + 1) + low;
	return Digipen::Utils::Random(low, high);
}

template <typename T>
void SwapInt(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T> void Shuffle(T *array, int count, int stride = 1) {
	for(int i = 0; i < count; i += stride) {
		int r = RandomInt(0, count - 1);
		SwapInt(array[i], array[r]);
	}
}

void GetValues(int *array, int size) {
  //std::srand(1);
	Digipen::Utils::srand(1, 2);
	for(int i = 0; i < size; i++)
		array[i] = i;

	Shuffle(array, size);
}

template <typename T>
void Test1(void) {
	T tree;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test1 - random insert";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++) {
			tree.Insert(vals[i]);
			tree.DebugPrint( );
		}
		tree.DebugPrint( );
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}


template <typename T>
void Test2(void) {
	T tree;
	const int size = 10;
	const char *test = "Test2 - sorted insert";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++)
			tree.Insert(i);
		tree.DebugPrint( );
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void Test3(void) {
	T tree;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test3 - random insert/remove";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++) {
			tree.Insert(vals[i]);
		}
		tree.DebugPrint(true);

		std::cout << "remove 6, 3, 2:\n";
		tree.Remove(6);
		tree.DebugPrint(true);
		tree.Remove(3);
		tree.DebugPrint(true);
		tree.Remove(2);
		tree.DebugPrint(true);
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void Test4(void) {
	T tree;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test4 - random insert/remove all";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++)
			tree.Insert(vals[i]);
		tree.DebugPrint(true);

		std::cout << "remove 2, 0, 1, 4, 3:\n";
		tree.Remove(2);
		tree.DebugPrint(true);
		tree.Remove(0);
		tree.DebugPrint(true);
		tree.Remove(1);
		tree.DebugPrint(true);
		tree.Remove(4);
		tree.DebugPrint(true);
		tree.Remove(3);
		tree.DebugPrint(true);

		std::cout << "remove some invalid (10, -1):\n";
		tree.Remove(10);
		tree.Remove(-1);
		tree.DebugPrint(true);

		std::cout << "remove 8, 9, 7, 5, 6:\n";
		tree.Remove(8);
		tree.DebugPrint(true);
		tree.Remove(9);
		tree.DebugPrint(true);
		tree.Remove(7);
		tree.DebugPrint(true);
		tree.Remove(5);
		tree.DebugPrint(true);
		tree.Remove(6);
		tree.DebugPrint(true);

		std::cout << "remove 2 from empty tree:\n";
		tree.Remove(2);
		tree.DebugPrint( );
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void Test5(void) {
	T tree;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test5 - random insert/clear";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++)
			tree.Insert(vals[i]);

		std::cout << "clear:\n";
		tree.Clear( );
		tree.DebugPrint( );
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void Test6(void) {
	T tree;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test6 - random insert/find";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++)
			tree.Insert(vals[i]);

		tree.DebugPrint( );
		int value;

		value = 1;
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		value = 3;
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		value = 5;
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		value = 50;
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void Test7(void) {
	T tree1, tree2;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test7 - assignment";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++) {
			tree1.Insert(vals[i]);
			tree2.Insert(vals[i] * 3);
		}
		std::cout << "tree 1 ------------------------------------------\n";
		tree1.DebugPrint( );

		std::cout << "tree 2 ------------------------------------------\n";
		tree2.DebugPrint( );

		tree1 = tree2;

		std::cout << "Remove 2 from tree 1\n";
		tree1.Remove(6);
		std::cout << "tree 1 ------------------------------------------\n";
		tree1.DebugPrint( );
		std::cout << "tree 2 ------------------------------------------\n";
		tree2.DebugPrint( );

		tree1.Clear( );
		tree2.ResetRoot( );
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void Test8(void) {
	T tree1;
	const int size = 10;
	int vals[size];
	GetValues(vals, size);
	const char *test = "Test8 - copy constructor";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++)
			tree1.Insert(vals[i]);
		std::cout << "tree 1 ------------------------------------------\n";
		tree1.DebugPrint( );

		T tree2(tree1);

		std::cout << "Remove 2 from tree 1\n";
		tree1.Remove(2);
		std::cout << "tree 1 ------------------------------------------\n";
		tree1.DebugPrint( );
		std::cout << "tree 2 ------------------------------------------\n";
		tree2.DebugPrint( );
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

template <typename T>
void TestIndex(void) {
	T tree;
	char vals[] = "ASERCHIN";
	const int size = static_cast<int>(strlen(vals));
	const char *test = "TestIndex - random insert/subscript";

	std::cout << "\n====================== " << test << " ======================\n";
	std::cout << ReadableType(typeid(T).name( )) << std::endl;
	try {
		for(int i = 0; i < size; i++) {
			tree.Insert(vals[i]);
			//std::cout << "============================\n";
			//PrintBST(tree);     
		}
		std::cout << "height: " << tree.Height( ) << std::endl;
		std::cout << " nodes: " << tree.Size( ) << std::endl;
		if(tree.Empty( ))
			std::cout << "tree is empty\n\n";
		else
			std::cout << "tree is NOT empty\n\n";

		tree.DebugPrint( );
		for(int i = 0; i < size; i++)
			std::cout << "Index " << i << ": " << tree[static_cast<int>(i)].data << std::endl;

	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in " << test;
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Caught unknown exception in " << test << std::endl;
	}
}

#include <fstream>
template <typename T>
void MakeFile(const AVLTree<T>& tree) {
	tree.Empty( );
	if(tree.ImplementedBalanceFactor( )) {
		std::ofstream bf("bf.txt");
		bf << "balance factor implemented" << std::endl;
	}
}

void AVLStress(void) {
	const char *test = "AVLStress";
	std::cout << "\n====================== " << test << " ======================\n";

	int *ia = 0;
	try {
		AVLTree<int> tree;

		int size = 10000;

		ia = new int[size];
		for(int i = 0; i < size; i++)
			ia[i] = i;

		Shuffle(ia, size, 1);
		//Print(ia, size);

		for(int i = 0; i < size; i++) {
			tree.Insert(ia[i]);
		}

		  // Stress indexing
		int sum = 0;
		for(int j = 0; j < 1000; j++)
			for(int i = size - 1; i > size - 1000; i--)
				sum += tree[i].data;
		std::cout << "Sum is " << sum << std::endl;
		tree.DebugPrint( );

		std::cout << "Remove stuff" << std::endl;
		Shuffle(ia, size, 1);
		for(int i = 0; i < size - 10; i++) {
			tree.Remove(ia[i]);
		}
		tree.DebugPrint( );
		for(unsigned i = 0; i < tree.Size( ); i++)
			std::cout << "Index " << i << ": " << tree[static_cast<int>(i)].data << std::endl;

	} catch(const BSTException& e) {
		std::cout << "Exception caught: " << e.what( ) << std::endl;
	} catch(...) {
		std::cout << "Unknown exception." << std::endl;
	}
	delete[] ia;
}

#include <string>
template <typename T>
void TestStrings(void) {
	const char *test = "TestStrings";
	std::cout << "\n====================== " << test << " ======================\n";

	try {
		T tree;

		const char *strs[] = {"abe", "for", "fad", "one", "two", "six", "box",
							  "zoo", "car", "dog", "dig", "fat", "fav", "hit",
							  "cab", "abd", "sox", "man", "boy", "sow", "abc",
		};

		size_t size = sizeof(strs) / sizeof(*strs);
		for(size_t i = 0; i < size; i++)
			tree.Insert(strs[i]);

		tree.DebugPrint( );

		std::string value = "dig";
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		value = "abe";
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		value = "hot";
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		value = "abcd";
		if(tree.Find(value)) {
			std::cout << "Value " << value << " found\n";
		} else {
			std::cout << "Value " << value << " NOT found\n";
		}

		for(size_t i = 0; i < size; i++)
			std::cout << "Index " << i << ": " << tree[static_cast<int>(i)].data << std::endl;
	} catch(const BSTException &e) {
		std::cout << "Caught BSTException in: " << test << ": ";
		int value = e.code( );
		if(value == BSTException::E_NO_MEMORY)
			std::cout << "E_NO_MEMORY" << std::endl;
		else
			std::cout << "Unknown error code." << std::endl;
	} catch(...) {
		std::cout << "Unknown exception." << std::endl;
	}
}

//***********************************************************************
//***********************************************************************
//***********************************************************************

typedef void(*TestFn)(void);

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000) {
	if(maxwait + safewait > 0)
		fn( );
}

int main(int argc, char **argv) {

	size_t test_num =12;
	if(argc > 1)
		test_num = static_cast<size_t>(std::atoi(argv[1]));

	struct TimedTest {
		void(*test)(void);
		int maxwait;
		int safewait;
	};
	typedef int T;
	typedef std::string U;
	TimedTest Tests[] = {{Test1<BSTree<T> >,         1000,  500}, //  0 random insert
						 {Test2<BSTree<T> >,         1000,  500}, //  1 sorted insert
						 {Test3<BSTree<T> >,         1000,  500}, //  2 random insert/remove some
						 {Test4<BSTree<T> >,         1000,  500}, //  3 random insert/remove all
						 {Test5<BSTree<T> >,         1000,  500}, //  4 random insert/clear
						 {Test6<BSTree<T> >,         1000,  500}, //  5 random insert/find

						 {Test7<BSTree<T> >,         1000,  500}, //  6 assignment
						 {Test8<BSTree<T> >,         1000,  500}, //  7 copy constructor

						 {Test1<AVLTree<T> >,        1000,  500}, //  8 random insert
						 {Test2<AVLTree<T> >,        1000,  500}, //  9 sorted insert
						 {Test3<AVLTree<T> >,        1000,  500}, // 10 random insert/remove some
						 {Test4<AVLTree<T> >,        1000,  500}, // 11 random insert/remove all
						 {Test5<AVLTree<T> >,        1000,  500}, // 12 random insert/clear
						 {Test6<AVLTree<T> >,        1000,  500}, // 13 random insert/find

						 {Test7<AVLTree<T> >,        1000,  500}, // 14 assignment
						 {Test8<AVLTree<T> >,        1000,  500}, // 15 copy constructor

						 {TestIndex<BSTree<char> >,  1000,  500}, // 16 random insert/select
						 {TestIndex<AVLTree<char> >, 1000,  500}, // 17 random insert/select
						 {TestStrings<BSTree<U> >,   1000,  500}, // 18 random insert strings/select
						 {TestStrings<AVLTree<U> >,  1000,  500}, // 19 random insert strings/select*/
						 {AVLStress,                10000, 3000}, // 20 stress avl only
	};

	size_t num = sizeof(Tests) / sizeof(*Tests);
	if(test_num == 0) {
		for(size_t i = 0; i < num; i++)
			ExecuteTest(Tests[i].test, Tests[i].maxwait, Tests[i].safewait);
	} else if(test_num > 0 && test_num <= num) {
		ExecuteTest(Tests[test_num - 1].test, Tests[test_num - 1].maxwait, Tests[test_num - 1].safewait);
	}

	return 0;
}
