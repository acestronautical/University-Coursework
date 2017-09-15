/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 122, Fall  2017; Lab Section 2                                               *
* Programming Assignment: PA1 - Fitbit Data                                                *
* Date: 8-26-17                                                                            *
* Description: A program which reads in fitbit data and runs some analyses                 *
*******************************************************************************************/

#include "header.h"

int main(void) {

	//declare stuff
	fitbitdata parsedlines[1440] = { 0 };
	int parsedlinessize = sizeof(parsedlines) / sizeof(parsedlines[0]);
	char oneline[100] = "";
	FILE* infile = NULL;
	FILE* outfile = NULL;
	int counter = 0;
	double caloriesum = 0, distancesum = 0;
	unsigned int floorsum = 0, stepsum = 0, stepmax = 0, hrsum = 0, hrdatapoints = 0, sleeprangesum = 0;
	unsigned int sleeprangemax = 0, indexsleepstart = 0, indexsleepend = 0, indexsleepstartmax = 0, indexsleependmax = 0;
	bool inrange = false;
	double hraverage = 0;
	char* token = NULL;

	//create read write streams
	infile = fopen("FitbitData.csv", "r");
	outfile = fopen("Results.csv", "w");

	if (infile == NULL || outfile == NULL)
		exit(1);

	//throw away first line
	fgets(oneline, 100, infile);

	//start read from file loop into fitbitdata structs
	do {
		fgets(oneline, 100, infile); //grab a single line
		preprocessline(oneline, ',', '0'); //fix double delimiters
		//debug line
		//printf("%s", oneline); 
		token = strtok(oneline, ",");
		if (token != NULL) //make sure token not null, it never should be since we fixed double delims but just in case
			strcpy(parsedlines[counter].minute, token);
		token = strtok(NULL, ",");
		if (token != NULL)
		parsedlines[counter].calories = atof(token);
		token = strtok(NULL, ",");
		if (token != NULL)
			parsedlines[counter].distance = atof(token);
		token = strtok(NULL, ",");
		if (token != NULL)
			parsedlines[counter].floors = atoi(token);
		token = strtok(NULL, ",");
		if (token != NULL)
			parsedlines[counter].heartRate = atoi(token);
		token = strtok(NULL, ",");
		if (token != NULL)
			parsedlines[counter].steps = atoi(token);
		token = strtok(NULL, ",");
		if (token != NULL)
			parsedlines[counter].sleepLevel = atoi(token);
		//debug line
		//printf("%s %lf %lf %d %d %d %d\n", parsedlines[counter].minute, parsedlines[counter].calories, parsedlines[counter].distance, parsedlines[counter].floors, parsedlines[counter].heartRate, parsedlines[counter].steps, parsedlines[counter].sleepLevel);
		counter++;
	} while (counter < parsedlinessize);

	//analyze data by iterating through parsedlines array
	for (int i = 0; i < parsedlinessize; i++) {
		
		//sums up values
		caloriesum += parsedlines[i].calories;
		distancesum += parsedlines[i].distance;
		floorsum += parsedlines[i].floors;
		stepsum += parsedlines[i].steps;
		hrsum += parsedlines[i].heartRate;

		//find max steps
		if (parsedlines[i].steps >= stepmax)
			stepmax = parsedlines[i].steps;

		//counts how many valid heartrate datapoints we have
		if (parsedlines[i].heartRate > 25) //record for lowest resting hr is 26bpm
			hrdatapoints += 1;

		//checks if within sleep range and checks if current range is poorest range
		if ((parsedlines[i].sleepLevel > 1) && (inrange == false)) {
			inrange = true;
			indexsleepstart = i;
		}
		if (parsedlines[i].sleepLevel > 1) {
			sleeprangesum += parsedlines[i].sleepLevel;
			if (sleeprangesum > sleeprangemax) {
				sleeprangemax = sleeprangesum;
				indexsleepstartmax = indexsleepstart;
			}
		}
		else if ((parsedlines[i].sleepLevel < 2) && (inrange == true)) {
			inrange = false;
			indexsleepend = (i - 1);
			if (indexsleepend > sleeprangemax) {
				indexsleependmax = indexsleepend;
			}
			sleeprangesum = 0;
		}
		//debug line
		//printf("caloriesum = %lf distance = %lf floorsum = %d stepsum = %d hrsum = %d sleeprangesum = %d\n", caloriesum, distancesum, floorsum, stepsum, hrsum, sleeprangesum);

	}

	//calculates average heartrate for the period
	hraverage = hrsum / (double)hrdatapoints;

	//debug line
	//printf("hraverage = %lf\n", hraverage);


	//outputs to console and to file
	fprintf(outfile, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	fprintf(stdout, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	fprintf(outfile, "%lf,%lf,%d,%d,%lf,%d,%s  %s", caloriesum, distancesum, floorsum, stepsum, hraverage, stepmax, parsedlines[indexsleepstartmax].minute,parsedlines[indexsleependmax].minute);
	fprintf(stdout, "%-14lf,%-14lf,%-12d,%-11d,%-13lf,%-9d,%-s  %-s\n", caloriesum, distancesum, floorsum, stepsum, hraverage, stepmax, parsedlines[indexsleepstartmax].minute, parsedlines[indexsleependmax].minute);


	//destroy read write streams
	_fcloseall();

	//pauses at end of program
	system("pause");
	return 0;
}