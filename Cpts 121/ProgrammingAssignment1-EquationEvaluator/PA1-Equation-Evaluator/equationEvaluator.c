/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA1                                                              *
* Date: January 18, 2017                                                                   *
* Description: Evaluates various math and physics equations                                *
*******************************************************************************************/
#include<stdio.h>
#include<math.h>
#define pi 3.14159265358979323846

main() {
	/*Variable declarations*/
	char userChoiceFirstChar = '\0'; // used to store user prompt choice
	double userDouble1 = 0;
	double userDouble2 = 0;
	double userDouble3 = 0;
	double userDouble4 = 0;
	char userChar1 = '\0';


	do //This is a do while loop that will exit when 9 is entered. I Chose do while to ensure that the loop would run at least once.
	{
		/*This Section prints out a prompt for the user*/
		printf_s("\n");
		printf_s("1.Newtons Second Law of Motion : force = mass * acceleration\n");
		printf_s("2.Volume of a cylinder : volume_cylinder = PI * radius * height\n");
		printf_s("3.Character encoding : encoded_character = (plaintext_character - 'a') + 'A'\n");
		printf_s("4.Gauss Lens Formula(solve for focal length) : 1 / focal length = 1 / object distance + 1 / image distance\n");
		printf_s("5.Tangent : tan_theta = sin(theta) / cos(theta)\n");
		printf_s("6.Resistive divider : vout = r2 / (r1 + r2) * vin\n");
		printf_s("7.Distance between two points : distance = square root of((x1 - x2)2 + (y1 - y2)2)\n");
		printf_s("8.General equation : y = a / (a %% 2) - (63 / -17) + x * z\n");
		printf_s("\n");
		printf_s("9.Exit\n");
		printf_s("\n");
		printf_s("Please enter the number of equation you would like to evaluate\n\n");

		/*get user choice*/
		scanf_s(" %c", &userChoiceFirstChar);

		/*control flow based on user choice*/
		switch (userChoiceFirstChar) //I thought switch case the most appropriate
		{
		case '1':
			printf_s("\nNewtons Second Law of Motion : force = mass * acceleration\n");
			printf_s("\nPlease enter the mass:"); //prompt
			scanf_s("%lf", &userDouble1); //input
			printf_s("Please enter the acceleration:"); //prompt
			scanf_s("%lf", &userDouble2); //input
			printf_s("\nforce is equal to %lf", (userDouble1 * userDouble2)); //output
			break;
		case '2':
			printf_s("\nVolume of a cylinder : volume = PI * radius *radius * height\n");
			printf_s("\nPlease enter the radius:");
			scanf_s("%lf", &userDouble1);
			printf_s("Please enter the height:");
			scanf_s("%lf", &userDouble2);
			printf_s("\nVolume is equal to %lf", (pi * userDouble1 * userDouble1 * userDouble2));
			break;
		case '3':
			printf_s("\nCharacter encoding : encoded character = (plaintext character - 'a') + 'A'\n");
			printf_s("\nPlease enter the plaintext character:");
			scanf_s(" %c", &userChar1);
			printf_s("\nEncoded character is equal to %c", (userChar1 - 'a') +'A' ); 
			break;
		case '4':
			printf_s("Gauss Lens Formula(solve for f) : 1 / focal length = (1 / object distance) + (1 / image distance)\n");
			printf_s("\nPlease enter value for object distance:");
			scanf_s("%lf", &userDouble1);
			printf_s("Please enter image distance:");
			scanf_s("%lf", &userDouble2);
			printf_s("\nFocal Length is equal to %lf", (1 / ((1 / userDouble1) + (1 / userDouble2))));
			break;
		case '5':
			printf_s("Tangent : tan(theta) = sin(theta) / cos(theta)\n");
			printf_s("\nPlease enter a value for theta:");
			scanf_s("%lf", &userDouble1);
			printf_s("\nTan(theta) is equal to %lf", (sin(userDouble1) / cos(userDouble1)));
			break;
		case '6':
			printf_s("Voltage divider : Vout = r2 / (r1 + r2) * Vin\n");
			printf_s("\nPlease enter r1:");
			scanf_s("%lf", &userDouble1);
			printf_s("Please enter r2:");
			scanf_s("%lf", &userDouble2);
			printf_s("Please enter Vin:");
			scanf_s("%lf", &userDouble3);
			printf_s("\nVout is equal to %lf", ((userDouble2 / (userDouble1 + userDouble2)) * userDouble3));
			break;
		case '7':
			printf_s("Distance between two points : distance = square root of((x1 - x2)^2 + (y1 - y2)^2)\n");
			printf_s("\nPlease enter x1:");
			scanf_s("%lf", &userDouble1);
			printf_s("Please enter x2:");
			scanf_s("%lf", &userDouble2);
			printf_s("Please enter y1:");
			scanf_s("%lf", &userDouble3);
			printf_s("Please enter y2:");
			scanf_s("%lf", &userDouble4);
			printf_s("\nDistance is equal to %lf", (double)sqrtf(powf((userDouble1 - userDouble2), 2) + powf((userDouble3 - userDouble4), 2)));
			break;
		case '8':
			printf_s("General equation : y = a / (a %% 2) - (63 / -17) + x * z\n");//to escape '%' i used '%%'
			printf_s("\nPlease enter integar value for a:"); //prompt for integar but will accept float
			scanf_s("%lf", &userDouble1);
			while ((int)userDouble1 % 2 == 0)//loop triggers if the entered number will cause a divide by zero
			{
				printf_s("This value for a will create a  divide by zero error \nPlease select a different value");
				printf_s("\nPlease enter an integer value for a:"); //reprompt
				scanf_s("%lf", &userDouble1);//get new value
			}
			printf_s("Please enter x:");
			scanf_s("%d", &userDouble2);
			printf_s("Please enter z:");
			scanf_s("%d", &userDouble3);
			printf_s("\ny is equal to %lf", (((int)userDouble1 / ((int)userDouble1 % 2)) - (63/(double)-17) + userDouble2 * userDouble3)); //int type casting strips values after decimal from userDouble1 
			break;
		case '9':
			printf_s("\n");
			break;
		default:
			printf_s("\nThat is an invalid choice");
			break;
		}
		getchar();
		getchar();
	} while (userChoiceFirstChar != '9'); //if user selected 9, break loop and go to return

	return 0;
}

