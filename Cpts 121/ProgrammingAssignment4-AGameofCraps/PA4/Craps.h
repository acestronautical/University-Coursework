/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA4                                                              *
* Date: February 13, 2017                                                                  *
* Description: A game of craps,  playable in a win32 console                               *
*******************************************************************************************/

#ifndef _HEADER_H
#define _HEADER_H

//Includes
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

//disable security warnings
#define _CRT_SECURE_NO_WARNING

//Add support for until statements
#define until(exp) while(!(exp))

//FUNCTION PROTOTYPES/DECLARATIONS

void print_game_rules(void); 
//Prints out the rules of the game of "craps".

double get_bank_balance(void); 
//Prompts the player for an initial bank balance from which wagering will be added or subtracted.The player entered bank balance(in dollars, i.e.$100.00) is returned.

double get_wager_amount(void); 
//Prompts the player for a wager on a particular roll.The wager is returned.

int check_wager_amount(double wager, double balance); 
//Checks to see if the wager is within the limits of the player's available balance. If the wager exceeds the player's allowable balance, then 0 is returned; otherwise 1 is returned.

void wager_banter(double wager_amount);
//says funny stuff about your wager amount

void eat_input_buffer(void);
//pulls character out of the input buffer until newline or EOF

int roll_die(void); 
//Rolls one die.This function should randomly generate a value between 1 and 6, inclusively.Returns the value of the die.

int calculate_sum_dice(int die1_value, int die2_value); 
//Sums together the values of the two dice and returns the result.Note: this result may become the player's point in future rolls.

int is_win_loss_or_point(int sum_dice); 
//Determines the result of the first dice roll.If the sum is 7 or 11 on the roll, the player wins and 1 is returned.If the sum is 2, 3, or 12 on the first throw (called "craps"), the player loses(i.e.the "house" wins) and 0 is returned.If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's "point" and -1 is returned.

int is_point_loss_or_neither(int sum_dice, int point_value); 
//Determines the result of any successive roll after the first roll.If the sum of the roll is the point_value, then 1 is returned.If the sum of the roll is a 7, then 0 is returned.Otherwise, -1 is returned.

double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract); 
//If add_or_subtract is 1, then the wager amount is added to the bank_balance.If add_or_subtract is 0, then the wager amount is subtracted from the bank_balance.Otherwise, the bank_balance remains the same.The bank_balance result is returned.

void number_rolls_banter(int number_rolls);
//banters based on how many rolls have passed

void win_loss_banter(int win_loss_neither);
//banters based on how many win loss or neither have passed

void bank_balance_banter(double initial_bank_balance, double current_bank_balance);
//banters based on net loss/winnings

void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);
//Prints an appropriate message dependent on the number of rolls taken so far by the player
//the current balance, and whether or not the player just won his roll
//The parameter win_loss_neither indicates the result of the previous roll.

void print_dice_art(void);
//prints ascii dice art 

void enter_to_continue(void);
//makes a press enter to continue delay

void print_goodbye(void);
//prints ascii goodbye text

#endif // !_HEADER_H