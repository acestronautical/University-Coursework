/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a digital music manager
* Date: 9/15/17
* Description: part two of music manager
*******************************************************************************************/
#include "header.h"

//creates a node with the entered data and returns a pointer to that node
//return NULL if space not available
Node *makeNode(Record data){

	Node* thisNode = (Node *)malloc(sizeof(Node));

	if (thisNode == NULL)
		return NULL;
	
		// initialize
		thisNode->leftNode = NULL;
		thisNode->rightNode = NULL;
		thisNode->data = data;
	return thisNode;
}

//creates a Record struct based on a string
Record makeRecord(char* oneline) {
	
	char* token;
	Record newRecord;
	//enter data into record
	token = strtokl(oneline, ",");
	strcpy(newRecord.artist, token);
	token = strtokl(NULL, ",");
	strcpy(newRecord.album, token);
	token = strtokl(NULL, ",");
	strcpy(newRecord.title, token);
	token = strtokl(NULL, ",");
	strcpy(newRecord.genre, token);
	token = strtokl(NULL, ",");
	//strtokl and strtok are different functions. strtokl respects quoted literals.
	newRecord.length.minutes = atoi(strtok(token, ":"));
	newRecord.length.seconds = atoi(strtok(NULL, ":"));
	token = strtokl(NULL, ",");
	newRecord.playcount = atoi(token);
	token = strtokl(NULL, ",");
	newRecord.rating = atoi(token);

	return newRecord;
}

//makes a node with record data and then inserts it at front of doubly linked list
int insertFront(Record data, Node** list) {
	Node* insertNode = makeNode(data);
	insertNode->rightNode = *list;
	if (*list != NULL)
		(*list)->leftNode = insertNode;
	*list = insertNode;
	return (bool)insertNode;
}

//Creates nodes LIFO from file 
int loadList(const char* fileName, Node** playList) {
	char oneline[1000] = { "\0" };
	char *token = NULL;
	Node *newNode = NULL;
	Record newRecord;
	FILE* infile = NULL;
	infile = fopen(fileName, "r");
	
	//check if file opened succesfully
	if (!infile) {
		printf("error reading file");
		return 0;
	}

	while(fgets(oneline, 1000, infile)){ // fgets grabs a single line returns null if EOF

		//make record
		newRecord = makeRecord(oneline);

		//insert front and make sure node was allocated
		if (!insertFront(newRecord, playList))
			return false;
	}

	printf("Records Loaded\n");
	fclose(infile);
	return true;
}

//writes to linked list data to csv file
void storeList(const char* fileName, Node* playList){
	FILE* outfile = NULL;
	Node* thisNode = playList;

	//check if list present
	if (!(playList)) {
		printf("list not loaded\n");
		return;
	}

	//open file
	outfile = fopen(fileName, "w");

	//go to end of list since list was loaded LIFO
	while (thisNode->rightNode)
		thisNode = thisNode->rightNode;

	while (thisNode) {
		fprintf(outfile, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
		fprintf(outfile, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
		thisNode = thisNode->leftNode;
	}
	printf("Records Stored\n");
	fclose(outfile);
}

//plays through from given node and increments playcount
void play(Node* song) {
	while (song) {
		printf("\nplaying %s\n", song->data.title);
		song->data.playcount++;
		for (int i = 0; i < 25; i++) {
			Sleep(100);
			printf(". ");
		}
		song = song->leftNode;
	}
	printf("\ndone playing\n");
	return;
}

//supports editing (a), rating (r), displaying (d) modes
//I do not specifically have a printList() function
//I felt it made more design sense to wrap this functionality into useList()
Node* useList(char* inString, Node* playList, char mode) {
	Node* thisNode = playList;
	char input[100];

	//check if list present
	if (!(playList)) {
		printf("list not loaded\n");
		return NULL;
	}

	//check if nothing entered
	if (*inString == '\n' || *inString == NULL) {
		if (mode == 'd')
			*inString = NULL;
		else {
			printf("Please enter something\n");
			return NULL;
		}
	}

	//go to end of list and work backwards since list was loaded LIFO
	while (thisNode->rightNode) {
		thisNode = thisNode->rightNode;
	}
	if (mode == 'a' || mode == 'r' || mode == 'd') {
		while (thisNode) {
			//if matches then print
			if (keywordMatch(thisNode->data.artist, inString)) {
				fprintf(stdout, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
				fprintf(stdout, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
				if (mode != 'd') {
					if (mode == 'a')
						fprintf(stdout, "Is this the song you would like to edit?\n");
					if (mode == 'r')
						fprintf(stdout, "Is this the song you would like to rate?\n");
					fgets(input, 100, stdin);
					if (tolower(*input) == 'y') {
						if (mode == 'a')
							editRecord(thisNode);
						else if (mode == 'r')
							editRating(thisNode);

						return thisNode;
					}
				}
			}
			thisNode = thisNode->leftNode;
		}
	}
	else if (mode == 'p') {
		while(thisNode){
			if (keywordMatch(thisNode->data.title, inString)) {
				fprintf(stdout, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
				fprintf(stdout, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
				fprintf(stdout, "Is this the song you would like to play?\n");
				fgets(input, 100, stdin);
				if (tolower(*input) == 'y') {
					play(thisNode);
					return thisNode;
				}
			}
			thisNode = thisNode->leftNode;
		}
		printf("done searching for songs\n");
	}
	return NULL;
}

//this is my own strtok functions which respects quoted literals
//the l in strtokl is for literal
char* strtokl(char* string, const char *delimiter) {
	static char* token;
	char* output;
	char* reader;
	int insideQuotes = 0;
	if (string)
		token = string;

	output = token;
	reader = token;

	while (!(*reader == *delimiter && !insideQuotes) && *reader != NULL) {
		if (*reader == '\"') {
			insideQuotes = !insideQuotes;
		}
		reader++;
	}
	*reader = NULL;
	token = ++reader;
	return output;
}

//returns 1 if all needles were found in haystack
//I E if all keywords were matched
int keywordMatch(const char* haystack, const char* needles) {
	//copy values over into 'safe' variables
	char safeHaystack[100];
	strcpy(safeHaystack, haystack);
	char safeNeedles[100];
	strcpy(safeNeedles, needles);
	char* keywords[100] = { "\0" };
	char* token = NULL;
	int i = 0;

	//remove newline from needles, won't remove newline if string is only newline
	strtok(safeNeedles, "\n");

	//if no needles then turn needles into empty string which will match everything
	if (*safeNeedles == '\n')
		*safeNeedles = NULL;

	//lowercase needles with sick one liner
	for (i = 0; safeNeedles[i]; ++i) safeNeedles[i] = tolower(safeNeedles[i]);

	//lowercase haystack with sick one liner
	for (i = 0; safeHaystack[i]; ++i) safeHaystack[i] = tolower(safeHaystack[i]);

	//split needles into keywords
	i = 0;
	keywords[i] = strtok(safeNeedles, " \t");
	i++;
	for (i; token = strtok(NULL, " \t"); i++)
		keywords[i] = token;

		//check if matches all keywords
	for (i = 0; keywords[i]; i++) {
		if (!strstr(safeHaystack, keywords[i]))
			break;
	}

		//if matched all keywords return true
	if (!keywords[i])
		return true;
	else
		return false;
}

//goes through record fields and allows user to edit them
int editRecord(Node* editNode) {
	char input[100];
	char changeMade = false;
	printf("Artist field currently set to: %s\n", editNode->data.artist);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(editNode->data.artist, input), changeMade = true;
	printf("Album field currently set to: %s\n", editNode->data.album);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(editNode->data.album, input), changeMade = true;
	printf("Title field currently set to: %s\n", editNode->data.title);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(editNode->data.title, input), changeMade = true;
	printf("Genre field currently set to: %s\n", editNode->data.genre);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(editNode->data.genre, input), changeMade = true;
	printf("Minutes field currently set to: %d\n", editNode->data.length.minutes);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') editNode->data.length.minutes = atoi(input), changeMade = true;
	printf("Seconds field currently set to: %d\n", editNode->data.length.seconds);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') editNode->data.length.seconds = atoi(input), changeMade = true;
	printf("Playcount field currently set to: %d\n", editNode->data.playcount);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') editNode->data.playcount = atoi(input), changeMade = true;
	printf("Rating field currently set to: %d\n", editNode->data.rating);
	while ((atoi(input) > 5 || atoi(input) < 1) && *input != '\n' && input != '\0') {
		printf("Enter new value from 1-5, or press enter:\n");
		fgets(input, 100, stdin);
	}
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') editNode->data.rating = atoi(input), changeMade = true;

	return changeMade;
}

//allows editing of rating field of given node
//this functionality might get refactored into editRecord
int editRating(Node* editNode) {
	char input[100] = {NULL};
	printf("Rating field currently set to: %d\n", editNode->data.rating);

	while (atoi(input) > 5 || atoi(input) < 1) {
		printf("Enter new value from 1-5, or press enter:\n");
		fgets(input, 100, stdin);
	}

	strtok(input, "\n");
	if (*input != '\n' && input != '\0') {
		editNode->data.rating = atoi(input);
		return true;
	}
	else
		return false;
}