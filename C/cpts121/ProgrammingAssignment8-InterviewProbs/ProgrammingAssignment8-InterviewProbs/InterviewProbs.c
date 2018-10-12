/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA8 - Interview Questions                                        *
* Date: 4-19-17                                                                            *
* Description: A series of Interview problems and thier solutions with tests               *
*******************************************************************************************/
#include "header.h"

//1.(10 pts)Write a function called my_str_n_cat() that accepts pointer to a destination character array 
//and a pointer to a source character array and returns the pointer to the destination character array. 
//This function needs to copy at most n characters, character by character, 
//from the source character array to the end of the destination character array.
//If a null character is encountered before n characters have been encountered, copying must stop. 

//Quoting C11, chapter Åò7.24.3.2
//The strncat function appends not more than n characters(a null character and characters that follow it are not appended) 
//from the array pointed to by s2 to the end of the string pointed to by s1.
//The initial character of s2 overwrites the null character at the end of s1.
//A terminating null character is always appended to the result.

//I have written my function in accordance with C11 standard as the original prompt is unclear
//a null is always appended, it is up to the programmer to ensure that the destination has enough space
char* my_str_n_cat(char* dest_str, char* src_str, int num_chars) {
	int idx = 0, idy = 0;
	for (idx = 0; *(dest_str + idx) != NULL; idx++);
	for (idy = 0; *(src_str + idy) != NULL && (idy < num_chars); idy++)
		*(dest_str + idx + idy) = *(src_str + idy);

	*(dest_str + idx + idy) = NULL;

	return dest_str;
}

//This is the set of tests for my_str_n_cat()
//after performing the tests it checks against an expected result
//returns true if all test pass, or false if any test fails
bool TEST_my_str_n_cat(){
	char word_one[15] = "", word_two[15] = "";
	char* concated_word;
	int num;
	char* word_list_one[10] = { "lime", "dogs and ", "c", "it is fourteen", "boat", "", "abcdef", "ice", "123456789", "" };
	char* word_list_two[10] = { "coconut", "cats", "hat", "four", "s", "not blank", "ghijklmn", "ice baby", "ABCD", "" };
	char* expected_result[10] = { "limecoconut", "dogs and cats", "chat", "it is fourteen", "boats", "not blank", "abcdefghijklmn", "iceice baby", "123456789ABCD", "" };
	int num_chars[10] = { 7, 4, 3, 0, 1, 20, 8, 8, 4, 15 };
	bool success = true;
	printf("Test set for my_str_n_cat:\nperformed with size 15 char arrays)\n\n");
	for (int idx = 0; idx < 10; idx++) {
		strcpy(word_one, word_list_one[idx]);
		strcpy(word_two, word_list_two[idx]);
		num = num_chars[idx];
		printf("%d.\"%s\" concatenated with %d characters of \"%s\" results in",idx, word_one, num, word_two);
		concated_word = my_str_n_cat(word_one, word_two, num);
		printf(" \"%s\"\n", concated_word);

		if (strcmp(concated_word, expected_result[idx]) == 0)
			printf("Test Passed!\n");
		else
		{
			printf("Test Failed :(\n");
			success = false;
		}
	}
	if (success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return success;
}

//2.(10 pts) Recall Binary Search:
 //Input: a list of n SORTED integer values and a target value
//Output : True if target value exists in list and location of target value, false otherwise
//Write a C function called binary_search().

//determines if target exists within the passed array of integers in log(n) time
bool binary_search(int* list, int list_size, int target, int** found_index) {
	int start = 1;
	int end = list_size;
	bool success = false;
	*found_index = NULL;
	while (start <= end && !success) {
		if (*(list - 1 + (start + end) / 2) == target) {
			success = true;
			*found_index = (list - 1 + (start + end) / 2);
		}
		if (*(list - 1 + (start + end) / 2) > target)
			end = ((start + end) / 2) - 1;
		else if (*(list - 1 + (start + end) / 2) < target)
			start = ((start + end) / 2) + 1;
	}
	return success;
}

//This is the set of tests for binary_search
//after performing the tests it checks against an expected result
//returns true if all tests pass, or false if any test fails
bool TEST_binary_search() {
	int nums_one[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	int valid_targets_one[] = { 0, 3, 10, 18, 19 };
	int invalid_targets_one[] = { -49, -1, 20, 21, 50 };
	int nums_two[] = { 2, 3, 5, 6, 7, 11, 13, 17, 19, 23, 24, 25, 26, 27, 29, 31, 41, 43, 47, 53 };
	int valid_targets_two[] = { 2, 17, 19, 23, 53};
	int invalid_targets_two[] = { 0, 1, 34, 45, 54 };
	bool success = true;
	int* found_index = NULL;
	printf("Test set for binary_search:\n\n"
		"Searching the int array \n"
		"{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 }\n");
	for (int idx = 0; idx < 5; idx++)
	{
		printf("Searching for %d results in true    ", valid_targets_one[idx]);
		if (binary_search(nums_one, 20, valid_targets_one[idx], &found_index))
			printf("Test Passed!, target at address %p\n", found_index);
		else {
			printf("Test Failed :(\n");
			success = false;
		}
		printf("Searching for %d results in false   ", invalid_targets_one[idx]);
		if (!binary_search(nums_one, 20, invalid_targets_one[idx], &found_index))
			printf("Test Passed!, target at address %p\n", found_index);
		else {
			printf("Test Failed :(\n");
			success = false;
		}
	}
	printf("\nSearching the int array \n"
		"{ 2, 3, 5, 6, 7, 11, 13, 17, 19, 23, 24, 25, 26, 27, 29, 31, 41, 43, 47, 53 }\n");
	for (int idx = 0; idx < 5; idx++)
	{
		printf("Searching for %d results in true    ", valid_targets_two[idx]);
		if (binary_search(nums_two, 20, valid_targets_two[idx], &found_index))
			printf("Test Passed!, target at address %p\n", found_index);
		else {
			printf("Test Failed :(\n");
			success = false;
		}
		printf("Searching for %d results in false   ", invalid_targets_two[idx]);
		if (!binary_search(nums_two, 20, invalid_targets_two[idx], &found_index))
			printf("Test Passed!, target at address %p\n", found_index);
		else {
			printf("Test Failed :(\n");
			success = false;
		}
	}
	if (success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return success;
}

//3.(20 pts) Write a function called bubble_sort() that accepts an array of pointers to strings 
//and the number of strings as arguments, and returns nothing. 
//Your implementation for this function may NOT use strcpy().
//You may only exchange or swap pointers, but NOT actually make copies of the strings!

//Bubble sorts a list of strings ascending "alphabetically" (not actually alphabetical) using strcmp
void bubble_sort(char* word_list[], int word_list_size) {
	char* swap = NULL;
	while (word_list_size) {
		for (int idx = 1; idx < word_list_size; idx++) {
			if (strcmp(word_list[idx - 1], word_list[idx]) > 0)
				swap = word_list[idx - 1], word_list[idx - 1] = word_list[idx], word_list[idx] = swap;
		}
		word_list_size = word_list_size - 1;
	}
}

//This is the set of tests for binary_search
//after performing the tests it checks against an expected result
//returns true if all tests pass, or false if any test fails
bool TEST_bubble_sort() {
	bool test_success = true;
	bool overall_success = true;
	char* word_list_one[] = { "zebra","charlie", "delta", "foxtrot", "ALPHA", "geronimo", "canteen", "alpha", "quicksilver", "beta" };
	char* word_list_one_result[] = { "ALPHA", "alpha", "beta", "canteen", "charlie", "delta", "foxtrot", "geronimo", "quicksilver", "zebra" };

	char* word_list_two[] = {"dog", "ball", "cat", "ampersand", "1", "2", "0", "!*&", "apple pie", "candied peach cobbler"};
	char* word_list_two_result[] = { "!*&", "0", "1", "2", "ampersand", "apple pie", "ball", "candied peach cobbler", "cat", "dog" };

	printf("Test set for bubble sort:\n\n");
	printf("sorting");
	for (int idx = 0; idx < 10; idx++)
		printf(" \"%s\"", word_list_one[idx]);
	printf("\nyields");
	bubble_sort(word_list_one, 10);
	for (int idx = 0; idx < 10; idx++) {
		printf(" \"%s\"", word_list_one[idx]);
		if (strcmp(word_list_one[idx], word_list_one_result[idx]) != 0)
			test_success = false;
	}
	if (test_success)
		printf("\nTest Passed!\n\n");
	else
	{
		printf("\nTest Failed :(\n\n");
		overall_success = false;
	}

	printf("sorting");
	for (int idx = 0; idx < 10; idx++)
		printf(" \"%s\"", word_list_two[idx]);
	printf("\nyields");
	bubble_sort(word_list_two, 10);
	for (int idx = 0; idx < 10; idx++) {
		printf(" \"%s\"", word_list_two[idx]);
		if (strcmp(word_list_two[idx], word_list_two_result[idx]) != 0)
			test_success = false;
	}
	if (test_success)
		printf("\nTest Passed!\n\n");
	else
	{
		printf("\nTest Failed :(\n\n");
		overall_success = false;
	}

	if (overall_success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return overall_success;
}

//4.(15 pts) Write a recursive function called is_palindrome() that accepts a pointer to a string and its length, 
//and recursively determines if the string is a palindrome.The function must return 1 for a palindrome, 0 otherwise.
//A palindrome is a sequence of symbols that may be interpreted the same forward and backward.
//For example, Ågrace carÅh.Note: whitespace should be ignored in your solution.

//checks if a given string is a palindrome including whitespace
bool is_palindrome(char* str)
{
	int end = strlen(str) - 1;
	int start = 0;
	return is_palindrome_recurse(str, start, end);
}

//utility function for is_palindrome to allow is_palindrome to accept only one argument
bool is_palindrome_recurse(char* str, int start, int end)
{
	if (str[end] == ' ')
		end = end - 1;
	if (str[start] == ' ')
		start = start + 1;
	if (start >= end)
		return true;
	if (str[start] != str[end])
		return false;

	return is_palindrome_recurse(str, start + 1, end - 1);
}

//This is the set of tests for is_palindrome
//after performing the tests it checks against an expected result
//returns true if all tests pass, or false if any test fails
bool TEST_is_palindrome() {
	char word_one[15] = "", word_two[15] = "";
	char* palindromes[10] = { "racecar", "race car", "c", "aaa", "a toyota race fast safe car a toyota", "", "abc c b a", "bobob", "1234321", "   " };
	char* not_palindromes[10] = { "coconut", "cats", "hat", "four", "abc", "not blank", "ghijklmn", "ice baby", "ABCD", "50" };
	bool success = true;
	printf("Test set for is_palindrome():\n\n");
	for (int idx = 0; idx < 10; idx++) {
		printf("checking \"%s\" results in true\n", palindromes[idx]);
		if (is_palindrome(palindromes[idx]))
			printf("Test Passed!\n");
		else
		{
			printf("Test Failed :(\n");
			success = false;
		}
		printf("checking \"%s\" results in false\n", not_palindromes[idx]);
		if (!is_palindrome(not_palindromes[idx]))
			printf("Test Passed!\n");
		else
		{
			printf("Test Failed :(\n");
			success = false;
		}
	}
	if (success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return success;
}

//5.(20 pts) Write a recursive function called sum_primes() that accepts an unsigned integer, n, as an argument, 
//and returns the sum of all primes from 2 to n. You must use recursion to solve this problem!

//sums all primes from 2 to n, including n
int sum_primes(int n) {
	for (int idy = 2; idy < n && n > 1; idy++) {
			if (n % idy == 0) {
				n = n - 1;
				idy = 2;
			}
		}
		if (n <= 1)
			return 0;
		else
			return n + sum_primes(n - 1);
}

//This is the set of tests for sum_primes
//after performing the tests it checks against an expected result
//returns true if all tests pass, or false if any test fails
bool TEST_sum_primes() {
	int n[] = { 0, 2, 10, 31, 101 };
	int expected_result[] = { 0, 2, 17, 160, 1161};
	bool success = true;
	printf("Test set for sum_primes:\n\n");
	for (int idx = 0; idx < 5; idx++) {
		printf("checking %d results in %d\n", n[idx], sum_primes(n[idx]));
		if (sum_primes(n[idx]) == expected_result[idx])
			printf("Test Passed!\n");
		else
		{
			printf("Test Failed :(\n");
			success = false;
		}
	}
	if (success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return success;
}

//(25 pts) Write a function called maximum_occurences() that accepts a pointer to a string 
//(consisting of alphanumeric and whitespace characters only), a pointer to an array of struct occurrences,  
//a pointer to an integer, and a pointer to a character as arguments.
 //The function determines the frequency of each character found in the array.
//The frequency is defined as : number of one character symbol / total number of characters.
//The function should use the second array argument(of struct occurrences) to keep track of the frequency of each character.
//Also, it must return, through the pointers, the maximum number of occurrences of any one character 
//and the corresponding character for which the maximum represents.
//Thus, for a string such as Ågtest stringÅh, ÅetÅf occurs 3 times, which is the maximum occurrences for any one character in the string.

//counts the occurence and frequency of all alphanumeric characters in a given string 
//and returns the character with the most occurence and the number of occurences via pointers
//intentionally does not distuinguish between upper and lower case letters
//in case of a tie returns the character with the lower ascii value is returned
//if passed an empty string the character pointer is unmodified and 0 occurrences is returned
void maximum_occurences(char* input_string, Occurrences alphanumerics[43], int* max_occur, char* symbol_the_most) {
	//parallel array to alphanumerics
	char symbols[43] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	int string_length = strlen(input_string);
	int spaces = 0;
	*max_occur = alphanumerics[0].num_occurrences;
	for (int idx = 0; idx < string_length; idx++) {
		if (*(input_string + idx) == ' ')
			spaces += 1;
		else
			alphanumerics[(int)(toupper(*(input_string + idx)) - 48)].num_occurrences += 1;
	}
	for (int idx = 0; idx < 43; idx++)
		alphanumerics[idx].frequency = (double)alphanumerics[idx].num_occurrences / (string_length - spaces);
	for (int idx = 0; idx < 43; idx++) {
		if (alphanumerics[idx].num_occurrences > *max_occur)
			*max_occur = alphanumerics[idx].num_occurrences, *symbol_the_most = tolower(symbols[idx]);
	}
}

//This is the set of tests for maximum occurences
//after performing the tests it checks against an expected result
//returns true if all tests pass, or false if any test fails
bool TEST_maximum_occurences() {
	bool success = true;
	Occurrences alphanumerics[43] = { 0 };
	int most_occurences = 0;
	char symbol = 'a';
	char symbols[43] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	char* strings[] = { "test string", "banana", "1234567890", "", "kill a bird in the living room then look like most innocent animal", "The quick brown fox jumps over the lazy dog", "zz z z zz" };
	char expected_symbol[] = { 't', 'a', '0', '0', 'i', 'o', 'z' };
	int expected_num[] = { 3, 3, 1, 0, 8, 4, 6 };
	printf("Test set for maximum_occurences():\n\n");
	for (int idx = 0; idx < sizeof strings / sizeof strings[0]; idx++) {
		for (int idy = 0; idy < 43; idy++)
			alphanumerics[idy].num_occurrences = 0, alphanumerics[idy].frequency = 0;

		maximum_occurences(strings[idx], alphanumerics, &most_occurences, &symbol);
		printf("checking the string \"%s\"\ngives symbol '%c' with %d occurences and frequency %.2lf\n", strings[idx], symbol, most_occurences, alphanumerics[toupper(symbol) - 48].frequency);
		if (most_occurences == expected_num[idx] && symbol == expected_symbol[idx])
			printf("Test Passed!\n");
		else
		{
			printf("Test Failed :(\n");
			success = false;
		}
	}
	if (success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return success;
}

//7. (20 pts - BONUS) Write a function called max_consecutive_integers() that accepts a two-dimensional array of signed integers, 
//the number of rows, the number of columns as input parameters, and two pointers as output parameters 
//(one of these pointers is actually a pointer to a pointer, i.e. two stars!). 
//The function finds the maximum consecutive sequence of one integer. 
//The first pointer stores the address the start of the maximum consecutive sequence of the same integer. 
//The second indirectly stores the number the same consecutive integers in a row. 
//These sequences may wrap from one row to the next. For example ([$xxxx] denotes address value):

void max_consecutive_integers(signed int** grid, int rows, int columns, int** found_address, int* num_consecutive) {
	*found_address = NULL;
	*num_consecutive = 0;
	bool success = false;
	int in_a_row = 0;
	int* sequence_start = NULL;
	int idx = 0;
	while (idx < rows *  columns - 1) {
		in_a_row = 1;
		sequence_start = grid + idx;
		if (*(grid + idx) == *(grid + idx + 1)) {
			while (*(grid + idx) == *(grid + idx + 1)) {
				in_a_row += 1;
				idx += 1;
				if (in_a_row > *num_consecutive) {
					*num_consecutive = in_a_row;
					*found_address = sequence_start;
				}
			}
		}
		else {
			idx += 1;
		}
	}
}

//This is the set of tests for max consecutive integers
//after performing the tests it checks against an expected result
//returns true if all tests pass, or false if any test fails
bool TEST_max_consecutive_integers() {
	signed int grid_one[3][2] = { { 2, 3 },{ 3, 3 },{ 3, 4 } };
	signed int grid_two[3][3] = { { 2 , 2, 3 },{ 3, 4, 4 },{ 4, 4, 4 } };
	signed int grid_three[4][3] = { { 1 , 2, 3 },{ 1, 3, 10 },{ 10, 1, 4 }, { 2, 5, 9 } };

	int* found_address = NULL;
	int num_consecutive = 0;
	bool success = true;
	printf("Test set for max_consecutive_integers():\n\n");

	max_consecutive_integers(grid_one, 3, 3, &found_address, &num_consecutive);
	printf("check grid  { { 2, 3 },{ 3, 3 },{ 3, 4 } } at address %p\nreturns %d consecutive and sequence start at %p\n", &grid_one, num_consecutive, found_address);
	if (num_consecutive == 4)
		printf("Test Passed!\n");
	else {
		printf("Test Failed :(\n");
		success = false;
	}
	max_consecutive_integers(grid_two, 3, 3, &found_address, &num_consecutive);
	printf("check grid  { { 2 , 2, 3 },{ 3, 4, 4 },{ 4, 4, 4 } } at address %p\nreturns %d consecutive and sequence start at %p\n", &grid_one, num_consecutive, found_address);
	if (num_consecutive == 5)
		printf("Test Passed!\n");
	else {
		printf("Test Failed :(\n");
		success = false;
	}
	max_consecutive_integers(grid_three, 3, 3, &found_address, &num_consecutive);
	printf("check grid  { { 1 , 2, 3 },{ 1, 3, 10 },{ 10, 1, 4 }, { 2, 5, 9 } } at address %p\nreturns %d consecutive and sequence start at %p\n", &grid_one, num_consecutive, found_address);
	if (num_consecutive == 2)
		printf("Test Passed!\n");
	else {
		printf("Test Failed :(\n");
		success = false;
	}
	if (success)
		printf("\nAll tests passed\n");
	else
		printf("\nSome tests failed\n");
	return success;
}


