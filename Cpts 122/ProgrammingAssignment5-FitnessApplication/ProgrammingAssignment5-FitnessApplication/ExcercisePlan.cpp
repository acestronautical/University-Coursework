#include "ExcercisePlan.h"
//constructor
ExcercisePlan::ExcercisePlan(int argStepGoal, std::string argPlanName, std::string argDate) {
	stepGoal = argStepGoal;
	planName = argPlanName;
	date = argDate;
}
//copy constructor totally unnecassary default does the same thing and is not used in this program
ExcercisePlan::ExcercisePlan(const ExcercisePlan & argExcercisePlan)
{
	stepGoal = argExcercisePlan.stepGoal;
	planName = argExcercisePlan.planName;
	date = argExcercisePlan.date;
}
//destructor
ExcercisePlan::~ExcercisePlan() {
	//std::cout << "ExcercisePlan destructor";
}
//getter
int ExcercisePlan::getStepGoal() const {
	return stepGoal;
}
//getter
std::string ExcercisePlan::getPlanName() const {
	return planName;
}
//getter
std::string ExcercisePlan::getDate() const {
	return date;
}
//setter
void ExcercisePlan::setStepGoal(const int &argStepGoal) {
	stepGoal = argStepGoal;
}
//setter
void ExcercisePlan::setPlanName(const std::string &argPlanName) {
	planName = argPlanName;
}
//setter
void ExcercisePlan::setDate(const std::string &argDate) {
	date = argDate;
}
//edit goal
void ExcercisePlan::editGoal()
{
	int n;
	std::cin >> n;
	setStepGoal(n);
}
//overloaded extraction
std::istream& operator >> (std::istream &stream, ExcercisePlan &plan) {
	std::string blank;
	stream >> std::ws;
	getline(stream, plan.planName);
	stream >> plan.stepGoal >> plan.date;
	return stream;
}
//overloaded insertion
std::ostream& operator << (std::ostream &stream, const ExcercisePlan &plan) {
	stream << plan.getPlanName() << std::endl << plan.getStepGoal() << std::endl << plan.getDate() << std::endl << std::endl;
	return stream;
}