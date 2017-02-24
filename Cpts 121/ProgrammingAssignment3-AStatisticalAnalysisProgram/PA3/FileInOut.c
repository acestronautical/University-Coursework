/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017{return 0;} Lab Section 9                                   *
* Programming Assignment: PA3                                                              *
* Date: February 2, 2017                                                                   *
* Description: Establish Stream, Manipulate Data, Destroy Stream                           *
*******************************************************************************************/

#include "FileInOut.h"

/*FUNCT: read_double
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Reads one double from input file
PRECONS: Read stream must be established POSTCONS: Returns a double*/
double read_double(FILE *infile) {	
	double doubleFromFile = 0;
	fscanf(infile, "%lf", &doubleFromFile);
	return doubleFromFile;
}


/*FUNCT: read_integer
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Reads one integer from input file
PRECONS: The input file must be open POSTCONS: returns an integer from file*/
int read_integer(FILE *infile){
	int intFromFile = 0;
	fscanf(infile, "%d", &intFromFile);
	return intFromFile;
}


/*FUNCT: calculuate_sum
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Finds the sum of number1, number2, number3, number4, and number5
PRECONS: Main must be running POSTCONS: returns sum as double*/
double calculate_sum(double number1, double number2, double number3, double number4, double number5){
	double sum = number1 + number2 + number3 + number4 + number5;
	return sum;
}

/*FUNCT: calculuate_mean
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the mean through the calculation sum / number with error check for number == 0
PRECONS: Main must be running POSTCONS: returns mean as double*/
double calculate_mean(double sum, int number){
	double mean = 0;
	if (number == 0)
	{
		return -1;
	}
	mean = sum / number;
	return mean;
}

/*FUNCT: calculuate_deviation
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the deviation of number from the mean. The deviation may be calculated as number - mean.
PRECONS: Main must be running POSTCONS: returns deviation as double*/
double calculate_deviation(double number, double mean){
	double deviation = number - mean;
	return deviation;
}

/*FUNCT: calculuate_variance
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP:Determines variance via: ((deviation1)^2 + (deviation2)^2 + (deviation3)^2 + (deviation4)^2 + (deviation5)^2) / number
PRECONS: Main must be running POSTCONS: returns variance as double*/
double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5, int number){
	double variance = ((deviation1 * deviation1) + (deviation2 * deviation2) + (deviation3 * deviation3) + (deviation4 * deviation4) + (deviation5 * deviation5)) / number;
	return variance;
}

/*FUNCT: calculate_standard_deviation
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Calculates the standard deviation as sqrt (variance) and returns the result
PRECONS: Main must be running POSTCONS: returns variance as double*/
double calculate_standard_deviation(double variance){
	double deviation = sqrt(variance, 2);
	return deviation;
}

/*FUNCT: find_max
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the max number of five input parameters passed into the FUNCT
PRECONS: Main must be running POSTCONS: returns max as double*/
double find_max(double number1, double number2, double number3, double number4, double number5){
	double max = number1;
	if (max < number2)
	{
		max = number2;
	}
	if (max < number3)
	{
		max = number3;
	}
	if (max < number4)
	{
		max = number4;
	}
	if (max < number5)
	{
		max = number5;
	}
	return max; //I feel like there's a more elegant way of finding the max than a bunch of if statements but i'm not sure what it is
}

/*FUNCT: find_min
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the min number of five input parameters passed into the FUNCT
PRECONS: Main must be running POSTCONS: returns min as double*/
double find_min(double number1, double number2, double number3, double number4, double number5){
	double min = number1;
	if (min > number2)
	{
		min = number2;
	}
	if (min > number3)
	{
		min = number3;
	}
	if (min > number4)
	{
		min = number4;
	}
	if (min > number5)
	{
		min = number5;
	}
	return min;
}

/*FUNCT: print_double
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Prints a double precision number (to the hundredths place) to an output file
PRECONS: Main must be running POSTCONS: FUNCT is used for side effects to write to file*/
void print_double(FILE *outfile, double number){
	fprintf(outfile, "%.2lf\n", number);
}
