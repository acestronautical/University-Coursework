/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a digital music manager
* Date: 9/15/17
* Description: part two of music manager
*******************************************************************************************/
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

//Structs

typedef struct duration {
	int seconds;
	int minutes;

} Duration;

typedef struct record {
	char artist[100];
	char album[100];
	char title[100];
	char genre[100];
	struct duration length;
	int playcount;
	int rating;

} Record;

typedef struct node {
	Record data;
	struct node* rightNode;
	struct node* leftNode;

} Node;

typedef struct list {
	struct node* start;
	struct node* end;
}List;

//Functions

//creates a node with the entered data and returns a pointer to that node
//return NULL if space not available
Node *makeNode(Record data);

//creates a Record struct based on a string
Record stringToRecord(char* oneLine);

//makes a node with record data and then inserts it at front of doubly linked list
int insertFront(Record data, List* list);

bool deleteNode(Node* deleteNode, List* list);

//Creates nodes LIFO from file 
int loadList(const char* fileName, List* list);

//writes to linked list data to csv file
void storeList(const char* fileName, List list);

//this is my own strtok functions which respects quoted literals
//the l in strtokl is for literal
char* strtokl(char* string, const char *delimiter);

//returns 1 if all needles were found in haystack
//I E if all keywords were matched
int keywordMatch(const char* haystack, const char* needles);

//goes through record fields and allows user to edit them, returns a boolean
bool modifyRecord(Record* data);

//allows editing of rating field of given node
//this functionality might get refactored into inputRecord
bool modifyRating(Record* data);

Node* findArtist(char* inString, List list);

Node* findSong(char* inString, List list);

void display(char* inString, List list);

Node* edit(char* inString, List list);

Node* rate(char* inString, List list);

//plays through from given node to end of playlist and increments playcount
void play(Node* song);

Node* sort(List* list, int mode);

char* lowercase(char* artist);

void shufflePlay(List list);

