//data members :
//-mTreeSold : BST
//- mTreePurchased : BST
//- mCsvStream : ifstream
//
//Member functions :
//-A function that opens data.csv // yes, it’s private, and must use mCsvStream to open the file
//- A function that reads one line from the file and splits the line into units, type, and transaction fields
//- A function that loops until all lines are read from the file; calls the function below,
//and then displays the current contents of both BSTs; use inOrderTraversal() to display the trees
//- A function that compares the transaction field and inserts the units and type into the appropriate tree(mTreeSold or mTreePurchased) 
// note with the way the data.csv file is organized the trees will be fairly balanced
//- A function that writes to the screen the trends we see in our tree; 
//the function must display the type and number of units that are least purchased and sold, 
//and the most purchased and sold
//+ runAnalysis(), which is the only public function in the class, 
//aside from possibly a constructor and / or destructor; this function calls the other private functions

#pragma once
#include "BST.h"
#include "TransactionNode.h"
#include <fstream>
#include <string>
#include <sstream>
using std::string;
using std::stringstream;

enum Transaction {Purchased, Sold, Invalid};

class DataAnalysis
{
public:
	DataAnalysis();
	~DataAnalysis();
	void runAnalysis();

private:
	bool openFile(string filePath);
	bool parseLine(int units, string type, Transaction transaction);
	void parseFile();
	bool insertItem(int units, string type, Transaction transaction);
	void displayTrends();

	BST<TransactionNode> mTreeSold;
	BST<TransactionNode> mTreePurchased;
	std::ifstream mCsvStream;
};

DataAnalysis::DataAnalysis()
{
	
}

DataAnalysis::~DataAnalysis()
{
}

//+ runAnalysis(), which is the only public function in the class, 
//aside from possibly a constructor and / or destructor; this function calls the other private functions
inline void DataAnalysis::runAnalysis()
{
	openFile("data.csv");
	parseFile();
}

//-A function that opens data.csv // yes, it’s private, and must use mCsvStream to open the file
inline bool DataAnalysis::openFile(string filePath)
{
	mCsvStream.open(filePath);
}

//- A function that reads one line from the file and splits the line into units, type, and transaction fields
inline bool DataAnalysis::parseLine(int units, string type, Transaction transaction)
{
	bool success = true;
	string line;
	string substr;
	getline(mCsvStream, line);
	stringstream ss(line);
	getline(ss, substr, ',');
	units = stoi(substr);
	getline(ss, substr, ',');
	type = substr;
	getline(ss, substr, ',');
	if (substr == "Purchased")
		transaction = Purchased;
	else if (substr == "Sold")
		transaction = Sold;
	else
		success = false, transaction = Invalid;

	return success;
}

//- A function that loops until all lines are read from the file; calls the function below,
//and then displays the current contents of both BSTs; use inOrderTraversal() to display the trees
inline void DataAnalysis::parseFile()
{
	int units; string type; Transaction transaction;
	while (parseLine(units, type, transaction))
		insertItem(units, type, transaction);
	mTreePurchased.inorder(std::cout);
	mTreeSold.inorder(std::cout);
}

//- A function that compares the transaction field and inserts the units and type into the appropriate tree(mTreeSold or mTreePurchased) 
// note with the way the data.csv file is organized the trees will be fairly balanced
inline bool DataAnalysis::insertItem(int units, string type, Transaction transaction)
{
	bool success = true;
	TransactionNode node(units, type);
	if (transaction == Purchased)
		mTreePurchased.insertNode(&node);
	else if (transaction == Sold)
		mTreeSold.insertNode(&node);
	else if (transaction == Invalid)
		success = false;
	return success;
}

//- A function that writes to the screen the trends we see in our tree; 
//the function must display the type and number of units that are least purchased and sold, and the most purchased and sold
inline void DataAnalysis::displayTrends()
{
}
