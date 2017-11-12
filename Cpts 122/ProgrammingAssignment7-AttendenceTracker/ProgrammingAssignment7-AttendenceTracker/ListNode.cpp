#include "ListNode.h"
#include <string>

// constructor - "constructs" a ListNode; initializes the object
ListNode::ListNode(StudentRecord argStudent)
{
	student.uid = argStudent.uid, student.id = argStudent.id, student.name = argStudent.name,
		student.email = argStudent.email, student.units = argStudent.units, student.program = argStudent.program, student.level = argStudent.level;
	mpNext = nullptr;
	absences = new Stack<string>(0);
}

// copy constructor - implicitly invoked copying a ListNode object during construction of 
// another ListNode object, or when a ListNode object is passed-by-value
ListNode::ListNode(const ListNode &copy)
{
	student.uid = copy.student.uid, student.id = copy.student.id, student.name = copy.student.name,
	student.email = copy.student.email, student.units = copy.student.units, student.program = copy.student.program,
	mpNext = copy.mpNext;
}

// destructor - implicitly invoked when a ListNode object leaves scope
ListNode::~ListNode()
{
	delete absences;
	cout << "Inside ListNode's destructor!" << endl;
}

ListNode * ListNode::getNextPtr() const // the const indicates "constant" function; can't modify the object's data members with this function
{
	return mpNext;
}

StudentRecord ListNode::getStudentRecord() const
{
	return student;
}

Stack<string>* ListNode::getStudentAbsences() const
{
	return absences;
}

int ListNode::getNumAbsences() const
{
	return absences->getSize();
}

void ListNode::setStudentRecord(const StudentRecord argStudent) // the const in this context ensures newData can't be modified
{
	student = argStudent;
}

// the const in this context ensures pNewNext can't be modified;
// remember read as pNewNext is a constant pointer to a ListNode - the ListNode object is not const though!
void ListNode::setNextPtr(ListNode * const pNewNext) 
{
	mpNext = pNewNext;
}