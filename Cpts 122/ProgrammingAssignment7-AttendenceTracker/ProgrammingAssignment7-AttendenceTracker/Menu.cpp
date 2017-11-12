#include "Menu.h"
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iostream>

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::display()
{
	std::cout <<
		"1.    Import course list\n"
		"2.    Load master list\n"
		"3.    Store master list\n"
		"4.    Mark absences\n"
		"5.    BONUS: Edit absences\n"
		"6.    Generate report\n"
		"7.    Exit\n" << std::endl;
}

int Menu::getChoice(){
	char choice = 0;
	std::cin >> choice;
	while (choice > '7' || choice < '1') {
		std::cout << "Please enter a number between 1 and 7:" << std::endl;
		std::cin >> choice;
		std::cin.clear();
	}
	return choice;
}

void Menu::launch()
{
	char choice = 0;
	while (choice != 7) {
		display();
		choice = getChoice();
		if (choice == '1') { importCourseList(); }
		else if (choice == '2') { loadMasterList(); }
		else if (choice == '3') { storeMasterList(); }
		else if (choice == '4') { markAbsences(); }
		else if (choice == '5') { editAbsences(); }
		else if (choice == '6') { generateReport(); }
		else if (choice == '7') { break; }
	}
}

void Menu::reportRecent()
{
	ListNode* curNode = students.getHeadPtr();
	while (curNode) {
		cout << curNode->getStudentRecord().name << " was most recently absent " << curNode->getStudentAbsences()->peek() << std::endl;
		curNode = curNode->getNextPtr();
	}
}

void Menu::reportThreshold()
{
	int choice = -1;
	cout << "Enter number of absences for threshhold:" << endl;
	while (choice < 0 || choice > 105) {
		cout << "number: ";
		cin >> choice;
	}
	
	ListNode* curNode = students.getHeadPtr();
	while (curNode) {
		if (curNode->getNumAbsences() >= choice) {
			cout << curNode->getStudentRecord().name << " has had " << curNode->getStudentAbsences()->getSize() << " total absences" << std::endl;
		}
		curNode = curNode->getNextPtr();
	}
}

void Menu::importCourseList()
{
	char choice = '\0';
	cout << "This will remove current saved absence data, continue?" << endl;
	while (choice != 'y' && choice != 'n') {
		cout << "y/n: ";
		cin >> choice;
	}
	if (choice == 'n')
		return;

	students.destroyList();
	StudentRecord record;
	string parseLine;
	string substr;
	std::fstream classList;
	classList.open("classList.csv", std::fstream::in);
	while (getline(classList, parseLine)) {
		if (parseLine[0] == ',')
			continue;
		std::stringstream ss(parseLine);
		getline(ss, substr, ',');
		record.uid = substr;
		getline(ss, substr, ',');
		record.id = substr;
		getline(ss, substr, ',');
		record.name = substr;
		getline(ss, substr, ',');
		record.name += ",";
		record.name += substr;
		getline(ss, substr, ',');
		record.email = substr;
		getline(ss, substr, ',');
		record.units = substr;
		getline(ss, substr, ',');
		record.program = substr;
		getline(ss, substr, ',');
		record.level = substr;

		students.insertAtFront(record);
	}
	classList.close();
	cout << "list created from roster" << endl;
}

void Menu::loadMasterList()
{
	students.destroyList();
	StudentRecord record;
	string parseLine;
	string substr;
	std::fstream classList;
	classList.open("master.txt", std::fstream::in);
	while (getline(classList, parseLine)) {
		if (parseLine[0] == ',')
			continue;
		std::stringstream ss(parseLine);
		getline(ss, substr, ',');
		record.uid = substr;
		getline(ss, substr, ',');
		record.id = substr;
		getline(ss, substr, ',');
		record.name = substr;
		getline(ss, substr, ',');
		record.name += ",";
		record.name += substr;
		getline(ss, substr, ',');
		record.email = substr;
		getline(ss, substr, ',');
		record.units = substr;
		getline(ss, substr, ',');
		record.program = substr;
		getline(ss, substr, ',');
		record.level = substr;

		students.insertAtFront(record);

		while (getline(ss, substr, ',')) {
			students.getHeadPtr()->getStudentAbsences()->push(substr);
		}

	}
	classList.close();
	cout << "list loaded" << endl;
}

void Menu::storeMasterList()
{
	if (students.isEmpty()) {
		cout << "Please load a list" << endl;
		return;
	}
	StudentRecord record;
	Stack<string> temp;
	string date;
	std::fstream masterList;
	ListNode* curNode = students.getHeadPtr();
	masterList.open("master.txt", std::fstream::out);
	while (curNode) {
		record = curNode->getStudentRecord();
		masterList << record.uid << "," << record.id << "," << record.name << ","
			<< record.email << "," << record.units << "," << record.program << "," << record.level;
		while (!curNode->getStudentAbsences()->isEmpty())
			temp.push(curNode->getStudentAbsences()->pop());
		while (!temp.isEmpty()) {
			date = temp.pop();
			masterList << "," << date;
			curNode->getStudentAbsences()->push(date);
		}
		masterList << std::endl;
		curNode = curNode->getNextPtr();
	}
	masterList.close();
}

void Menu::markAbsences()
{
	if (students.isEmpty()) {
		cout << "Please load a list" << endl;
		return;
	}
	ListNode* curNode = students.getHeadPtr();
	char choice = '\0';
	string stringTime;

	while (curNode) {
		choice = '\0';
		cout << "would you like to mark " << curNode->getStudentRecord().name << " as absent?" << endl;
		while (choice != 'y' && choice != 'n') {
			cout << "y/n: ";
			cin >> choice;
		}
		if (choice == 'y') {
			time_t t = time(0);
			struct tm * now = localtime(&t);
			stringTime = std::to_string(now->tm_year + 1900) + '-' + std::to_string(now->tm_mon + 1) + '-' + std::to_string(now->tm_mday);
			if (curNode->getStudentAbsences()->peek() != stringTime) {
				curNode->getStudentAbsences()->push(stringTime);
				cout << "absence noted, student will be punished remotely via shock collar\n" << endl;
			}
			else
				cout << "you have already marked " << curNode->getStudentRecord().name << " as absent today" << endl;
		}
		else
			cout << "presence noted, student will be rewarded for their obedience\n" << endl;

		curNode = curNode->getNextPtr();
	}
}

void Menu::editAbsences()
{
	if (students.isEmpty()) {
		cout << "Please load a list" << endl;
		return;
	}
	string date;
	ListNode* curNode = students.getHeadPtr();
	Stack<string> temp;
	char choice;
	while (curNode) {
		choice = '\0';
		cout << "would you like to edit absences for " << curNode->getStudentRecord().name << "?" << endl;
		while (choice != 'y' && choice != 'n') {
			cout << "y/n: ";
			cin >> choice;
		}
		if (choice == 'y' && !curNode->getStudentAbsences()->isEmpty()) {
			while (!curNode->getStudentAbsences()->isEmpty())
				temp.push(curNode->getStudentAbsences()->pop());
			while (!temp.isEmpty()) {
				date = temp.pop();
				cout << "remove absence on " << date << "?" << endl;
				choice = '\0';
				while (choice != 'y' && choice != 'n') {
					cout << "y/n: ";
					cin >> choice;
				}
				if (choice == 'n')
					curNode->getStudentAbsences()->push(date);
			}
		}
		else
			cout << "this student has never been absent, pay more attention teacher" << endl;
		curNode = curNode->getNextPtr();
	}
}

void Menu::generateReport()
{
	if (students.isEmpty()) {
		cout << "Please load a list" << endl;
		return;
	}

	char choice = '\0';
	cout << "1.See most recent absences" << endl;
	cout << "2.See absences above threshold" << endl;
	while (choice != '1' && choice != '2') {
		cout << "1/2: ";
		cin >> choice;
	}
	if (choice == '1')
		reportRecent();
	else if (choice == '2')
		reportThreshold();

}
