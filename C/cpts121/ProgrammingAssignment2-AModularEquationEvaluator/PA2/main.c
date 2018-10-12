/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA2                                                              *
* Date: January 27, 2017                                                                   *
* Description: Modular extension of PA1 using functions                                    *
*******************************************************************************************/
#include "equations.h"

main() {
	/*Variable declarations*/
	char userChoice = '\0'; // used to store user prompt choice
	double userDouble1 = 0; //reusable double for use as equation variable
	double userDouble2 = 0; //reusable double for use as equation variable
	double userDouble3 = 0; //reusable double for use as equation variable
	double userDouble4 = 0; //reusable double for use as equation variable
	char userChar1 = '\0'; // used for character encoding


	do  //This is a do while loop that will exit when 9 is entered
		//do while ensures that the loop will run at least once
	{

		userChoice = prompt_user_choice(); //call function to prompt user to select which function they would like to evaluate

		/*switch case control flow based on user choice*/
		switch (userChoice)
		{
		case '1':
			printf_s("\nNewtons Second Law of Motion : force = mass * acceleration\n");
			printf_s("\nPlease enter the mass:"); //prompt
			scanf("%lf", &userDouble1); //input
			printf_s("Please enter the acceleration:"); //prompt
			scanf("%lf", &userDouble2); //input
			printf_s("\nforce is equal to %.2lf", calculate_newtons_2nd_law(userDouble1, userDouble2)); //output value for force
			break;
		case '2':
			printf_s("\nVolume of a cylinder : volume = PI * radius * height\n");
			printf_s("\nPlease enter the radius:");  //prompt
			scanf("%lf", &userDouble1); //input
			printf_s("Please enter the height:"); //prompt
			scanf("%lf", &userDouble2); //input
			printf_s("\nVolume is equal to %.2lf", calculate_volume_cylinder(userDouble1, userDouble2)); //output value for volume
			break;
		case '3':
			printf_s("\nCharacter encoding : encoded character = (plaintext character - 'a') + 'A'\n");
			printf_s("\nPlease enter the plaintext character:"); //prompt for character
			scanf(" %c", &userChar1); //input
			printf_s("\nEncoded character is equal to %.2c", perform_character_encoding(userChar1)); //output encoded character
			break;
		case '4':
			printf_s("Gauss Lens Formula(solve for f) : 1 / focal length = (1 / object distance) + (1 / image distance)\n");
			printf_s("\nPlease enter value for object distance:"); //prompt
			scanf("%lf", &userDouble1); //input
			printf_s("Please enter image distance:"); //prompt
			scanf("%lf", &userDouble2); //input
			printf_s("\nFocal Length is equal to %.2lf", calculate_gauss_lens(userDouble1, userDouble2)); //output value for focal length
			break;
		case '5':
			printf_s("Tangent : tan(theta) = sin(theta) / cos(theta)\n");
			printf_s("\nPlease enter a value for theta:"); //prompt
			scanf("%lf", &userDouble1); //input
			printf_s("\nTan(theta) is equal to %.2lf", calculate_tangent(userDouble1)); //ouptut value for Tan(theta)
			break;
		case '6':
			printf_s("Voltage divider : Vout = r2 / (r1 + r2) * Vin\n");
			printf_s("\nPlease enter r1:"); //prompt
			scanf("%lf", &userDouble1); //input
			printf_s("Please enter r2:"); //prompt
			scanf("%lf", &userDouble2); //input
			printf_s("Please enter Vin:"); //prompt
			scanf("%lf", &userDouble3); //input
			printf_s("\nVout is equal to %.2lf", calculate_resistive_divider(userDouble1, userDouble2, userDouble3)); //output value Vout
			break;
		case '7':
			printf_s("Distance between two points : distance = square root of((x1 - x2)^2 + (y1 - y2)^2)\n");
			printf_s("\nPlease enter x1:"); //prompt
			scanf("%lf", &userDouble1);//input
			printf_s("Please enter y1:"); //prompt
			scanf("%lf", &userDouble2);//input
			printf_s("Please enter x2:"); //prompt
			scanf("%lf", &userDouble3); //input
			printf_s("Please enter y2:"); //prompt
			scanf("%lf", &userDouble4); //input
			printf_s("\nDistance is equal to %.2lf", calculate_distance_between_2pts(userDouble1, userDouble2, userDouble3, userDouble4)); //output value for distance
			break;
		case '8':
			printf_s("General equation : y = a / (a %% 2) - (63 / -17) + x * z\n");//to escape '%' I used '%%'
			printf_s("\nPlease enter integer value for a:"); //prompt for integer but will accept float
			scanf("%lf", &userDouble1);
			while ((int)userDouble1 % 2 == 0) //loop triggers if the entered number will cause a divide by zero
			{
				printf_s("This value for a will create a  divide by zero error \nPlease select a different value");
				printf_s("\nPlease enter an integer value for a:"); //reprompt
				scanf("%lf", &userDouble1);//get new value
			}
			printf_s("Please enter x:"); //prompt
			scanf("%lf", &userDouble2); //input
			printf_s("Please enter z:"); //prompt
			scanf("%lf", &userDouble3); //input
			printf_s("\ny is equal to %.2lf", calculate_general_equation(userDouble1, userDouble2, userDouble3)); //output value for y
			break;
		case '9':
			break;
		default:
			printf_s("\nThat is an invalid choice"); // invoked if user enters something other than 1 through 9
			break;
		}
		getchar(); //adds an extra keypress before looping back to main prompt
		getchar();
		system("cls");
	} while (userChoice != '9'); //if user selected 9, break loop and go to return
	printf("\nGoodbye\n\n"); //says goodbye
	return 0;
}
