#ifndef H_adjacencyList
#define H_adjacencyList

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ostream>

using namespace std;

//used as a linked list
struct node {

	string _word;
	node *next = NULL;
};

//the actual graph
struct list {

	node *first = NULL;
	node *last = NULL;
	int size = 0;

};



class adjacencyList {


public:
	~adjacencyList();
	//destructor
	adjacencyList();
	//no-arg constructor
	void setReplacements(int x);
	//sets the number of repleacements for a word, entered by the user. 
	void setList(string file);
	//sets up the list
	void setRows(fstream &inf);
	void destroyGraph();
	void changeParagraph(string file);
	void printList();
	int addToList(int x);
	//used when adding nodes to the adjacency list. Will see if a word has appeared earlier in the list.
	string wordReplacement(string str);
	void setCycle();
	//function will set the cycle of the adjacency lists if they have more than 2 nodes
	void secondPass();

	void setParagraphs(string file, string file2);
	//setting up the first paragraph and second paragraph similarity analysis
	bool inList(string str);
	bool BFS(int x, string correctWord, string attemptedWord);
	char toUnder(char c);

private:
	//adjList* Graph;
	int rowNum = 0;
	int rows = 0;
	int graphFoundIndex = 0; //used to help make the BFS easier and faster. Tracks the location of the adjacency
	//list for a found word in paragraph1 for the similarity analysis.
	int hammingDistance = 0;
	void setRow(string line);
	fstream inFileList;
	int numReplacements = 0;
	fstream paragraph1;
	fstream paragraph2;
	vector<list> graph;
	vector<string> listWords1;//used to compare to list2 for paragraph similarity analysis
	vector<string> listWords2;//used to compare to list1 for paragraph similarity analysis
	vector<int> graphFound; //used for showing where the found rows for listWords1.
	ofstream outFile;
	ofstream shortListCheck;
	string newParagraph, copyParagraph, copyParagraph2;
	bool isTheSame = true;
};

#endif // !H_adjacencyList
#pragma once
