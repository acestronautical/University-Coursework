/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA8 - Interview Questions                                        *
* Date: 4-19-17                                                                            *
* Description: A series of Interview problems and thier solutions with tests               *
*******************************************************************************************/

#pragma once //i am not using ifndef guard code because pragma once accomplishes the same effect
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Structs
typedef struct occurrences
{
	int num_occurrences;
	double frequency;
} Occurrences;

//Functions prototypes
char* my_str_n_cat(char* dest_str, char* src_str, int num_chars);
bool TEST_my_str_n_cat();
bool binary_search(int* list, int list_size, int target, int** found_index);
bool TEST_binary_search();
void bubble_sort(char* word_list[], int word_list_size);
bool TEST_bubble_sort();
bool is_palindrome(char* str);
bool is_palindrome_recurse(char* str, int start, int end);
bool TEST_is_palindrome();
void maximum_occurences(char* input_string, Occurrences alphanumerics[43], int* max_occur, char* symbol_the_most);
bool TEST_maximum_occurences();
void max_consecutive_integers(signed int** grid, int rows, int columns, int** found_address, int* num_consecutive);
bool TEST_max_consecutive_integers();