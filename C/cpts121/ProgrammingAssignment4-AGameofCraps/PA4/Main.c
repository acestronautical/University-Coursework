/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA4                                                              *
* Date: February 13, 2017                                                                  *
* Description: A game of craps,  playable in a win32 console                               *
*******************************************************************************************/

#include"Craps.h"

int main() {
	//set global randomness seed variable to time
	srand((unsigned)time(NULL)); 

	//declare variables
	double initial_bank_balance = 0, current_bank_balance = 0, wager_amount = 0, wager_additional = 0;
	int sum_dice = 0, point_value = 0, number_rolls = 0, win_loss_neither = 3;
	char walk_away = 'n', bet_more = 'n';

	//print the rules
	print_game_rules();

	//get bank balance
	initial_bank_balance = get_bank_balance();
	current_bank_balance = initial_bank_balance;

	system("cls");

	//Main game loop
	do
	{
		//eat leftover input buffer from previous loop. This allows user to enter 'no' instead of just 'n' to not walk away.
		eat_input_buffer();

		//ascii  art
		print_dice_art();

		//get wager amount
		printf("\nBets on the table!\n"
			"(how much would you like to wager?)\n\n$");
		wager_amount = get_wager_amount();

		//check wager vs balance
		until(check_wager_amount(wager_amount, current_bank_balance))
		{
			printf("Who you trying to fool punk\n"
				"You don't have that much money\n");
			wager_amount = get_wager_amount();
		}

		//say something funny about wager amount
		wager_banter(wager_amount);
		enter_to_continue();


		//first dice roll
		sum_dice = calculate_sum_dice(roll_die(), roll_die());
		point_value = sum_dice;
		enter_to_continue();
		printf("you roll %d\n\n", sum_dice);
		number_rolls = ++number_rolls;
		win_loss_neither = is_win_loss_or_point(sum_dice);


		//main game logic
			until(win_loss_neither == 1 || win_loss_neither == 0)
			{
				//prompt  for wage increase if possible
				if (wager_amount != current_bank_balance) {
					printf("increase bet?");
					scanf(" %c", &bet_more);
					eat_input_buffer(); //in case user enters 'yes' instead of just 'y' this will consume the extra input
					if (bet_more == 'Y' || bet_more == 'y')
					{
						printf("how much?");
						wager_additional = get_wager_amount();
						until(check_wager_amount((wager_amount + wager_additional), current_bank_balance))
						{
							printf("You don't have that much money\n"
								"how much?");
							wager_additional = get_wager_amount();
						}
						wager_amount = wager_amount + wager_additional;
					}
				}
				else
				{
					printf("all in!\n");
				}

				//roll to match try and match point
				sum_dice = calculate_sum_dice(roll_die(), roll_die());
				number_rolls = ++number_rolls;
				printf("shake shake shake...\n"
					"you roll %d\n\n", sum_dice);
				win_loss_neither = is_point_loss_or_neither(sum_dice, point_value);
				point_value = sum_dice;

			}
				
		//adjust balance based on win or lose and chatter
		current_bank_balance = adjust_bank_balance(current_bank_balance, wager_amount, win_loss_neither);
		chatter_messages(number_rolls, win_loss_neither, initial_bank_balance, current_bank_balance);
		printf("\nYou now have %.2lf dollers!\n", current_bank_balance);
		
		//determine if you're done playing
		if (current_bank_balance > 0)
		{
			printf("Are you ready to walk away?\n");
			scanf(" %c", &walk_away);
			system("cls");
		}

	} until(walk_away == 'y' || walk_away == 'Y' || walk_away == '1' || (current_bank_balance < 1));

	//say goodbye 
	print_goodbye();
	printf("\nCome back anytime sucker, I mean friend!\n");

	return 0;
}