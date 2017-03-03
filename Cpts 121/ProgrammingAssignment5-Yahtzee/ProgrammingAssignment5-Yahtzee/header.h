/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA5                                                              *
* Date: February 27, 2017                                                                  *
* Description: A game of Yahtzee,  playable in a win32 console                             *
*******************************************************************************************/

#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int roll_die(void);

void enter_to_continue(void);

void randomize_dice(char *dice, int sizeof_dice, char *hold_dice, int sizeof_hold_dice);

void hold_which_dice(char *hold_dice, int sizeof_hold_dice);

void print_dice(char *dice, int sizeof_dice);

void potential_scoring(char *dice, int sizeof_dice, char *potential_scores, int sizeof_potential_scores);

char sum_of_dice(char *dice, int sizeof_dice);

void print_score_card(char *scores, int sizeof_score_card);

#endif // !HEADER
