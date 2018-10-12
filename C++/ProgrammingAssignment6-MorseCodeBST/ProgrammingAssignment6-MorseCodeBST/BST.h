#pragma once
#include "BSTNode.h"
#include <iostream>
using std::ostream;
using std::string;

class BST
{
public:
	BST();
	BST(string filePath);
	~BST();
	void inorder(ostream &outStream);
	void preorder(ostream &outStream);
	void postorder(ostream &outStream);
	bool insert(const char &argKey, const string &argValue);
	string search(const char &argKey);
	string operator[] (const char &argKey);
	bool isEmpty();
private:
	//data
	BSTNode* pRoot;
	//functions
	bool insertNode(BSTNode* newNode);
	void inorder(ostream &outStream, BSTNode* argNode);
	void preorder(ostream &outStream, BSTNode* argNode);
	void postorder(ostream &outStream, BSTNode* argNode);

};

void BSTparse(const string &filepath, BST &tree);
