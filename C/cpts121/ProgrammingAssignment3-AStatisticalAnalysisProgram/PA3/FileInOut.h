#ifndef _HEADER_H
#define _HEADER_H

//Include standard i/o and math libraries
#include<stdio.h>
#include<math.h> //gotta have my sqrt

//disable those pesky warnings
#define _CRT_SECURE_NO_WARNING


//FUNCTION PROTOTYPES/DECLARATIONS
                                    
double read_double(FILE *infile);
/*FUNCT: read_double
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Reads one double from input file
PRECONS: The input file must be open POSTCONS:*/


int read_integer(FILE *infile);
/*FUNCT: read_integer
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Reads one integer from input file
PRECONS: The input file must be open POSTCONS: returns an integer from file*/


double calculate_sum(double number1, double number2, double number3, double number4, double number5);
/*FUNCT: calculuate_sum
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Finds the sum of number1, number2, number3, number4, and number5
PRECONS: Called from Main POSTCONS: returns sum as double*/

double calculate_mean(double sum, int number);
/*FUNCT: calculuate_mean
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the mean through the calculation sum / number with error check for number == 0
PRECONS: Called from Main POSTCONS: returns mean as double*/

double calculate_deviation(double number, double mean);
/*FUNCT: calculuate_deviation
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP:Determines the deviation of number from the mean. The deviation may be calculated as number - mean.
PRECONS: Called from Main POSTCONS: returns deviation as double*/

double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5, int number);
/*FUNCT: calculuate_variance
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP:Determines variance via: ((deviation1)^2 + (deviation2)^2 + (deviation3)^2 + (deviation4)^2 + (deviation5)^2) / number
PRECONS: Called from Main POSTCONS: returns variance as double*/

double calculate_standard_deviation(double variance);
/*FUNCT: calculate_standard_deviation
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Calculates the standard deviation as sqrt (variance) and returns the result
PRECONS: Called from Main POSTCONS: returns variance as double*/

double find_max(double number1, double number2, double number3, double number4, double number5);
/*FUNCT: find_max
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the max number of five input parameters passed into the FUNCT
PRECONS: Called from Main POSTCONS: returns max as double*/

double find_min(double number1, double number2, double number3, double number4, double number5);
/*FUNCT: find_min
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Determines the min number of five input parameters passed into the FUNCT
PRECONS: Called from Main POSTCONS: returns min as double*/

void print_double(FILE *outfile, double number);
/*FUNCT: print_double
CREATED: February 2, 2017 MODIFIED: February 2, 2017
DESCRIP: Prints a double precision number (to the hundredths place) to an output file
PRECONS: Called from Main POSTCONS: FUNCT is used for side effects*/

#endif // !_HEADER_H