#include "BST.h"
#include <fstream>
using std::string;
using std::cout;
using std::fstream;


int main() {
	
	BST tree("MorseTable.txt");

	BSTparse("Convert.txt", tree);

	cout << std::endl;
	system("pause");
	return 0;
}