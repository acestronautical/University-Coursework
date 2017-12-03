//Next define a class TransactionNode, which publically inherits from abstract base class Node. Class TransactionNode must encapsulate the following:
//New Data members :
//-mUnits : int // - denotes private
//
//New Member functions :
//+destructor // + denotes public
//+ constructor which accepts a string to set the data and an integer to set the number of units in the node; should invoke class Node’s constructor
//+ setter
//+ getter
//+ printData(), which overrides the pure virtual function in class Node
#pragma once
#include <string>
#include "BSTNode.h"
using std::string;

class TransactionNode:public BSTNode<string>
{
public:
	TransactionNode(int argUnits = 0, string argData = "");
	~TransactionNode();
	void setUnits(int argUnits);
	int getUnits();
	void printData();

private:
	int mUnits;
};

TransactionNode::TransactionNode(int argUnits, string argData)
{
	mUnits = argUnits;
	setData(argData);
}

TransactionNode::~TransactionNode()
{
}

inline void TransactionNode::setUnits(int argUnits)
{
	mUnits = argUnits;
}

inline int TransactionNode::getUnits()
{
	return mUnits;
}

inline void TransactionNode::printData()
{
}
