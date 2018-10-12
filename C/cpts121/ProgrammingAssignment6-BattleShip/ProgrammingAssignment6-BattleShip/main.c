/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA6 - BattleShip                                                 *
* Date: 3-12-17                                                                            *
* Description: A game of battleship played in terminal with AI opponent                    *
*******************************************************************************************/

#include "header.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	FILE* bs_log = NULL;
	bs_log = fopen("battleship.log", "w");

	//human and robot boards
	char human_ship_grid[ROWS][COLUMNS] = { 0 };
	char robot_ship_grid[ROWS][COLUMNS] = { 0 };

	//used for stats, win condition, and check if ship is sunk
	Stats human_stats = { .player_name = "Human", .hits = 0,.misses = 0,.won = FALSE ,.enemy_carrier_hp = 5,.enemy_battleship_hp = 4,.enemy_cruiser_hp = 3,.enemy_submarine_hp = 3,.enemy_destroyer_hp = 2 };
	Stats robot_stats = { .player_name = "Robot", .hits = 0,.misses = 0,.won = FALSE ,.enemy_carrier_hp = 5,.enemy_battleship_hp = 4,.enemy_cruiser_hp = 3,.enemy_submarine_hp = 3,.enemy_destroyer_hp = 2 };

	//used for ship placement
	Ship carrier = { .name = "carrier",.size = 5,.symbol = 'c' };
	Ship battleship = { .name = "battleship",.size = 4,.symbol = 'b' };
	Ship cruiser = { .name = "cruiser",.size = 3,.symbol = 'r' };
	Ship submarine = { .name = "submarine",.size = 3,.symbol = 's' };
	Ship destroyer = { .name = "destroyer",.size = 2,.symbol = 'd' };

	//passed into ship placement function
	Ship armada[5] = { carrier , battleship , cruiser , submarine , destroyer };
	
	bool human_turn = TRUE;
	Shot current_shot;
	char rand_or_man = 'z';

	initialize_2d_array(human_ship_grid, ROWS, COLUMNS, WATER);
	initialize_2d_array(robot_ship_grid, ROWS, COLUMNS, WATER);

	GREEN_TEXT;

	welcome_screen();
	
	human_turn = coin_flip();

	system("pause");
	system("cls");
	
	while (rand_or_man != 'r' && rand_or_man != 'R' && rand_or_man != 'm' && rand_or_man != 'M')
	{
		puts("Would you like to place your ships (R)andomly or (M)anually?");
		rand_or_man = _getch();
		if (rand_or_man == 'm' || rand_or_man == 'M')
			place_ships(human_ship_grid, armada, MANUAL);
		else  if (rand_or_man == 'r' || rand_or_man == 'R')
			place_ships(human_ship_grid, armada, RANDOM);
	}
	system("cls");

	place_ships(robot_ship_grid, armada, RANDOM);

	while (robot_stats.won != TRUE && human_stats.won != TRUE) //main game loop
	{
		if (human_turn) { //human turn
			puts("     Robot Board");
			print_game_board(robot_ship_grid, FALSE);

			puts("     Human Board");
			print_game_board(human_ship_grid, TRUE);

			current_shot = shoot_at(robot_ship_grid, HUMAN);
			human_stats = update_stats(current_shot, human_stats);
			log_shot(current_shot, human_stats, bs_log);
			printf("%s\n", sunk_something_string(current_shot, human_stats));

			system("pause");
			system("cls");
		}
		else //robot turn
		{
			current_shot = shoot_at(human_ship_grid, ROBOT); //robot has 1 in 7 chance of getting a 'kill shot' instead of random shot
			robot_stats = update_stats(current_shot, robot_stats);
			log_shot(current_shot, robot_stats, bs_log);

			printf("%s\n", sunk_something_string(current_shot, robot_stats));

			system("pause");
			system("cls");
		}
		human_turn = !human_turn; //switch whose turn it is
	}
	

	if (human_stats.won == TRUE)
		puts("\nHuman wins!\nSkynet has been defeated");
	else
		puts("\nRobot wins!\nThis does not bode well for the human race");

	puts("Let's look the stats");
	system("pause");
	system("cls");

	stats_to_screen(human_stats);
	if (human_stats.won)
		puts("Human Won! Yeah go Humans! Humans are the best!");
	else
		puts("Human Lost. This is a dark day for mankind.");
	system("pause");
	system("cls");

	stats_to_screen(robot_stats);
	if (robot_stats.won) 
		puts("Robot Won! Organic life is inferior");
	else 
		puts("Robot Lost. He goes home to his roomba wife and drinks.");
	system("pause");
	system("cls");

	stats_to_file(bs_log, human_stats);
	stats_to_file(bs_log, robot_stats);
	puts("Stats written to log file");

	return 0;
}
