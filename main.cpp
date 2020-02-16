#include <iostream>
#include <fstream>
#include "Graph.h"
#include <vector>
#include <sstream>
using namespace std;

int main()
{
	//Local Variables
	ifstream inputFile;
	string stringStorage;
	string temp;
	vector<string> stringParseStorage;
	Graph graph;

	inputFile.open("airports.csv");
	if (inputFile.is_open())
	{
		cout << "File opened." << endl;
	}
	else
	{
		cout << "File failed to open." << endl;
		return 0;
	}

	//Reads the book.
	while (inputFile >> stringStorage)
	{
		stringParseStorage.clear();

		stringstream parseMe(stringStorage);

		while (getline(parseMe, stringStorage, ','))
		{
			stringParseStorage.push_back(stringStorage);
		}
		if (stringParseStorage.size() == 3)
		{
			graph.addLink(stringParseStorage.at(0), stringParseStorage.at(1), stringParseStorage.at(2));
		}
	}

	cout << "Enter airport you are coming from." << endl;
	cin >> stringStorage;
	cout << endl << "Enter airport you are going to" << endl;
	cin >> temp;
	cout << endl << graph.testConnection(stringStorage, temp) << endl;


	inputFile.close();
	cout << "File closed." << endl << endl;

	return 0;
}
