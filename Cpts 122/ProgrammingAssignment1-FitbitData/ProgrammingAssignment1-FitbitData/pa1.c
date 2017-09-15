/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 122, Fall  2017; Lab Section 2                                               *
* Programming Assignment: PA1 - Fitbit Data                                                *
* Date: 8-26-17                                                                            *
* Description: A program which reads in fitbit data and runs some analyses                 *
*******************************************************************************************/

#include "header.h"

//Takes in a string and puts a value between double delimiters (strtok hates double delims)
//Returns nothing, but edits string argument destructively
void preprocessline(char line[], char delim, char value) {
	int index1 = 1;
	int index2 = 0;
	char temp = '\0';
	char swap = '\0';
	while (line[index1] != '\0') {
		if ((line[index1 - 1] == delim) && (line[index1] == delim)) {
			index2 = index1;
			line[index2] = value;
			index2++;
			temp = line[index2];
			line[index2] = ',';
			do {
				index2++;
				swap = line[index2];
				line[index2] = temp;
				temp = swap;
			} while (swap != '\0');
			index2++;
			line[index2] = '\0';
		}
		index1++;
	}
}