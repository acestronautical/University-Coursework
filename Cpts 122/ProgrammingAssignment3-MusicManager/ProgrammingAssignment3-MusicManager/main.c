/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a digital music manager
* Date: 9/15/17
* Description: part two of music manager
*******************************************************************************************/
#include "header.h"

int main() {

	//declare stuff
	char userinput[3] = "0";
	int selection = 0;
	List list = { .start = NULL, .end = NULL };
	char* fileName = "musicplayList.csv";
	char inString[100];
	Record newRecord = {NULL};

	//menu loop
	while (selection != 11) {
		printf(
			"(1)   load\n"
			"(2)   store\n"
			"(3)   display\n"
			"(4)   insert\n"
			"(5)   delete\n"
			"(6)   edit\n"
			"(7)   sort\n"
			"(8)   rate\n"
			"(9)   play\n"
			"(10)  shuffle\n"
			"(11)  exit\n");

		//grab user string and convert to integer
		selection = atoi(fgets(userinput, 3, stdin));
		system("cls");
		switch (selection)
		{
		case 1:
			loadList(fileName, &list);
			break;
		case 2:
			storeList(fileName, list);
			break;
		case 3:
			printf("enter an artist name to display their songs\nor enter nothing for all songs\n");
			fgets(inString, 100, stdin);
			display(inString, list);
			break;
		case 4:
			newRecord = stringToRecord("empty, empty, empty, empty, 0:00, 0, 0");
			modifyRecord(&newRecord);
			insertFront(newRecord, &list);
			break;
		case 5:
			printf("enter a song name to delete song:\n");
			fgets(inString, 100, stdin);
			if (!deleteNode(findSong(inString, list), &list))
				printf("no records deleted\n");
			else
				printf("record deleted successfully\n");
			break;
		case 6:
			printf("enter an artist name to edit song fields for:\n");
			fgets(inString, 100, stdin);
			edit(inString, list);
			break;
		case 7:
			printf(
				"1.    Sort based on artist (A-Z)\n"
				"2.    Sort based on album title(A - Z)\n"
				"3.    Sort based on rating(1 - 5)\n"
				"4.    Sort based on times played(largest - smallest))\n");
			fgets(inString, 100, stdin);
			sort(&list, atoi(inString));
			break;
		case 8:
			printf("enter an artist name to edit song rating for:\n");
			fgets(inString, 100, stdin);
			rate(inString, list);
			break;
		case 9:
			printf("enter a song name to find song to play:\n");
			fgets(inString, 100, stdin);
			play(inString, list);
			break;
		case 10:
			break;
		case 11:
			storeList(fileName, list);
			break;
		default:
			system("cls");
			printf("invalid selection\n");
			system("pause");
			system("cls");
			break;
		}//end of switch case

		while (getc(stdin) != '\n'); //clears input buffer
		system("cls");
	} //menu loop breaks out here when selection is 11

	_fcloseall();
	return 0;
}