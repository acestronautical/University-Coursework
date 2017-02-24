#include "equations.h"
//Such functions much wow


//makes a prompt asking for a number 1 through 9 and then returns that value as a char
char prompt_user_choice() {

	char userChoice;

	//This Section prints out a prompt for the user
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

	//This section gets the users choice
	scanf(" %c", &userChoice);

	return userChoice; //Then we return the user choice, which is a char
}

//multiplies mass by acceleration then returns the result force as a double
double calculate_newtons_2nd_law(double mass, double acceleration) {
	double force = mass * acceleration;
	return force;
}

//Performs the calculations to find the volume of a cylinder then returns that volume as a double
double calculate_volume_cylinder(double radius, double height) {
	double volume = radius * radius * height * PI;
	return volume;
}

//Takes in a char, subtracts 'a' then adds 'A' and returns the encoded character as a char
char perform_character_encoding(char plaintext_character) {
	char encoded_character = (plaintext_character - 'a') + 'A';
	return encoded_character;
}

//performs the gauus lens equation and returns the value of f as a double
double calculate_gauss_lens(double u, double v) {
	double f = (1 / ((1 / u) + (1 / v)));
	return f;
}

//calcululates Tan for a given theta in radians then returns that result as a double
double calculate_tangent(double theta) {
	double tan = (sin(theta) / cos(theta));
	return tan;
}

//This really should be called a voltage divider
//Calculates the voltage across a given resistor for two resistors in series
//returns vout as a double
double calculate_resistive_divider(double r1, double r2, double vin) {
	double vout = ((r1 / (r1 + r2)) * vin);
	return vout;
}

//calculates the distance between two points and returns that value as a double
//This is the only place where a function from math.h is called
double calculate_distance_between_2pts(double x1, double y1, double x2, double y2) {
	double distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return distance;
}

//performs some  arbitrary calculation and returns the result as a double
//because the modulo operator is used the value for double a is type cast as an int
//even values, or values which truncate to even should not be passed in for argument double a
double calculate_general_equation(double a, double x, double z) {
	double y = ((int)a / ((int)a % 2) - (63 / (double)-17) + x * z);
	return y;
}