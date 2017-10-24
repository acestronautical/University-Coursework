#include "FitnessAppWrapper.h"
//constructor
FitnessAppWrapper::FitnessAppWrapper(std::string argDietPlansFile, std::string argExcercisePlansFile) {
	dietPlansFile = argDietPlansFile;
	excercisePlansFile = argExcercisePlansFile;
}
//destructor
FitnessAppWrapper::~FitnessAppWrapper() {
}
//getter
std::vector<DietPlan> FitnessAppWrapper::getDietPlan() {
	return dietPlan;
}
//getter
std::vector<ExcercisePlan> FitnessAppWrapper::getExcercisePlan() {
	return excercisePlan;
}
//setter
void FitnessAppWrapper::setDietPlan(std::vector<DietPlan> argDietPlan) {
	dietPlan = argDietPlan;
}
//setter
void FitnessAppWrapper::setExcercisePlan(std::vector<ExcercisePlan> argExcercisePlan) {
	excercisePlan = argExcercisePlan;
}
//main application
void FitnessAppWrapper::runApp(void) {
	int choice = 0;
	while (choice = displayMenu(), choice != 9) {
		switch (choice)
		{
		case 1:
			loadWeeklyPlan(dietPlanStream, dietPlan);
			break;
		case 2:
			loadWeeklyPlan(excercisePlanStream, excercisePlan);
			break;
		case 3:
			storeWeeklyPlan(dietPlanStream, dietPlan);
			break;
		case 4:
			storeWeeklyPlan(excercisePlanStream, excercisePlan);
			break;
		case 5:
			displayWeeklyPlan(dietPlan);
			break;
		case 6:
			displayWeeklyPlan(excercisePlan);
			break;
		case 7:
			editWeeklyPlan(dietPlan);
			break;
		case 8:
			editWeeklyPlan(excercisePlan);
			break;
		case 9:
			storeWeeklyPlan(dietPlanStream, dietPlan);
			storeWeeklyPlan(excercisePlanStream, excercisePlan);
			//exit loop
			break;
		default:
			std::cout << "Invalid selection" << std::endl;
			break;
		}
	}
}
//used by run app, outputs an integer
int FitnessAppWrapper::displayMenu() {
	int userInput;
	std::cout << std::string(50, '\n');
	std::cout <<
		"1.    Load weekly diet plan from file\n"
		"2.    Load weekly exercise plan from file\n"
		"3.    Store weekly diet plan to file\n"
		"4.    Store weekly exercise plan to file\n"
		"5.    Display weekly diet plan to screen\n"
		"6.    Display weekly exercise plan to screen\n"
		"7.    Edit daily diet plan\n"
		"8.    Edit daily exercise plan\n"
		"9.    Exit\n" << std::endl;
	std::cin >> userInput;
	std::cout << std::string(50, '\n');
	return userInput;
}

//loads a single daily diet plan from file
void FitnessAppWrapper::loadDailyPlan(std::fstream &fileStream, DietPlan &argDietPlan) {
	fileStream >> argDietPlan;
	//std::cout << "loadDailyPlan read: " << argDietPlan.getPlanName() << argDietPlan.getCalorieGoal() << argDietPlan.getDate() << std::endl;
	//system("pause");
}
//loads a single daily excercise plan from file
void FitnessAppWrapper::loadDailyPlan(std::fstream &fileStream, ExcercisePlan &argExcercisePlan) {
	fileStream >> argExcercisePlan;
	//std::cout << "loadDailyPlan read: " << argExcercisePlan.getPlanName() << argExcercisePlan.getStepGoal() << argExcercisePlan.getDate() << std::endl;
	//system("pause");
}

//loads 7 diet plans from file then closes file
void FitnessAppWrapper::loadWeeklyPlan(std::fstream &fileStream, std::vector<DietPlan> &dietPlan) {
	DietPlan tempDietPlan;
	fileStream.open(dietPlansFile, std::fstream::in);
	for (int i = 0; i < 7; i++) {
		tempDietPlan.setPlanName("empty");
		tempDietPlan.setCalorieGoal(0);
		tempDietPlan.setDate("empty");
		loadDailyPlan(dietPlanStream, tempDietPlan);
		dietPlan.push_back(tempDietPlan);
	}
	fileStream.close();
	std::cout << "Diet Plan Loaded" << std::endl;
	system("pause");
}

//loads 7 excercise plans from file then closes file
void FitnessAppWrapper::loadWeeklyPlan(std::fstream &fileStream, std::vector<ExcercisePlan> &excercisePlan) {
	ExcercisePlan tempExcercisePlan;
	fileStream.open(excercisePlansFile, std::fstream::in);
	for (int i = 0; i < 7; i++) {
		tempExcercisePlan.setPlanName("empty");
		tempExcercisePlan.setStepGoal(0);
		tempExcercisePlan.setDate("empty");
		loadDailyPlan(excercisePlanStream, tempExcercisePlan);
		excercisePlan.push_back(tempExcercisePlan);
	}
	fileStream.close();
	std::cout << "Excercise Plan Loaded" << std::endl;
	system("pause");
}

//displays a single diet plan
void FitnessAppWrapper::displayDailyPlan(DietPlan argDietPlan) {
	std::cout << argDietPlan;
}

//display a single excercise plan
void FitnessAppWrapper::displayDailyPlan(ExcercisePlan argExcercisePlan) {
	std::cout << argExcercisePlan;
}

//displays seven diet plans
void FitnessAppWrapper::displayWeeklyPlan(std::vector<DietPlan> dietPlan) {
	for (std::vector<DietPlan>::iterator iter = dietPlan.begin(); iter != dietPlan.end(); iter++) {
		displayDailyPlan(*iter);
	}
	system("pause");
	std::cout << std::string(100, '\n');

}

//displays seven excercise plans
void FitnessAppWrapper::displayWeeklyPlan(std::vector<ExcercisePlan> excercisePlan) {
	for (std::vector<ExcercisePlan>::iterator iter = excercisePlan.begin(); iter != excercisePlan.end(); iter++) {
		displayDailyPlan(*iter);
	}
	system("pause");
	std::cout << std::string(100, '\n');

}

//stores a single diet plan
void FitnessAppWrapper::storeDailyPlan(std::fstream &fileStream, DietPlan &argDietPlan) {
	fileStream << argDietPlan;
}

//stores a single excercise plan
void FitnessAppWrapper::storeDailyPlan(std::fstream &fileStream, ExcercisePlan &argExcercisePlan) {
	fileStream << argExcercisePlan;
}

//stores a week of diet plans
void FitnessAppWrapper::storeWeeklyPlan(std::fstream &fileStream, std::vector<DietPlan> &dietPlan) {
	if (dietPlan.empty()) {
		std::cout << "Please Load A Plan First" << std::endl;
		system("pause");
		return;
	}
	else {
		std::cout << "Plan Stored" << std::endl;
		system("pause");
	}
	fileStream.open(dietPlansFile, std::fstream::out);
	for (std::vector<DietPlan>::iterator iter = dietPlan.begin(); iter != dietPlan.end(); iter++) {
		storeDailyPlan(fileStream, *iter);
	}
	fileStream.close();
}

//stores a week of excercise plans
void FitnessAppWrapper::storeWeeklyPlan(std::fstream &fileStream, std::vector<ExcercisePlan> &excercisePlan) {
	if (dietPlan.empty()) {
		std::cout << "Please Load A Plan First" << std::endl;
		system("pause");
		return;
	}
	else {
		std::cout << "Plan Stored" << std::endl;
		system("pause");
	}
	fileStream.open(excercisePlansFile, std::fstream::out);
	for (std::vector<ExcercisePlan>::iterator iter = excercisePlan.begin(); iter != excercisePlan.end(); iter++) {
		storeDailyPlan(fileStream, *iter);
	}
	fileStream.close();
}
//allows editing of single plans
void FitnessAppWrapper::editDailyPlan(DietPlan &argDietPlan) {
	std::string input = "";
	char yesNo = 'x';
	std::cout << "Editing this Plan:" << std::endl;
	displayDailyPlan(argDietPlan);
	std::cout << "Would you like to edit this plan?" << std::endl;
	std::cin.ignore();
	do
	{
		std::cout << "Edit this Plan? [y/n]" << std::endl;
		std::cin >> yesNo;
	} while (!std::cin.fail() && yesNo != 'y' && yesNo != 'n');
	if (yesNo == 'n') return;
	int num = 0;
	std::cout << "Enter New Daily Plan Name:" << std::endl;
	std::cin.ignore();
	getline(std::cin, input);
	argDietPlan.setPlanName(input);
	std::cout << "Enter New Calorie Goal:" << std::endl;
	std::cin >> num;
	argDietPlan.setCalorieGoal(num);
	std::cout << "Enter New Date in the format MM/DD/YY:" << std::endl;
	std::cin.ignore();
	getline(std::cin, input);
	argDietPlan.setDate(input);
}
//allows sequential editing of plans, no templates allowed on this assignment
void FitnessAppWrapper::editDailyPlan(ExcercisePlan &argExcercisePlan) {
	std::string input = "";
	char yesNo = 'x';
	std::cout << "Editing this Plan:" << std::endl;
	displayDailyPlan(argExcercisePlan);
	std::cout << "Would you like to edit this plan?" << std::endl;
	std::cin.ignore();
	do
	{
		std::cout << "Edit this Plan? [y/n]" << std::endl;
		std::cin >> yesNo;
	} while (!std::cin.fail() && yesNo != 'y' && yesNo != 'n');
	if (yesNo == 'n') return;
	int num;
	std::cout << "Enter New Daily Plan Name:" << std::endl;
	std::cin.ignore();
	getline(std::cin, input);
	argExcercisePlan.setPlanName(input);
	std::cout << "Enter New Calorie Goal:" << std::endl;
	std::cin >> num;
	argExcercisePlan.setStepGoal(num);
	std::cout << "Enter New Date in the format MM/DD/YY:" << std::endl;
	std::cin.ignore();
	getline(std::cin, input);
	argExcercisePlan.setDate(input);
}
void FitnessAppWrapper::editWeeklyPlan(std::vector<DietPlan> &dietPlan) {
	for (std::vector<DietPlan>::iterator iter = dietPlan.begin(); iter != dietPlan.end(); iter++) {
		editDailyPlan(*iter);
		std::cout << std::string(100, '\n');
	}
}
void FitnessAppWrapper::editWeeklyPlan(std::vector<ExcercisePlan> &excercisePlan) {
	for (std::vector<ExcercisePlan>::iterator iter = excercisePlan.begin(); iter != excercisePlan.end(); iter++) {
		editDailyPlan(*iter);
		std::cout << std::string(100, '\n');
	}
}
