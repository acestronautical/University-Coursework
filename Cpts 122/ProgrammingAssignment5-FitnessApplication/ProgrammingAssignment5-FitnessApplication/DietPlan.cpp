#include "DietPlan.h"
//constructor
DietPlan::DietPlan(int argCalorieGoal, std::string argPlanName, std::string argDate) {
	calorieGoal = argCalorieGoal;
	planName = argPlanName;
	date = argDate;
}
//copy constructor totally unnecassary default does the same thing and is not use in this program
DietPlan::DietPlan(const DietPlan & argDietPlan)
{
	calorieGoal = argDietPlan.calorieGoal;
	planName = argDietPlan.planName;
	date = argDietPlan.date;
}
//destructor
DietPlan::~DietPlan() {
	//std::cout << "DietPlan destructor";
}
//getter
int DietPlan::getCalorieGoal () const {
	return calorieGoal;
}
//getter
std::string DietPlan::getPlanName () const{
	return planName;
}
//getter
std::string DietPlan::getDate() const {
	return date;
}
//setter
void DietPlan::setCalorieGoal(const int &argCalorieGoal) {
	calorieGoal = argCalorieGoal;
}
//setter
void DietPlan::setPlanName(const std::string &argPlanName) {
	planName = argPlanName;
}
//setter
void DietPlan::setDate(const std::string &argDate) {
	date = argDate;
}
//edit goal
void DietPlan::editGoal()
{
	int n;
	std::cin >> n;
	setCalorieGoal(n);
}
//overloaded stream extraction
std::istream& operator >> (std::istream &stream, DietPlan &plan) {
	std::string blank;
	stream >> std::ws;
	getline(stream, plan.planName);
	stream >> plan.calorieGoal >> plan.date;
	return stream;
}
//overloaded stream insertion
std::ostream& operator << (std::ostream &stream, const DietPlan &plan) {
	stream << plan.getPlanName() << std::endl << plan.getCalorieGoal() << std::endl << plan.getDate() << std::endl << std::endl;
	return stream;
}