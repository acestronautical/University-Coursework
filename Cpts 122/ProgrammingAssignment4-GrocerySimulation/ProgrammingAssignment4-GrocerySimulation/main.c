/*******************************************************************************************
* Programmer: Ace Cassidy 011481306
* Class: CptS 122, Fall  2017; Lab Section 2
* Programming Assignment: Create a grocery store line simulation
* Date: 9/28/17
* Description: Simulate two grocery store lines
*******************************************************************************************/
#include "header.h"

int main() {
	srand(time(NULL));
	int simulationEnd = 0;
	int totalMinutes = -1;
	int minutes = -1;
	int hours = 0;
	int days = 1;
	int normalArrival = (rand() % 5) + 1;
	int expressArrival = (rand() % 6) + 3;
	int normalWait = 0;
	int expressWait = 0;
	int customerNumber = 1;
	int simulationSpeed = 1000;
	Queue normalLane = { NULL, NULL };
	Queue expressLane = { NULL, NULL };
	Data newCustomer = { 0 , 0, 0 };
	puts("WELCOME TO GROCERY STORE SIMULATOR 3000!\n");
	printf(
"     _______________________________\n"
"    [=U=U=U=U=U=U=U=U=U=U=U=U=U=U=U=]\n"
"    |.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.|\n"
"    |        +-+-+-+-+-+-+-+        |\n"
"    |        |Super Grocery|        |\n"
"    |        +-+-+-+-+-+-+-+        |\n"
"    |.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.|\n"
"    |  _________  __ __  _________  |\n"
"  _ | |___   _  ||[]|[]||  _      | | _\n"
" (!)||OPEN|_(!)_|| ,| ,||_(!)_____| |(!)\n"
".T~T|:.....:T~T.:|__|__|:.T~T.:....:|T~T.\n"
"||_||||||||||_|||||||||||||_||||||||||_||\n"
"~\=/~~~~~~~~\=/~~~~~~~~~~~\=/~~~~~~~~\=/~\n\n"
		);
	puts("How fast would like the simulation to run?\n"
		"Enter the number of milliseconds it takes for a simulation minute:");
	scanf("%d", &simulationSpeed);
	puts("How long would you like to run the simulation for?\n"
		"Enter the number of simulation minutes you would like to run for:");
	scanf("%d", &simulationEnd);
	system("cls");

	//One loop is one minute "simulation time"
	while (totalMinutes <= simulationEnd) {
		Sleep(simulationSpeed);
		totalMinutes++, minutes++; normalArrival--, expressArrival--;
		if (normalWait)
			normalWait--;
		if (expressWait)
			expressWait--;
		if (minutes % 60 == 0) {
			minutes = 0;
			hours++;
		}
		if (hours % 24 == 0 && hours != 0) {
			hours = 0;
			customerNumber = 1;
			days++;
		}

		//print both lanes every ten minutes
		if (minutes % 10 == 0) {
			system("cls");
			printf("Simulation Day: %2d      Simulation Time: %02d:%02d\n", days, hours, minutes);
			printQueues(expressLane, normalLane);
		}

		//New customer arrives in normal lane every 1 - 5 minutes
		if (!normalArrival) {
			normalArrival = (rand() % 5) + 1;
			newCustomer.customerNumber = customerNumber++;
			newCustomer.serviceTime = (rand() % 5) + 1;
			normalWait += newCustomer.serviceTime;
			newCustomer.totalTime = normalWait;
			enqueue(&normalLane ,newCustomer);
			printf("Customer number %d arrived in normal lane at %02d:%02d\n", newCustomer.customerNumber, hours, minutes);
		}

		//New customer arrives in express lane every 3 - 8 minutes
		if (!expressArrival) {
			expressArrival = (rand() % 6) + 3;
			newCustomer.customerNumber = customerNumber++;
			newCustomer.serviceTime = (rand() % 6) + 3;
			expressWait += newCustomer.serviceTime;
			newCustomer.totalTime = expressWait;
			enqueue(&expressLane, newCustomer);
			printf("Customer number %d arrived in express lane at %02d:%02d\n", newCustomer.customerNumber, hours, minutes);
		}

		//Decrement service time of front normal lane customer
		//Customer leaves if service time 0
		if (!isEmpty(normalLane)) {
			normalLane.pHead->customerInfo->serviceTime--;
			if (normalLane.pHead->customerInfo->serviceTime <= 0) {
				printf("Customer Number %d finished checking out of normal lane after a %d minute wait time\n",
					normalLane.pHead->customerInfo->customerNumber, normalLane.pHead->customerInfo->totalTime);
				dequeue(&normalLane);
			}
		}

		//Decrement service time of front express lane customer
		//Customer leaves if service time 0
		if (!isEmpty(expressLane)) {
			expressLane.pHead->customerInfo->serviceTime--;
			if (expressLane.pHead->customerInfo->serviceTime <= 0) {
				printf("Customer Number %d finished checking out of express lane after a %d minute wait time\n",
					expressLane.pHead->customerInfo->customerNumber, expressLane.pHead->customerInfo->totalTime);
				dequeue(&expressLane);
			}
		}
	}
	printf("simulation complete\n");
	system("pause");
	return 0;
}