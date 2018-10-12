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

//creates a node with the given data and returns a pointer to that node
//return NULL if space not available
Node *makeNode(Record data);

//makes a node with record data and then inserts it at front of doubly linked list
int insertFront(Record data, List* list);

//deletes node from list and fixes list
//returns true if node deleted successfully
bool deleteNode(Node* deleteNode, List* list);

//creates a Record struct based on a string
Record stringToRecord(char* oneLine);

//Creates nodes LIFO from file 
int loadList(const char* fileName, List* list);

//writes linked list data to csv file
void storeList(const char* fileName, List list);

//this is my own strtok functions which respects quoted literals
//the l in strtokl is for literal
char* strtokl(char* string, const char *delimiter);

//returns a lowercase version of given string
//also removes leading quote mark for use with strcmp()
char* lowercase(char* artist);

//returns 1 if all needles were found in haystack
//I E if all keywords were matched
bool keywordMatch(const char* haystack, const char* needles);

//finds matching artists records and prompts user to select one
Node* findArtist(char* inString, List list);

//finds matching songs and prompts user to select one
Node* findSong(char* inString, List list);

//displays based on entered artist, or displays all if newline or null is entered
void display(char* inString, List list);

//goes through record fields and allows user to edit them
//returns a true if a change was made
bool modifyRecord(Record* data);

//allows editing of rating field of given node
//this functionality might get refactored
bool modifyRating(Record* data);

//prompts user to select a record matching the artist, then allows user to edit that record
Node* edit(char* inString, List list);

//same as edit, but only allows editing of rating field
//possibly should be refactored somehow
Node* rate(char* inString, List list);

//plays through from given node to end of playlist and increments playcount
void play(Node* song);

//sorts list in place based on user selected criteria
//currently implemented with bubble sort, will improve if time permits
List* sort(List* list, int mode);

//navigates through the list in a randomly determined order
//does not modify list or create new list
void shufflePlay(List list);

