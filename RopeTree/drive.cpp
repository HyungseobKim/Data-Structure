#include <fstream>

#include "RopeTree.h"


int main(void)
{
	std::cout << "---------------------Test1---------------------" << std::endl;

	RopeTree rope("Hello my name is Kevin");
	std::cout << rope << std::endl;
	std::cout << "Index 0 = " << rope[0] << std::endl;
	std::cout << "Index 4 = " << rope[4] << std::endl;
	std::cout << "Index 10 = " << rope[10] << std::endl;
	std::cout << "Index 11 = " << rope[11] << std::endl;
	std::cout << "Index 18 = " << rope[18] << std::endl;
	std::cout << "Index 20 = " << rope[20] << std::endl;
	std::cout << "Index 30 = " << rope[30] << std::endl;
	
	std::cout << std::endl << "---------------------Test2---------------------" << std::endl;

	RopeTree tree1("This is tree 1;");
	RopeTree tree2("This is tree 2;");
	tree1 += tree2;
	std::cout << tree1;

	std::cout << std::endl << "---------------------Test3---------------------" << std::endl;

	std::ifstream infile("Source.cpp");
	RopeTree currTree("");

	char buff[255];
	while (infile.eof() == false) {
		infile.getline(buff, 255);
		int len = strlen(buff);
		buff[strlen(buff)] = '\n';
		buff[len + 1] = '\0';
		currTree += RopeTree(buff);
	}
	std::cout << currTree;

	system("pause");
	return 0;
}