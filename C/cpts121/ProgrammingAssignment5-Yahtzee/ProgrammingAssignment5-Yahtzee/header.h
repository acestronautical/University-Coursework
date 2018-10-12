/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA5                                                              *
* Date: February 27, 2017                                                                  *
* Description: A game of Yahtzee,  playable in a win32 console                             *
*******************************************************************************************/

#ifndef HEADER
#define HEADER

//Macros used to change color of text
#define BLUE_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)
#define RED_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define GREEN_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define WHITE_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <wincon.h>


//Prints out the rules of the game of yahtzee.
void print_game_rules(void);

//Prints out a chart of scoring combinations for yahtzee
void print_scoring_combinations(void);

//prompts if the user wants to play and outputs a boolean
int want_to_play();

//pulls character out of the input buffer until newline or EOF
void eat_input_buffer(void);

//instructs user on controls etc..
void how_to_play();

//yahtzee game code game
int play_game();

//rolls a single die
int roll_die(void);

//gets characters until one of them is newline
void enter_to_continue(void);

//enters a random value from 1-6 in all elements of passed array for which parralel hold array is false
void randomize_dice(int *dice, int sizeof_dice, int *hold_dice, int sizeof_hold_dice);

//uses getche() prompt to propagate all elements of hold array with boolean values
//0 or 'n' or 'N' are false all others are true
void hold_which_dice(int *hold_dice, int sizeof_hold_dice);

//roll dice, prompt which to hold, reroll non held dice, prompt which to hold, reroll non held dice, reset hold dice array to 0's
void player_rolls(int *dice, int sizeof_dice, int *hold_dice, int sizeof_hold_dice);

//prints any number of 6 sided dice values from an array horizontally with ascii art 
void print_dice(int *dice, int sizeof_dice);

//iterates through all possible scorings and saves the values into potential_scores
void potential_scoring(int *dice, int sizeof_dice, int *potential_scores, int sizeof_potential_scores);

//compares scores already entered on scorecard with potential scores for round
//removes scores from potential scores for round if they have already been scored
//special case for yahtzee to allow multiple yahtzee's to score
void compare_and_remove_scores(int *scores, int size_scores, int *potential_scores, int sizeof_potential_scores);

//prompts  user to select the letter next to the score they want to use
//maps 'A'-'M' && 'a'-'m' to 0-12 array indices with switch case
//re prompts if value in potential scores for selection if -1
void select_score(int *potential_scores, int sizeof_potential_scores, int *selection, int sizeof_selection);

//iterates through an array and adds all elements of the array, returns the sum
int sum_of_array(int *dice, int sizeof_dice);

//looks for target value in given array and sums up all matching elements, returns the sum EX: add all ones in an array
int sum_of_target(int target, int *array, int sizeof_array);

//uses macro defined SetConsoleTextAttribute to switch text from red to white 
//logically prints enterable scores red and previously entered scores white using ternary expressions
void print_score_card(int *scores, int sizeof_scores, int *potential_scores, int sizeof_potential_scores);

//checks if all elements of the score card array are not -1
// -1 signifies emptiness in this program
int score_card_full(int *scores, int sizeof_scores);

//calculates bonus and total score and puts them into end of array
void score_bonus_and_total(int *scores, int sizeof_scores);

#endif // !HEADER
