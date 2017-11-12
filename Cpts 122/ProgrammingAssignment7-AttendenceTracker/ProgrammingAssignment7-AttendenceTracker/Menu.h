#pragma once
#include <iostream>
#include <string>
#include "List.h"

class Menu
{
public:
	Menu();
	~Menu();
	void display();
	int getChoice();
	void launch();
	void reportRecent();
	void reportThreshold();

private:
	List students;

	void importCourseList();
	void loadMasterList();
	void storeMasterList();
	void markAbsences();
	void editAbsences();
	void generateReport();
};

