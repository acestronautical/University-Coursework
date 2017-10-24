#pragma once
#include <iostream>
using std::ostream;
#include <string>
using std::string;

class BSTNode
{
public:
	BSTNode(const char &argKey, const string &argValue);
	BSTNode& operator= (const BSTNode &rhs);
	~BSTNode();
	char getKey() const;
	string getValue() const;
	BSTNode* getLeft() const;
	BSTNode* getRight() const;
	void setKey(char argKey);
	void setValue(string argValue);
	void setLeft(BSTNode* argLeft);
	void setRight(BSTNode* argRight);
	friend ostream & operator << (ostream &lhs, BSTNode &rhs);
	friend ostream & operator << (ostream &lhs, BSTNode* &rhs);

private:
	char key;
	string value;
	BSTNode* pLeft;
	BSTNode* pRight;
};

