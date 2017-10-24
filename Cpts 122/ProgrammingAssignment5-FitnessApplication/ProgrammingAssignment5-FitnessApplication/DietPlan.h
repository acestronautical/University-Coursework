/*Diet Plan Attributes:
The class DietPlan is used to represent a daily diet plan.
Your class must include three data members to represent your 
goal calories (an integer), plan name(a std::string), and date for which the plan is intended(a std::string).
The maximum intake of calories for a day is stored in the goal calories.*/


#pragma once
#include <iostream>
#include <string>

class DietPlan {
	int calorieGoal;
	std::string planName;
	std::string date;

public:
	DietPlan(int argCalorieGoal = 0, std::string argPlanName = "Default Diet Plan", std::string argDate = "01/01/2017");
	DietPlan(const DietPlan &argDietPlan);
	~DietPlan();
	int getCalorieGoal() const;
	std::string getPlanName() const;
	std::string getDate() const;
	void setCalorieGoal(const int &argCalorieGoal);
	void setPlanName(const std::string &argPlanName);
	void setDate(const std::string &argDate);
	void editGoal();
	friend std::istream& operator >> (std::istream &stream, DietPlan &plan);
	friend std::ostream& operator << (std::ostream &stream, DietPlan const &plan);
};