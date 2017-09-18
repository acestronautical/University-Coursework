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
Record stringToRecord(char* oneLine) {
	char safeLine[100] = "";
	strcpy(safeLine, oneLine);
	char* token;
	Record newRecord;
	//enter data into record
	token = strtokl(safeLine, ",");
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
int insertFront(Record data, List* list) {
	Node* insertNode = makeNode(data);
	if (list->start) {
		list->start->leftNode = insertNode;
	}
	else
		list->end = insertNode;
	insertNode->rightNode = list->start;
	list->start = insertNode;
	return (bool)insertNode;
}

bool deleteNode(Node* deleteNode, List* list) {
	if (!deleteNode)
		return false;
	if (deleteNode == list->start && deleteNode == list->end)
		list->start = NULL, list->end = NULL;
	else if (deleteNode == list->start) {
		if (deleteNode->rightNode) 
			deleteNode->rightNode->leftNode = NULL;
		list->start = deleteNode->rightNode;
	}
	else if (deleteNode == list->end) {
		list->end = deleteNode->leftNode;
		deleteNode->leftNode->rightNode = NULL;
	}
	else {
		deleteNode->leftNode->rightNode = deleteNode->rightNode;
		deleteNode->rightNode->leftNode = deleteNode->leftNode;
	}
	free(deleteNode);
	return true;
}

//Creates nodes LIFO from file 
int loadList(const char* fileName, List* list) {
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
	if (!list->start) {
		while (fgets(oneline, 1000, infile)) { // fgets grabs a single line returns null if EOF

			//make record
			newRecord = stringToRecord(oneline);

			//insert front and make sure node was allocated
			if (!insertFront(newRecord, list))
				return false;
		}

		printf("Records Loaded\n");
		fclose(infile);
		return true;
	}
	else
		printf("list already present\n");
	return false;
}

//writes to linked list data to csv file
void storeList(const char* fileName, List list) {
	FILE* outfile = NULL;
	Node* thisNode = list.end;
	//check if list present
	if (!(thisNode)) {
		printf("list not loaded\n");
		return;
	}
	//open file
	outfile = fopen(fileName, "w");

	while (thisNode) {
		fprintf(outfile, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
		fprintf(outfile, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
		thisNode = thisNode->leftNode;
	}
	printf("Records Stored\n");
	fclose(outfile);
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

//goes through record fields and allows user to edit them, returns a boolean
bool modifyRecord(Record* data) {
	char input[100];
	char changeMade = false;
	printf("Artist field currently set to: %s\n", data->artist);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(data->artist, input), changeMade = true;
	printf("Album field currently set to: %s\n", data->album);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(data->album, input), changeMade = true;
	printf("Title field currently set to: %s\n", data->title);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(data->title, input), changeMade = true;
	printf("Genre field currently set to: %s\n", data->genre);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') strcpy(data->genre, input), changeMade = true;
	printf("Minutes field currently set to: %d\n", data->length.minutes);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') data->length.minutes = atoi(input), changeMade = true;
	printf("Seconds field currently set to: %d\n", data->length.seconds);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') data->length.seconds = atoi(input), changeMade = true;
	printf("Playcount field currently set to: %d\n", data->playcount);
	printf("Enter new value, or press enter:\n");
	fgets(input, 100, stdin);
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') data->playcount = atoi(input), changeMade = true;
	printf("Rating field currently set to: %d\n", data->rating);
	while ((atoi(input) > 5 || atoi(input) < 1) && *input != '\n' && input != '\0') {
		printf("Enter new value from 1-5, or press enter:\n");
		fgets(input, 100, stdin);
	}
	strtok(input, "\n");
	if (*input != '\n' && input != '\0') data->rating = atoi(input), changeMade = true;

	return changeMade;
}

//allows editing of rating field of given node
//this functionality might get refactored into inputRecord
bool modifyRating(Record* data) {
	char input[100] = {NULL};
	printf("Rating field currently set to: %d\n", data->rating);

	while (atoi(input) > 5 || atoi(input) < 1) {
		printf("Enter new value from 1-5, or press enter:\n");
		fgets(input, 100, stdin);
	}

	strtok(input, "\n");
	if (*input != '\n' && input != '\0') {
		data->rating = atoi(input);
		return true;
	}
	else
		return false;
}

Node* findArtist(char* inString, List list){
	Node* thisNode = list.end;
	char input[100];

	//check if list present
	if (!(thisNode)) {
		printf("list not loaded\n");
		return NULL;
	}

	//check if nothing entered
	if (*inString == '\n' || *inString == NULL) {
			printf("Please enter something\n");
			return NULL;
		}

		while (thisNode) {
			//if matches then print and ask to edit
			if (keywordMatch(thisNode->data.artist, inString)) {
				char input[100] = { '\0' };
				fprintf(stdout, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
				fprintf(stdout, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
				fprintf(stdout, "Select this record?\n");
				fgets(input, 100, stdin);
				if (tolower(*input) == 'y')
					return thisNode;
			}
			thisNode = thisNode->leftNode;
		}
	return NULL;
}

Node* findSong(char* inString, List list) {
	Node* thisNode = list.end;
	char input[100];

	//check if list present
	if (!(thisNode)) {
		printf("list not loaded\n");
		return NULL;
	}

	//check if nothing entered
	if (*inString == '\n' || *inString == NULL) {
		printf("Please enter something\n");
		return NULL;
	}

	while (thisNode) {
		//if matches then print and ask to edit
		if (keywordMatch(thisNode->data.title, inString)) {
			char input[100] = { '\0' };
			fprintf(stdout, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
			fprintf(stdout, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
			fprintf(stdout, "Select this record?\n");
			fgets(input, 100, stdin);
			if (tolower(*input) == 'y')
				return thisNode;
		}
		thisNode = thisNode->leftNode;
	}
	return NULL;
}

void display(char* inString, List list) {
	Node* thisNode = list.end;
	//check if nothing entered
	if (*inString == '\n' || *inString == NULL)
		*inString = NULL;
		while (thisNode) {
			//if matches then print and ask to edit
			if (keywordMatch(thisNode->data.artist, inString)) {
				char input[100] = { '\0' };
				fprintf(stdout, "%s,%s,%s,%s,", thisNode->data.artist, thisNode->data.album, thisNode->data.title, thisNode->data.genre);
				fprintf(stdout, "%d:%d,%d,%d\n", thisNode->data.length.minutes, thisNode->data.length.seconds, thisNode->data.playcount, thisNode->data.rating);
			}
			thisNode = thisNode->leftNode;
		}
	return;
}

Node* edit(char* inString, List list) {
	Node* thisNode = findArtist(inString, list);
	if (thisNode)
		modifyRecord(&(thisNode->data));
	return thisNode;
}

Node* rate(char* inString, List list) {
	Node* thisNode = findArtist(inString, list);
	if (thisNode)
		modifyRating(&(thisNode->data));
	return thisNode;
}

//plays through from given node to end of playlist and increments playcount
void play(char* inString, List list) {
	Node* song = findSong(inString, list);
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


Node* sort(List* list, int mode) {
	Record tempRecord = { NULL };
	Node* sortNode = list->start;
	char string1[100] = { '\0' };
	char string2[100] = {'\0'};
	int int1 = 0;
	int int2 = 0;
	bool swaps = true;
	if (mode > 4 || mode < 1) {
		printf("invalid selection\n");
		return NULL;
	}
	while (swaps) {
		sortNode = list->start;
		swaps = false;
		while (sortNode->rightNode) {
			if (mode == 1 || mode == 2) {
				if (mode == 1) {
					strcpy(string1, lowercase(sortNode->data.artist));
					strcpy(string2, lowercase(sortNode->rightNode->data.artist));
				}
				else if (mode == 2) {
					strcpy(string1, lowercase(sortNode->data.title));
					strcpy(string2, lowercase(sortNode->rightNode->data.title));
				}
				if (strcmp(string2, string1) == 1) {
					tempRecord = sortNode->data;
					sortNode->data = sortNode->rightNode->data;
					sortNode->rightNode->data = tempRecord;
					swaps = true;
				}
			}
			else {
				if (mode == 3) {
					int1 = sortNode->data.rating;
					int2 = sortNode->rightNode->data.rating;
				}
				else if (mode == 4) {
					int1 = sortNode->data.playcount;
					int2 = sortNode->rightNode->data.playcount;
				}
				if (int1 > int2) {
					tempRecord = sortNode->data;
					sortNode->data = sortNode->rightNode->data;
					sortNode->rightNode->data = tempRecord;
					swaps = true;
				}
			}
			sortNode = sortNode->rightNode;
		}
	}

	return list;
}

char* lowercase(char* artist) {
	char safeArtist[100] = { NULL };
	strcpy(safeArtist, artist);
	for (int i = 0; safeArtist[i]; ++i) safeArtist[i] = tolower(safeArtist[i]);
	if (*safeArtist == '\"')
		strcpy(safeArtist, safeArtist + 1);
	return safeArtist;
}

Node* shuffleList(List* list) {
	srand(time(NULL));
	List shuffled = { NULL};
	Node* thisNode = list->start;
	Record tempRecord = { NULL };
	int randCount = 0;
	int listLength = 0;

	while (thisNode) {
		listLength++;
		thisNode = thisNode->rightNode;
	}

	while (listLength > 0) {
		thisNode = list->start;
		randCount = rand() % listLength;
		for (int i = 0; i < randCount; i++) {
			thisNode = thisNode->rightNode;
		}
		tempRecord = thisNode->data;
		deleteNode(thisNode, list);
		insertFront(tempRecord, &shuffled);
		listLength--;
	}
	list->start = shuffled.start;
	thisNode = list->start;
	while (thisNode->rightNode)
		thisNode = thisNode->rightNode;
	list->end = thisNode;
	return list;
}