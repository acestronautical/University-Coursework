#include "BSTNode.h"
using std::string;

BSTNode::BSTNode(const char &argKey, const string &argValue){
	key = argKey, value = argValue, pLeft = nullptr, pRight = nullptr;
}
BSTNode& BSTNode::operator=(const BSTNode &rhs)
{
	key = rhs.key;
	value = rhs.value;
	pLeft = rhs.pLeft;
	pRight = rhs.pRight;
	return *this;
}
BSTNode::~BSTNode(){
}
char BSTNode::getKey() const {
	return key;
}
string BSTNode::getValue() const {
	return value;
}
BSTNode* BSTNode::getLeft() const {
	return pLeft;
}
BSTNode* BSTNode::getRight() const {
	return pRight;
}
void BSTNode::setKey(char argKey) {
	key = argKey;
}
void BSTNode::setValue(std::string argValue) {
	value = argValue;
}
void BSTNode::setLeft(BSTNode* argLeft) {
	pLeft = argLeft;
}
void BSTNode::setRight(BSTNode* argRight) {
	pRight = argRight;
}
ostream & operator << (ostream &lhs, BSTNode &rhs) {
	lhs << rhs.getKey() << " = " << rhs.getValue();
	return lhs;
}

ostream & operator << (ostream &lhs, BSTNode* &rhs) {
	lhs << rhs->getKey() << " = " << rhs->getValue();
	return lhs;
}