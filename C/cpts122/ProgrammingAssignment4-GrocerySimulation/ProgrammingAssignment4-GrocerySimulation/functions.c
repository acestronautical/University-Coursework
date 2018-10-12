/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a grocery store line simulation
* Date: 9/28/17
* Description: Simulate two grocery store lines
*******************************************************************************************/
#include "header.h"

//creates node with newCustomer 
//returns pointer to node containing newCustomer
Node *makeNode(Data newCustomer)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode == NULL) //malloc fail?
		return NULL;
	newNode->pNext = NULL;
	newNode->customerInfo = (Data *)malloc(sizeof(Data));
	if (newNode->customerInfo != NULL)
	{
		newNode->customerInfo->customerNumber = newCustomer.customerNumber;
		newNode->customerInfo->serviceTime = newCustomer.serviceTime;
		newNode->customerInfo->totalTime = newCustomer.totalTime;
	}
	return newNode;
}

// Insert at the end of the queue
bool enqueue(Queue *queue, Data newCustomer)
{
	Node *newNode = makeNode(newCustomer);
	if (newNode == NULL) //makeNode fail?
		return false;
	if (queue->pHead == NULL) // empty queue
	{
		queue->pHead = queue->pTail = newNode;
	}
	else { // non-empty queue
		queue->pTail->pNext = newNode;
		queue->pTail = newNode;
	}
	return true;
}

// remove from front of list
void dequeue(Queue *queue)
{
	Node* tempNode = NULL;
	if (!queue->pHead) //queue empty
		return;

	if (!queue->pHead->pNext) // remove only node
	{
		free(queue->pHead->customerInfo);
		free(queue->pHead);
		queue->pHead = queue->pTail = NULL;
	}
	else { // remove from multiple nodes
		tempNode = queue->pHead->pNext;
		free(queue->pHead->customerInfo);
		free(queue->pHead);
		queue->pHead = tempNode;
	}
	return;
}

//returns true if empty list, false otherwise
bool isEmpty(Queue queue) {
	return (bool)!queue.pHead;
}

//Prints two queues side by side
void printQueues(Queue expressLane, Queue normalLane) {
	Node* expressNode = expressLane.pHead;
	Node* normalNode = normalLane.pHead;
	char* leftStickMan =
		"          O\n"
		"         /|\\\n"
		"         / \\\n";
	char* rightStickMan =
		"                           O\n"
		"                          /|\\\n"
		"                          / \\\n";
	char* twoStickMans =
		"          O                O\n"
		"         /|\\              /|\\\n"
		"         / \\              / \\\n";
	printf(
 "  +------+     +------+     +------+   \n"
 " /  / / /|     |      |     |\\ \\ \\  \\ \n"
 "+-+----+ |     +------+     | +------+\n"
 "|      | |     |      |     | |      |\n"
 "|Xpress| +     |      |     + |Normal|\n"
 "|      |/      |      |      \\|      |\n"
 "+------+       +------+       +------+\n");
	while (normalNode || expressNode) {
		if (normalNode && expressNode) {
			printf("%s", twoStickMans);
			printf("         #%3d            #%3d\n",expressNode->customerInfo->customerNumber, normalNode->customerInfo->customerNumber );
			normalNode = normalNode->pNext;
			expressNode = expressNode->pNext;
		}
		else if (expressNode) {
			printf("%s", leftStickMan);
			printf("         #%3d\n", expressNode->customerInfo->customerNumber);
			expressNode = expressNode->pNext;
		}
		else {
			printf("%s", rightStickMan);
			printf("                         #%3d\n", normalNode->customerInfo->customerNumber);
			normalNode = normalNode->pNext;
		}
	}
}



