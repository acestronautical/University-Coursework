/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA7 - Poker                                                      *
* Date: 4-12-17                                                                            *
* Description: A game where you play poker with your aunt, no betting occurs               *
*******************************************************************************************/
#include "Header.h"

int main(){
	//create deck array
	int deck[4][13] = { 0 };

	//create hand arrays
	Card Greg_hand[5] = { { 1, 0, 1 } ,{ 1, 0, 1 } ,{ 3, 0, 1 } ,{ 3, 0, 1 } ,{ 3, 0, 1 } };
	Card Debbie_hand[5] = { { 0, 0, 1 } ,{ 9, 0, 1 } ,{ 10, 3, 1 } ,{ 11, 0, 1 } ,{ 12, 1, 1 } };

	//hand rankings
	Ranking Greg_hand_ranking;
	Ranking Debbie_hand_ranking;

	//rounds won
	int Greg_rounds = 0;
	int Debbie_rounds = 0;

	//cards discarded this round
	int Greg_discards = 0;
	int Debbie_discards = 0;

	//hand ranking names
	char* ranking_names[10] = { "high card", "one pair", "two pair", "three of a kind", "a straight", "a flush", "a full house", "four of a kind", "a straight flush", "a royal flush" };

	//seed random-number generator
	srand((unsigned)time(NULL)); 

	puts(" Wake up Greg....\n\n");
	refresh_screen();
	puts(" You don't want to be late");
	refresh_screen();
	puts(" Today is the day you go to visit your aunt Debbie");
	puts("");
	puts(" She is your least favorite aunt, and a mean poker player");
	puts(" but today....");
	refresh_screen();
	puts(" YOU WILL BEAT HER AT OWN GAME");
	refresh_screen();
	puts(" You make it to the old folks home in time activity hour");
	puts(" from across the room your lock eyes, with Debbie");
	puts(" she already has the poker cards ready");
	refresh_screen();
	puts(" as you sit down to play, she cackles with laughter");
	puts(" \"Come to play me again sissy boy? Enjoy losing\"");
	refresh_screen();
	puts(" You cannot let her win");
	refresh_screen();
	puts(" BEGIN");
	refresh_screen();

	for(int idx = 0; idx <10; idx++) {
		printf("\n ---------------\n      ROUND %d\n ---------------\n\n      START\n", idx + 1);
		refresh_screen();
		//initialize deck to random order
		init_deck_random(deck);

		deal_hand(deck, Debbie_hand);

		deal_hand(deck, Greg_hand);

		show_hands(Debbie_hand, false, Greg_hand, true);
		Greg_hand_ranking = evaluate_hand(Greg_hand);
		Debbie_hand_ranking = evaluate_hand(Debbie_hand);
		printf(" You have %s\n", ranking_names[Greg_hand_ranking]);
		refresh_screen();
		show_hands(Debbie_hand, false, Greg_hand, true);
		printf(" Select which cards to keep using (y)es or (n)o\n You may only discard a maximum of three cards\n");
		refresh_screen();

		show_hands(Debbie_hand, false, Greg_hand, true);
		Greg_discards = discard_and_draw(Greg_hand, deck, true);
		Debbie_discards = discard_and_draw(Debbie_hand, deck, false);
		refresh_screen();

		printf("\n ---------------\n Greg discards %d\n Debb discards %d\n ---------------\n", Greg_discards, Debbie_discards);
		refresh_screen();

		show_hands(Debbie_hand, true, Greg_hand, true);
		Greg_hand_ranking = evaluate_hand(Greg_hand);
		Debbie_hand_ranking = evaluate_hand(Debbie_hand);
		printf(" You have %s\n", ranking_names[Greg_hand_ranking]);
		printf(" Debbie has %s\n", ranking_names[Debbie_hand_ranking]);

		if (who_won(Greg_hand, Debbie_hand) == 1)
		{
			printf("\n Greg wins this round\n");
			talk_trash(false);
			Greg_rounds++;
		}
		else if (who_won(Greg_hand, Debbie_hand) == -1)
		{
			printf("\n Debbie wins this round\n");
			talk_trash(true);
			Debbie_rounds++;
		}
		else
			printf("\n No one wins this round\n");
		refresh_screen();
		printf("\n ---------------\n  Greg Score:%d\n  Debb Score:%d\n ---------------\n", Greg_rounds, Debbie_rounds);
		refresh_screen();
	}
	if (Greg_rounds > Debbie_rounds)
		printf("\nYou are the ultimate champion\nDebbie slumps down in her chair and cries\nShe has resigned herself to dementia and jello\n");
	else if (Debbie_rounds > Greg_rounds)
		printf("\nDebbie has won again\n\"Looks like dementia hasn't gotten me yet\"\n\"I'll be calling your mom to let her know i'm moving back in\"\n\n NOOOOOOOOOOOOO.....\n");
	else if(Debbie_rounds == Greg_rounds)
		printf("\nYou have tied\nDebbie gives you a grudging nod of respect\nAs you walk away you feel proud\n");
	refresh_screen();
	return 0;
}