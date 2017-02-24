/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA3                                                              *
* Date: February 2, 2017                                                                   *
* Description: Establish Streams, Manipulate Data, Print Results to File, Destroy Streams  *
*******************************************************************************************/

#include "FileInOut.h"

int main(void) {
	double gpa1, gpa2, gpa3, gpa4, gpa5, gpaMean, gpaStanDv, gpaMin, gpaMax, cStandMean, ageMean; //look at all these variables
	int cStand1, cStand2, cStand3, cStand4, cStand5; //variables for days
	double age1, age2, age3, age4, age5; //there are 5 gpas, 5 class standings, 5 ages, and some doubles for calculation results 

	//ESTABLISH READ STREAM TO input.dat
	FILE *input = NULL;
	input = fopen("input.dat","r");
	if (!input) //sanity check that input.dat exists
	{
		printf("read file not found\n");
		return 1; //return 1 to indicate error if it doesn't exist
	}

	//ESTABLISH WRITE STREAM TO output.dat
	FILE *output = NULL;
	output =fopen("output.dat", "w");

	//READ DATA INTO VARIABLES
	//Student record 1
	read_integer(input); gpa1 = read_double(input); cStand1 = read_integer(input); age1 = read_double(input);
	//Student record 2
	read_integer(input); gpa2 = read_double(input); cStand2 = read_integer(input); age2 = read_double(input);
	//Student record 3
	read_integer(input); gpa3 = read_double(input); cStand3 = read_integer(input); age3 = read_double(input);
	//Student record 4
	read_integer(input); gpa4 = read_double(input); cStand4 = read_integer(input); age4 = read_double(input);
	//Student record 5
	read_integer(input); gpa5 = read_double(input); cStand5 = read_integer(input); age5 = read_double(input);
	//Student ID data is read and discarded
	//Using an array here probably would have worked better

	//DO CALCULATIONS
	gpaMean = calculate_mean(calculate_sum(gpa1, gpa2, gpa3, gpa4, gpa5), 5); //add the 5 gpas and then divide by 5

	cStandMean = calculate_mean(calculate_sum((double)cStand1, (double)cStand2, (double)cStand3, (double)cStand4, (double)cStand5), 5);

	ageMean = calculate_mean(calculate_sum((double)age1, (double)age2, (double)age3, (double)age4, (double)age5), 5);

	gpaStanDv = calculate_standard_deviation(calculate_variance( //functions, within functions, within functions!
		calculate_deviation(gpa1, gpaMean),
		calculate_deviation(gpa2, gpaMean),//function inception
		calculate_deviation(gpa3, gpaMean),
		calculate_deviation(gpa4, gpaMean),//funcception?
		calculate_deviation(gpa5, gpaMean),
		5)
	); //this calculation is split across multiple lines for readability

	gpaMin = find_min(gpa1, gpa2, gpa3, gpa4, gpa5);

	gpaMax = find_max(gpa1, gpa2, gpa3, gpa4, gpa5);

	//OUTPUT CALCULATIONS TO FILE

	print_double(output, gpaMean); //my print functions automatically append newline

	print_double(output, cStandMean);

	print_double(output, ageMean);

	fprintf(output, "\n"); //added an extra newline here to fit the example in the assignment

	print_double(output, gpaStanDv);

	print_double(output, gpaMin);

	print_double(output, gpaMax);

	//DESTROY READ STREAM
	fclose(input);

	//DESTROY WRITE STREAM
	fclose(output);

	printf("Data written successfully to output.dat\n");

	return 0;//Hey we're all done! sweet return 0 for success
}