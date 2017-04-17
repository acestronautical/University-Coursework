/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA7 - Poker                                                      *
* Date: 4-12-17                                                                            *
* Description: A game where you play poker with your aunt, no betting occurs               *
*******************************************************************************************/
#ifndef Header_Poker
#define Header_Poker

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>   
#include <stdio.h>   
#include <windows.h>  

//Type Definitions
typedef enum face {
Deuce, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
} Face;
typedef enum suite {
	Hearts, Diamonds, Clubs, Spades
} Suite;
typedef enum ranking{
	high_card, one_pair, two_pair, three_of, a_straight, a_flush, full_house, four_of, straight_flush, royal_flush
} Ranking;

typedef struct card
{	Face face;
	Suite suite;
	int ofakind;
	bool valuable;
}Card;

//pause and clear screen
void refresh_screen();

//Function Definitions
//originally shuffle function but renamed because it doesn't technically "shuffle" it initializes the deck to random values 
void init_deck_random(int deck[4][13]);

//deal a card from the deck and remove that card from the deck
Card deal_card(int deck[4][13]);

//deals a hand of 5 using Card hand[5] array as output parameter
//employs the deal_card function five times
void deal_hand(int deck[4][13], Card hand[5]);

//Displays a hand of five
void show_hand(Card hand[5], bool Greg);

void show_hands(Card opponent_hand[5], bool show_opponent, Card own_hand[5], bool show_own);

//returns a hand rank with higher values being better hands
Ranking evaluate_hand(Card hand[5]);

//comparison function for using qsort
int compare(Card *elem1, Card *elem2);

//uses qsort to put hand into ascending order
void sort_hand(Card hand[5]);

//determines if hand contains a flush
bool is_flush(Card hand[5]);

//determines if a hand contains a straight
bool is_straight(Card hand[5]);

//determine if a hand contains high card, pair, two pair, three of a kind, full house, or four of a kind
Ranking of_a_kind(Card hand[5]);

//discard and draw cards, manual for Greg , automated for Debbie. Returns number of cards discarded.
int discard_and_draw(Card hand[5], int deck[4][13], bool Greg);

//compare hands and see who won
int who_won(Card Greg_hand[5], Card Debbie_hand[5]);

//talks trash
void talk_trash(bool Debbie);

#endif // !Header_Poker
