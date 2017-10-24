/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a grocery store line simulation
* Date: 9/28/17
* Description: Simulate two grocery store lines
*******************************************************************************************/
#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

//TYPE DEFINITIONS

typedef struct data
{
     int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
     int serviceTime;   // Random time; varies between express and normal lanes; units in minutes
     int totalTime;     // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
} Data; // This memory needs to be allocated on the heap!

typedef struct node
{
	Data *customerInfo;
	struct node *pNext;
}Node;

typedef struct queue
{
	Node *pHead;
	Node *pTail;
} Queue;

//FUNCTION PROTOTYPES

//creates node with newCustomer 
//returns pointer to node containing newCustomer
Node *makeNode(Data newCustomer);

// Insert at the end of the queue
bool enqueue(Queue *queue, Data newCustomer);

// remove from front of list
void dequeue(Queue *queue);

//returns true if empty list, false otherwise
bool isEmpty(Queue queue);

//Prints two queues side by side
void printQueues(Queue expressLane, Queue normalLane);