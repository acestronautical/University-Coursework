#include "BST.h"
#include <fstream>
BST::BST()
{
	pRoot = nullptr;
}

BST::BST(string filePath)
{
	pRoot = nullptr;
	char key = '@';
	string value = "@";
	std::fstream stream;
	stream.open(filePath, std::fstream::in);
	while (stream >> key, stream >> value) {
		this->insert(key, value);
	}
	stream.close();
}

BST::~BST()
{
}

void BST::inorder(ostream &outStream)
{
	inorder(outStream, pRoot);
}

void BST::preorder(ostream &outStream)
{
	preorder(outStream, pRoot);
}

void BST::postorder(ostream &outStream)
{
	postorder(outStream, pRoot);
}

bool BST::insertNode(BSTNode * newNode)
{
	BSTNode* curNode = pRoot;
	if (this->isEmpty()) {
		pRoot = newNode;
		return true;
	}
	while (true) {
		if (newNode->getKey() < curNode->getKey()) {
			if (curNode->getLeft() == NULL) {
				curNode->setLeft(newNode);
				return true;
			}
			curNode = curNode->getLeft();
		}
		else if (newNode->getKey() > curNode->getKey()) {
			if (curNode->getRight() == NULL) {
				curNode->setRight(newNode);
				return true;
			}
			curNode = curNode->getRight();
		}
		else if (newNode->getKey() == curNode->getKey()) {
			free(newNode);
			return false;
		}
	}
}

bool BST::insert(const char & argKey, const string & argValue)
{
	BSTNode* newNode;
	newNode = new BSTNode(argKey, argValue);
	return insertNode(newNode);

}

bool BST::isEmpty()
{
	return (bool)!pRoot;
}

string BST::search(const char & argKey)
{
	static string empty = "";
	BSTNode* curNode = pRoot;
	if (this->isEmpty())
		return empty;
	while (true) {
		if (argKey < curNode->getKey()) {
			if (curNode->getLeft() == NULL)
				return empty;
			else
				curNode = curNode->getLeft();
		}
		else if (argKey > curNode->getKey()) {
			if (curNode->getRight() == NULL)
				return empty;
			else
				curNode = curNode->getRight();
		}
		else if (argKey == curNode->getKey())
			return curNode->getValue();
	}
}

string BST::operator[](const char &argKey)
{
	return search(argKey);
}

void BST::inorder(ostream &outStream, BSTNode * argNode)
{
	if (!argNode) return;
	inorder(outStream, argNode->getLeft());
	outStream << argNode << std::endl;
	inorder(outStream, argNode->getRight());
}

void BST::preorder(ostream &outStream, BSTNode * argNode)
{
	if (!argNode) return;
	outStream << argNode << std::endl;
	preorder(outStream, argNode->getLeft());
	preorder(outStream, argNode->getRight());
}

void BST::postorder(ostream &outStream, BSTNode * argNode)
{
	if (!argNode) return;
	postorder(outStream, argNode->getLeft());
	postorder(outStream, argNode->getRight());
	outStream << argNode << std::endl;
}

void BSTparse(const string &filepath, BST &tree)
{

	char letter = '@';
	std::fstream stream;
	stream.open(filepath, std::fstream::in);
	while (stream.get(letter)) {
		if (letter == ' ')
			std::cout << "  ";
		else if (letter == '\n')
			std::cout << '\n';
		else
			std::cout << tree.search(toupper(letter)) << " ";
	}
	stream.close();
}
