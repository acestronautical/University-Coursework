/*Exercise Plan Attributes:
 The class ExercisePlan is used to represent a daily exercise plan.
Your class must include three data members to represent your 
goal steps (an integer), plan name (a std::string), and date for which the plan is intended (a std::string). 
Your goal steps represent the number of desired steps for a day.*/

#pragma once
#include <iostream>
#include <string>

class ExcercisePlan {
private:
	int stepGoal;
	std::string planName;
	std::string date;

public:
	ExcercisePlan(int argStepGoal = 0, std::string argPlanName = "Default Excercise Plan", std::string argDate = "01/01/2017");
	ExcercisePlan(const ExcercisePlan &argExcercisePlan);
	~ExcercisePlan();
	int getStepGoal() const;
	std::string getPlanName() const;
	std::string getDate() const;
	void setStepGoal(const int &argStepGoal);
	void setPlanName(const std::string &argPlanName);
	void setDate(const std::string &argDate);
	void editGoal();
	friend std::istream& operator >> (std::istream &stream, ExcercisePlan &plan);
	friend std::ostream& operator << (std::ostream &stream, const ExcercisePlan &plan);
};
