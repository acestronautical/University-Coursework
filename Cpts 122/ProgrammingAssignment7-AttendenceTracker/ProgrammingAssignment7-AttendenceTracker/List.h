#pragma once

#include <iostream>

#include "ListNode.h"

using std::cin;
using std::cout;
using std::endl;

// This class defines a container for a list; it's a singly linked list
class List
{
public:
	List();                     // default constructor; will always set mpHead to NULL
	List(const List &copyList); // copy constructor - implicitly invoked copying a List object during construction of 
	~List();                    // destructor - implicitly invoked when a List object leaves scope 

	// getter
	ListNode * getHeadPtr() const;     // returns a copy of the address stored in mpHead
	// setter
	void setHeadPtr(ListNode * const pNewHead); // modifies mpHead

	bool insertAtFront(const StudentRecord newData);     // inserts newData at the beginning or front of the list
	StudentRecord deleteAtFront();                       // deletes the node at the front of the list
	bool isEmpty();                            // determines if the list is empty  
	void destroyList();                        // deletes each node to free memory; will call in the destructor

private:
	ListNode *mpHead; // pointer to the start or head of the singly linked list

	ListNode * makeNode(const StudentRecord newData);    // will only call within insert functions
	void destroyListHelper(ListNode * const pMem);    // we will use recursion to solve this problem!
};