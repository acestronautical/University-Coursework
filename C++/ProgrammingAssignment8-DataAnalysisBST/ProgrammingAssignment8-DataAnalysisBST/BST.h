//Data members :
//-mpRoot : Node * // yes, we want a pointer to a Node, not TransactionNode here!
//
//Member functions :
//+destructor // calls destroyTree ()
//- destroyTree() // yes, it’s private, and it should visit each node in postOrder to delete them
//+ default constructor
//+ setter
//+ getter
//+ insert() // public used to hide pointer information, i.e. won’t pass in the root of the tree into this function, only the private insert () function
//- insert() // yes, it’s private, and it dynamically allocates a TransactionNode and inserts recursively in the correct subtree based on mUnits; should pass in a reference to a pointer (i.e. Node *& pT)
//+ inOrderTraversal() // yes, once again it’s private to hide pointer information
//- inOrderTraversal(), which recursively visits and prints the contents(mData and mUnits) of each node in the tree in order; each node’s printData() should be called
//contents should be printed on a separate line; must call the printData() function associated with the TransactionNode
//+ findSmallest(), which returns a reference to a TransactionNode(i.e TransactionNode &)  with the smallest mUnits
//+ findLargest(), which returns a reference to a TransactionNode with the largest mUnits

#pragma once
#include "BSTNode.h"
#include <iostream>
using std::ostream;
using std::string;

template <class T>
class BST
{
public:
	BST();
	~BST();
	void inorder(ostream &outStream);
	bool insertNode(BSTNode<T> * newNode);
	T search(const char &argKey);
	bool isEmpty();
	BSTNode<T>* min();
	BSTNode<T>* max();
private:
	//data
	BSTNode<T>* pRoot;
	//functions
	void inorder(ostream &outStream, BSTNode<T>* argNode);

};


template <class T>
BST<T>::BST()
{
	pRoot = nullptr;
}

template <class T>
BST<T>::~BST()
{
}

template <class T>
void BST<T>::inorder(ostream &outStream)
{
	inorder(outStream, pRoot);
}

template <class T>
bool BST<T>::insertNode(BSTNode<T> * newNode)
{
	BSTNode* curNode = pRoot;
	if (this->isEmpty()) {
		pRoot = newNode;
		return true;
	}
	while (true) {
		if (newNode->getData() < curNode->getData()) {
			if (curNode->getLeft() == NULL) {
				curNode->setLeft(newNode);
				return true;
			}
			curNode = curNode->getLeft();
		}
		else if (newNode->getData() > curNode->getData()) {
			if (curNode->getRight() == NULL) {
				curNode->setRight(newNode);
				return true;
			}
			curNode = curNode->getRight();
		}
		else if (newNode->getData() == curNode->getData()) {
			free(newNode);
			return false;
		}
	}
}

template <class T>
bool BST<T>::isEmpty()
{
	return (bool)!pRoot;
}

template<class T>
inline BSTNode<T>* BST<T>::min()
{
	BSTNode* curNode = pRoot;
	while (curNode->getLeft())
		curNode = curNode->getLeft();
	return curNode;
}

template<class T>
inline BSTNode<T>* BST<T>::max()
{
	BSTNode* curNode = pRoot;
	while (curNode->getRight())
		curNode = curNode->getRight();
	return curNode;
}

template <class T>
T BST<T>::search(const char & argData)
{
	static T empty;
	BSTNode* curNode = pRoot;
	if (this->isEmpty())
		return empty;
	while (true) {
		if (argData < curNode->getData()) {
			if (curNode->getLeft() == NULL)
				return empty;
			else
				curNode = curNode->getLeft();
		}
		else if (argData > curNode->getData()) {
			if (curNode->getRight() == NULL)
				return empty;
			else
				curNode = curNode->getRight();
		}
		else if (argData == curNode->getData())
			return curNode->getData();
	}
}

template <class T>
void BST<T>::inorder(ostream &outStream, BSTNode<T> * argNode)
{
	if (!argNode) return;
	inorder(outStream, argNode->getLeft());
	outStream << argNode << std::endl;
	inorder(outStream, argNode->getRight());
}