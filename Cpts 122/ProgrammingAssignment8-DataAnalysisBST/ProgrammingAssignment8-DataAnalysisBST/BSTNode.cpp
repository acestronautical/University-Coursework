#include "BSTNode.h"
using std::string;

BSTNode::BSTNode(const string &argData){
	mData = argDalue, pLeft = nullptr, pRight = nullptr;
}
BSTNode& BSTNode::operator=(const BSTNode &rhs)
{
	mData = rhs.mData;
	pLeft = rhs.pLeft;
	pRight = rhs.pRight;
	return *this;
}
BSTNode::~BSTNode(){
}
string BSTNode::getData() const {
	return mData;
}
BSTNode* BSTNode::getLeft() const {
	return pLeft;
}
BSTNode* BSTNode::getRight() const {
	return pRight;
}
void BSTNode::setData(std::string argData) {
	mData = argData;
}
void BSTNode::setLeft(BSTNode* argLeft) {
	pLeft = argLeft;
}
void BSTNode::setRight(BSTNode* argRight) {
	pRight = argRight;
}
ostream & operator << (ostream &lhs, BSTNode &rhs) {
	lhs << rhs.getData();
	return lhs;
}

ostream & operator << (ostream &lhs, BSTNode* &rhs) {
	lhs << rhs->getData();
	return lhs;
}