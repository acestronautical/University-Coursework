/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA7 - Poker                                                      *
* Date: 4-12-17                                                                            *
* Description: A game where you play poker with your aunt, no betting occurs               *
*******************************************************************************************/
#include "Header.h"

//pause and clear screen
void refresh_screen(){
	printf("\n ");
	system("pause");
	system("cls");
}

//originally shuffle function but renamed because it doesn't technically "shuffle" it initializes the deck to random values 
//this code was provided to us and we were not allowed to radically change it. It is not good code.
void init_deck_random(int deck[4][13]){
	int row = 0;    //row represents suite
	int column = 0; //column represents face
	int card = 0;   //card number represents position in deck e.g. top == 1 bottom == 52

	//reset deck
	for (row = 0; row < 4; row++){
		for (column = 0; column < 13; column++)
				deck[row][column] = 0;
	}

	//find a random open slot for 52 cards,  super inefficient
	for (card = 1; card <= 52; card++){
		//find random open slot in deck
		do{	
			row = rand() % 4;
			column = rand() % 13;
		} while (deck[row][column] != 0);

		//place card in open slot
		deck[row][column] = card;
	}
} 

//deal a card from the deck and remove that card from the deck
//this code was also provided for us, though we were allowed to modify it.
Card deal_card(int deck[4][13]){
	int row = 0;    //row represents suite
	int column = 0; //column represents face
	int deck_position = 0;   //position in deck e.g. top == 1 bottom == 52
	bool finding_top_of_deck = true;
	Card this_card;
	//
	while(finding_top_of_deck){
		deck_position++;

		//loop through rows
		for (row = 0; row < 4; row++){
			//loop through columns
			for (column = 0; column < 13; column++){
				if (deck[row][column] == deck_position){
					finding_top_of_deck = false;
					deck[row][column] = 0;
					this_card.suite = row;
					this_card.face = column;
					this_card.ofakind = 1;
					this_card.valuable = false;
				}
			}
		}
	}
	return this_card;
}

//deals a hand of 5 using Card hand[5] array as output parameter
//employs the deal_card function five times
void deal_hand(int deck[4][13], Card hand[5]){
	for (int idx = 0; idx < 5; idx++)
	{
		hand[idx] = deal_card(deck);
	}
	sort_hand(hand);
}

//Displays a hand of five
void show_hand(Card hand[5], bool Greg){
	char *suit_names[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	char *face_names[13] = { "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	printf("  --------   --------   --------   --------   -------- \n");
	for (int idx = 0; idx < 5; idx++)
		Greg ? printf(" |%-8s|", face_names[hand[idx].face]) : printf(" |        |");
	printf("\n |        | |        | |        | |        | |        |\n"
		   	" |        | |        | |        | |        | |        |\n"
			" |        | |        | |        | |        | |        |\n");
	for (int idx = 0; idx < 5; idx++)
		Greg ? printf(" |%8s|", suit_names[hand[idx].suite]) : printf(" |        |");
	printf("\n  --------   --------   --------   --------   -------- \n\n");
}

//displays opponents hand facedown and your hand face up
void show_hands(Card Debbie_hand[5], bool show_Debbie, Card Greg_hand[5], bool show_Greg){
	puts("  Debbie's Hand");
	show_hand(Debbie_hand, show_Debbie);
	puts("                                           Greg's Hand");
	show_hand(Greg_hand, show_Greg);
}

//returns a hand rank with higher values being better hands
Ranking evaluate_hand(Card hand[5]){
	Ranking hand_rank = of_a_kind(hand);
	bool flush = is_flush(hand), straight = is_straight(hand);

	for (int idx = 0; idx < 5; idx++)
		hand[idx].valuable = true;

	if (flush && straight)
		hand_rank = straight_flush;
	else if (hand_rank == four_of || hand_rank == full_house)
		hand_rank = hand_rank;
	else if (flush)
		hand_rank = a_flush;
	else if (straight)
		hand_rank = a_straight;
	else if (hand_rank != high_card)
	{
		for (int idx = 0; idx < 5; idx++) {
			if (hand[idx].ofakind == 1)
				hand[idx].valuable = false;
		}
	}
	else
		hand[0].valuable = false, hand[1].valuable = false, hand[2].valuable = false, hand[3].valuable = true, hand[4].valuable = true;

	return hand_rank;
}

//comparison function for using qsort
int compare(Card *elem1,Card *elem2){
	if (elem1->face < elem2->face)
		return -1;
	else if (elem1->face > elem2->face)
		return 1;
	else
		return 0;
}

//uses qsort to put hand into ascending order
void sort_hand(Card hand[5]){
	qsort(hand, 5, sizeof(Card), compare);
}

//determines if hand contains a flush
bool is_flush(Card hand[5]){
	bool flush = true;
	for(int idx = 0; idx < 4; idx++)
	{
		if (hand[idx].suite != hand[idx + 1].suite)
		{
			flush = false;
			break;
		}
	}
	return flush;}

//determines if a hand contains a straight
bool is_straight(Card hand[5]){
	bool straight = true;
	for (int idx = 0; idx < 4; idx++)
	{
		if (!((hand[idx].face + 1 == hand[idx + 1].face)||(hand[idx].face == Five && hand[idx + 1].face == Ace)))
		{
			straight = false;
			break;
		}
	}
	return straight;
}

//determine if a hand contains high card, pair, two pair, three of a kind, full house, or four of a kind
Ranking of_a_kind(Card hand[5]){
	Ranking this_hand;
	int ofakind = 0, pairs = 0 , threeofs = 0, fourofs = 0;
	for (int idx = 0; idx < 5; idx++)
	{
		for (int idy = 0; idy < 5; idy++)
		{
			if (hand[idy].face == hand[idx].face)
				ofakind += 1;
		}
		hand[idx].ofakind = ofakind;
		if (ofakind == 2)
			pairs += 1;
		else if (ofakind == 3)
			threeofs += 1;
		else if (ofakind == 4)
			fourofs += 1;
		ofakind = 0;
	}
	if (fourofs >= 4)
		this_hand = four_of;
	else if (threeofs >= 3 && pairs >= 2)
		this_hand = full_house;
	else if (threeofs >= 3)
		this_hand = three_of;
	else if (pairs >= 4)
		this_hand = two_pair;
	else if (pairs >= 2)
		this_hand = one_pair;
	else
		this_hand = high_card;

	return this_hand;
}

//discard and draw cards, manual for Greg , automated for Debbie. returns number of cards discarded.
int discard_and_draw(Card hand[5], int deck[4][13], bool Greg){	
	char input;
	int discards = 0, slot = 0;
	if (Greg)	{
			while ( discards < 3 && slot < 5) {
				printf("  Keep?   ");
				do {
					input = _getch();
					if (input == 'n' || input == 'N' || input == '0') {
						hand[slot] = deal_card(deck);
						discards++;
					}
				} while (!(input == 'n' || input == 'N' || input == '0' || input == 'y' || input == 'Y' || input == '1'));
				printf("%c", input);
				slot++;
			}
	}
	else{
		for (int idx = 0; idx < 5; idx++){
			if (!hand[idx].valuable) {
				hand[idx] = deal_card(deck);
				discards++;
			}
		}
	}
	sort_hand(hand);
	printf("\n");
	return discards;
}

//compare hands and see who won
int who_won(Card Greg_hand[5], Card Debbie_hand[5]){
	int winner = 0, Deb_high, Greg_high, target, idx = 4, idy = 4; //1 is Greg win, 0 is tie, -1 is Greg lose
	Ranking Greg_hand_ranking = evaluate_hand(Greg_hand);
	Ranking Debbie_hand_ranking = evaluate_hand(Debbie_hand);
	
	if (Greg_hand_ranking > Debbie_hand_ranking)
		winner = 1;
	else if (Debbie_hand_ranking > Greg_hand_ranking)
		winner = -1;
	else {
		if (Greg_hand_ranking == royal_flush || Greg_hand_ranking == straight_flush || Greg_hand_ranking == a_straight || Greg_hand_ranking == high_card || Greg_hand_ranking == a_flush) {
				for (int idx = 4; idx >= 0; idx--) {
					if (Greg_hand[idx].face > Debbie_hand[idx].face) {
						winner = 1;
						break;
					}
					else if (Greg_hand[idx].face < Debbie_hand[idx].face) {
						winner = -1;
						break;
					}
				}
			}
		else {
			if (Greg_hand_ranking == one_pair || Greg_hand_ranking == two_pair)
				target = 2;
			else  if (Greg_hand_ranking == three_of || Greg_hand_ranking == full_house)
				target = 3;
			else
				target = 4;

			while (winner == 0) {
				while (Greg_hand[idx].ofakind != target && idx != 0) 
					idx--;
				while (Debbie_hand[idy].ofakind != target && idy != 0) 
					idy--;
				if (Greg_hand[idx].face > Debbie_hand[idy].face)
					winner = 1;
				else if (Greg_hand[idx].face < Debbie_hand[idy].face)
					winner = -1;
				else if (idx == 0 || idy == 0)
					idx = 4, idy = 4, target -= 1;
				else
					break;
			}
		}
	}
	return winner;
}

//talks trash
void talk_trash(bool Debbie)
{
	int saying = rand() % 5;
	if (Debbie) {
		switch (saying)
		{
		case 0:
			puts(" I knew you a worthless nephew");
			break;
		case 1:
			puts(" Just give up go home and cry Greg");
			break;
		case 2:
			puts(" Face it Greg, you not very smart");
			break;
		case 3:
			puts(" Debbie laughs maniacally");
			break;
		case 4:
			puts(" You going to lost Greg, you suck at this game, and at life");
			break;
		default:
			break;
		}
	}
	else {
		switch (saying)
		{
		case 0:
			puts(" That's right, teach that old crone a lesson");
			break;
		case 1:
			puts(" Debbie doesn't look so confident now");
			break;
		case 2:
			puts(" You begin to feel self esteem blossom in your chest");
			break;
		case 3:
			puts(" Looks like Debbie is losing her edge");
			break;
		case 4:
			puts(" Ha! Take that Debbie!");
			break;
		default:
			break;
		}
	}
}