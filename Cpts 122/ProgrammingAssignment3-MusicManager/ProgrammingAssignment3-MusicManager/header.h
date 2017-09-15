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

//Functions
Node *makeNode(Record data);
Record makeRecord(char* oneline);
int insertFront(Record data, Node** list);
int loadList(const char* fileName, Node** playList);
void storeList(const char* fileName, Node* playList);
Node* useList(char* inArtist, Node* playList, char mode);
void play(Node* song);
char* strtokl(char* string, const char *delimiter);
int keywordMatch(const char* haystack, const char* needles);
int editRecord(Node* editNode);
int editRating(Node* editNode);