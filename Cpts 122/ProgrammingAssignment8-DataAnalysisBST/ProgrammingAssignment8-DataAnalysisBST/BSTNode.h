//Data members:
//# mData : std::string // # denotes protected
//# mpLeft : Node *
//# mpRight : Node *

//Member functions :
//+virtual destructor // + denotes public
//+ constructor which accepts a string to set the data in the node; each pointer in the node is set to NULL
//+ setters – one for each data member(3 total should be defined)
//+ getters – one for each data member(3 total should be defined, the 2 defined to get the pointers should return a reference to the pointer, i.e.Node *&)
//+ pure virtual printData() function, which must be overridden in class TransactionNode

#pragma once
#include <iostream>
using std::ostream;
#include <string>
using std::string;

template <class T>
class BSTNode
{
private:

protected:
	T mData;
	BSTNode<T>* pLeft;
	BSTNode<T>* pRight;
public:
	BSTNode();
	BSTNode(const T & argData);
	BSTNode& operator= (const BSTNode &rhs);
	virtual ~BSTNode();
	T getData() const;
	BSTNode<T>* getLeft() const;
	BSTNode<T>* getRight() const;
	void setData(string argData);
	void setLeft(BSTNode* argLeft);
	void setRight(BSTNode* argRight);
	virtual void printData() = 0;

	friend ostream & operator << (ostream &lhs, BSTNode &rhs);
	friend ostream & operator << (ostream &lhs, BSTNode* &rhs);
};

template<class T>
inline BSTNode<T>::BSTNode()
{
	pLeft = nullptr, pRight = nullptr;
}

template <class T>
BSTNode<T>::BSTNode(const T &argData) {
	mData = argData, pLeft = nullptr, pRight = nullptr;
}

template <class T>
BSTNode<T> & BSTNode<T>::operator=(const BSTNode &rhs)
{
	mData = rhs.mData;
	pLeft = rhs.pLeft;
	pRight = rhs.pRight;
	return *this;
}

template <class T>
BSTNode<T>::~BSTNode() {
}

template <class T>
T BSTNode<T>::getData() const {
	return mData;
}

template <class T>
BSTNode<T>* BSTNode<T>::getLeft() const {
	return pLeft;
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight() const {
	return pRight;
}

template <class T>
void BSTNode<T>::setData(std::string argData) {
	mData = argData;
}

template <class T>
void BSTNode<T>::setLeft(BSTNode* argLeft) {
	pLeft = argLeft;
}

template <class T>
void BSTNode<T>::setRight(BSTNode* argRight) {
	pRight = argRight;
}

template <class T>
ostream & operator << (ostream &lhs, BSTNode<T> &rhs) {
	lhs << rhs.getData();
	return lhs;
}

template <class T>
ostream & operator << (ostream &lhs, BSTNode<T>* &rhs) {
	lhs << rhs->getData();
	return lhs;
}