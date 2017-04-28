/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA8 - Interview Questions                                        *
* Date: 4-19-17                                                                            *
* Description: A series of Interview problems and thier solutions with tests               *
*******************************************************************************************/
#include "header.h"

int main(void)
{
	char userinput = 1;
	while (userinput != '0') {
		printf(
			"Select which function you would like to test\n\n"
			"\t0. EXIT\n\n"
			"\t1. char* my_str_n_cat\n"
			"\t2. bool binary_search\n"
			"\t3. void bubble_sort\n"
			"\t4. bool is_palindrome\n"
			"\t5. int sum_primes\n"
			"\t6. void maximum_occurences\n"
			"\n"
			"\t7. void max_consecutive_integers\n"
		);
		userinput = getche();
		system("cls");
		switch (userinput)
		{
		case '1':
			TEST_my_str_n_cat();
			break;
		case '2':
			TEST_binary_search();
			break;
		case '3':
			TEST_bubble_sort();
			break;
		case '4':
			TEST_is_palindrome();
			break;
		case '5':
			TEST_sum_primes();
			break;
		case '6':
			TEST_maximum_occurences();
			break;
		case '7':
			TEST_max_consecutive_integers();
			break;
		default:
			break;
		}

		getch();
		system("cls");
	}
	return 0;
}