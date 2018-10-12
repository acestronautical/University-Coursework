/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a digital music manager
* Date: 9/3/17
* Description:
*******************************************************************************************/
#include "header.h"

int main() {

	//declare stuff
	char userinput[3] = "0";
	int selection = 0;
	Node *list = NULL;
	char* fileName = "musicplayList.csv";
	char artist[100];

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
		strcpy(userinput, fgets(userinput, 3, stdin));
		selection = atoi(userinput);

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
			fgets(artist, 100, stdin);
			useList(artist, list, 'd');
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			printf("enter an artist name to edit song fields for:\n");
			fgets(artist, 100, stdin);
			useList(artist, list, 'a');
			break;
		case 7:
			break;
		case 8:
			printf("enter an artist name to edit song rating for:\n");
			fgets(artist, 100, stdin);
			useList(artist, list, 'r');
			break;
		case 9:
			printf("enter a song name to find song to play:\n");
			fgets(artist, 100, stdin);
			useList(artist, list, 'p');
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