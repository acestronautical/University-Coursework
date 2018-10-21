#pragma once

#include <iostream>
#include <string>
#include "Stack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef struct studentRecord {
	string uid, id, name, email, units, program, level;
} StudentRecord;


class ListNode
{
public:
	
	ListNode::ListNode(StudentRecord argStudent = { "0", "0000", "name", "email", "units", "program", "level" });

	ListNode(const ListNode &copy);  // copy constructor - implicitly invoked copying a ListNode object during construction of 

	~ListNode();               // destructor - implicitly invoked when a ListNode object leaves scope;

	// getters
	ListNode * getNextPtr() const;      // used to retrieve a copy of the node's next pointer
	StudentRecord getStudentRecord() const; // used to retrieve a copy of the current student record
	Stack<string>* getStudentAbsences() const;
	int getNumAbsences()const;

	// setters
	void ListNode::setStudentRecord(const StudentRecord argStudent);            // used to modify the data in the node
	void setNextPtr(ListNode * const pNewNext); // used to modify the node's next pointer

private:
	StudentRecord student;
	Stack<string>* absences;
	ListNode *mpNext;
};
