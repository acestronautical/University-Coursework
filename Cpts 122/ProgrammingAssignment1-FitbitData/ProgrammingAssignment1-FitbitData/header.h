/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 122, Fall  2017; Lab Section 2                                               *
* Programming Assignment: PA1 - Fitbit Data                                                *
* Date: 8-26-17                                                                            *
* Description: A program which reads in fitbit data and runs some analyses                 *
*******************************************************************************************/
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void preprocessline(char line[], char delim, char value);

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} sleep;

typedef struct fitbit
{
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	sleep sleepLevel;
} fitbitdata;