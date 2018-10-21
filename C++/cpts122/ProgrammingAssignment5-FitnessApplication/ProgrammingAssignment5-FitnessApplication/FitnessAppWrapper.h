/*The class FitnessAppWrapper is used to “wrap” the application.
This class should contain two lists (must be an array, vector, or linked list) of weekly (7 days) plans:
one diet and one exercise weekly plan. It must also contain two fstream objects (input/output file streams):
one for each file. It must define the following member functions (some prototypes are given to you, but not all!):
-      void runApp (void): 
starts the main application.
-      void loadDailyPlan (fstream &fileStream, DietPlan &plan): 
must define two of these functions; one for a DietPlan and one for an ExercisePlan. 
This function reads one record from the given stream. 
These will be considered overloaded functions! 
Precondition: file is already open!
-      void loadWeeklyPlan (fstream &fileStream, DietPlan weeklyPlan[ ]): 
must define two of these functions; one for a DietPlan and one for an ExercisePlan. 
This function must read in all seven daily plans from the given stream. 
Note: the array parameter would change if using a vector or linked list! 
This function should call loadDailyPlan () directly. 
Precondition: file is already open!
-      displayDailyPlan (): 
writes a daily plan to the screen. 
You must apply the overloaded stream insertion operator here! 
Note: you must determine the appropriate parameters and return type. 
Once again you must define two of these!
-      displayWeeklyPlan (): 
writes a weekly plan to the screen. 
This function must call displayDailyPlan (). 
Note: you must determine the appropriate parameters and return type. 
Once again you must define two of these!
-      storeDailyPlan (): 
writes a daily plan to a file. 
You must apply the overloaded stream insertion operator here! 
Note: you must determine the appropriate parameters and return type. 
Once again you must define two of these!
-      storeWeeklyPlan (): 
writes a weekly plan to a file. 
This function must call storeDailyPlan (). 
You must apply the overloaded stream insertion operator here! 
Note: you must determine the appropriate parameters and return type. 
Once again you must define two of these!
 
-      displayMenu (): displays nine menu options. These include:
1.    Load weekly diet plan from file.
2.    Load weekly exercise plan from file.
3.    Store weekly diet plan to file.
4.    Store weekly exercise plan to file.
5.    Display weekly diet plan to screen.
6.    Display weekly exercise plan to screen.
7.    Edit daily diet plan.
8.    Edit daily exercise plan.
9.    Exit.   // Note: this must write the most recent weekly plans to the corresponding files.
 
-      Other functions? There should be!*/
#pragma once
#include "DietPlan.h"
#include "ExcercisePlan.h"
#include <vector>
#include <fstream>
#include <iostream>

class FitnessAppWrapper {
private:
	//private data members
	std::vector<DietPlan> dietPlan;
	std::vector<ExcercisePlan> excercisePlan;
	std::fstream dietPlanStream;
	std::fstream excercisePlanStream;
	std::string dietPlansFile;
	std::string excercisePlansFile;
	//private member functions
	int displayMenu();
	void loadDailyPlan(std::fstream &fileStream, DietPlan &argDietPlan);
	void loadDailyPlan(std::fstream &fileStream, ExcercisePlan &argExcercisePlan);
	void loadWeeklyPlan(std::fstream &fileStream, std::vector<DietPlan> &dietPlan);
	void loadWeeklyPlan(std::fstream &fileStream, std::vector<ExcercisePlan> &excercisePlan);
	void displayDailyPlan(DietPlan argDietPlan);
	void displayDailyPlan(ExcercisePlan argExcercisePlan);
	void displayWeeklyPlan(std::vector<DietPlan> dietPlan);
	void displayWeeklyPlan(std::vector<ExcercisePlan> excercisePlan);
	void storeDailyPlan(std::fstream &fileStream, DietPlan &argDietPlan);
	void storeDailyPlan(std::fstream &fileStream, ExcercisePlan &argExcercisePlan);
	void storeWeeklyPlan(std::fstream &fileStream, std::vector<DietPlan> &dietPlan);
	void storeWeeklyPlan(std::fstream &fileStream, std::vector<ExcercisePlan> &excercisePlan);
	void editDailyPlan(DietPlan &argDietPlan);
	void editDailyPlan(ExcercisePlan &argExcercisePlan);
	void editWeeklyPlan(std::vector<DietPlan> &dietPlan);
	void editWeeklyPlan(std::vector<ExcercisePlan> &excercisePlan);

public:
	void runApp(void);

	FitnessAppWrapper(std::string dietPlansFile = "dietPlans.txt", std::string excercisePlansFile = "excercisePlans.txt");
	~FitnessAppWrapper();

	std::vector<DietPlan> getDietPlan();
	std::vector<ExcercisePlan> getExcercisePlan();
	void setDietPlan(std::vector<DietPlan> argDietPlan);
	void setExcercisePlan(std::vector<ExcercisePlan> argExcercisePlan);
};