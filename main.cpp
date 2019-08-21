#include <iostream>
#include <string>
#include "adjacencyList.h"
#include <fstream>

using namespace std;

int main() {


	fstream inFile, inFile2, paragraph, paragraph2;
	string synonym, synonym2, line;
	adjacencyList adjList;
	char choice;
	int numReplacements = 0;
	/*
	setting up the list of synonms 
	*/
	cout << "Enter a file for synonym Replacement: ";
	cin >> synonym;
	inFile.open(synonym);

	while (!inFile) {

		cout << "ERROR: invalid file name. To quit, enter 'q'. Enter a valid file name: ";
		cin >> synonym;

		if (synonym == "q") {
			exit(0);
		}
		inFile.open(synonym);
	}

	adjList.setRows(inFile);

	inFile.close();
	adjList.setList(synonym);
	adjList.secondPass();
	
	cout << "Enter 1 for synnonym replacement, 2 for paragraph similarity analysis. " << endl;
	cin >> choice;

	//if the user chooses synonym replacement
	if (choice == '1') {

		cout << "Enter the paragraph for synonym replacement: ";
		cin >> synonym;
		paragraph.open(synonym);
		while (!paragraph) {
			cout << "ERROR: invalid file name. To quit, enter 'q'. Enter the paragraph for synonym replacement: ";
			cin >> synonym;
			if (synonym == "q") {
				exit(0);
			}
			paragraph.open(synonym);
		}
		//prompt the user to enter the amount of repalcements for all possible words
		cout << "enter the number of random replacements for all possible words: ";
		cin >> numReplacements;
		adjList.setReplacements(numReplacements);
		adjList.changeParagraph(synonym);

	}

	//if the user chooses paragraph similarity analysis
	else {

		cout << "Enter the first paragraph: ";
		cin >> synonym;
		paragraph.open(synonym);
		//testing to see if the files are valid
		while (!paragraph) {
			cout << "ERROR: invalid file name. To quit, enter 'q'. Enter the paragraph for synonym replacement: ";
			cin >> synonym;
			if (synonym == "q") {
				exit(0);
			}
			paragraph.open(synonym);
		}
		cout << "Enter the second paragraph; ";
		cin >> synonym2;
		paragraph2.open(synonym2);
		while (!paragraph2) {
			cout << "ERROR: invalid file name. To quit, enter 'q'. Enter the paragraph for synonym replacement: ";
			cin >> synonym2;
			if (synonym == "q") {
				exit(0);
			}
			paragraph2.open(synonym2);
		}
		//setting the 2 paragraphs to be compared
		adjList.setParagraphs(synonym, synonym2);
	

	}
	return 0;
}
