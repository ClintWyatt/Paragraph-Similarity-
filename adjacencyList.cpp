#include "adjacencyList.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>



adjacencyList::adjacencyList() {


}
/*
@name: ~adjacencyList
@parameters: none
@return: none
@throws: none implemented
@description: The destructor calls the destroy graph function, which deletes all the nodes dynamically allocated.

*/
adjacencyList::~adjacencyList() {

	destroyGraph();
}

/*
@name: setReplacements
@parameters: int x
@returns: none
@throws: none implemented
@description: mutator function sets the number of replacements (if possible) for a synonym in the paragraph
inputted by the user.
*/
void adjacencyList::setReplacements(int x) {

	numReplacements = x;
}
/*
@name: setList
@parameters: string file
@returns: none
@throws: none implemented
@description: setList is executed in the main file after the setRows function. The file name, "file", is passed in as 
a argument and is opened by the inFileList variable. Then, each line from the synnonym list is passed to the setRow function
to determine if subgraphs can be linked to each other.
*/
void adjacencyList::setList(string file) {

	string line;
	inFileList.open(file);//opening the file
	
	//here, each line from the synnonym list is passed into the setRow function
	while (getline(inFileList, line)) {
		
		setRow(line);
	}


	inFileList.close();
}
/*
@name: setRow
@parameters: string line
@returns: none
@throws: none implemented
@descritpion:setRow executes inside a loop of the setList function.
setRow function puts all the synonyms from the line of the input file into a adjacency list for the subgraph.
Then, the current row is passed into the addToList function to see if any of the synonyms appear earlier in
the adjacency list.
*/
void adjacencyList::setRow(string line) {

	
	string word;
	
	int numNodes = 0;
	
	for (int i = 0; i < line.length(); i++) {

		if (line[i] != ':' && line[i] != ',') {
			word += line[i];
		}
		else {
			//creating a new node to put to the adjacency list
			node *nde = new node;
			nde->_word = word;
			if (graph[rowNum].first == NULL) {
				graph[rowNum].first = nde;
				graph[rowNum].last = nde;
				nde->next = NULL;
				word.clear();
				graph[rowNum].size++;
			}
			else {
				graph[rowNum].last->next = nde;
				graph[rowNum].last = nde;
				graph[rowNum].size++;
				word.clear();
			}

		}
	}
	node *nde = new node;
	nde->_word = word;
	graph[rowNum].last->next = nde;
	graph[rowNum].last = nde;
	
	graph[rowNum].size++;
	
	//if there are more than 2 nodes, the last node will point to the first node, making a loop
	/*if (graph[rowNum].size > 2) {
		graph[rowNum].last->next = graph[rowNum].first;
	}*/
	/*else {
		graph[rowNum].last->next = NULL;
	}*/
	int x = 0;

	//addToList(rowNum) >1
	//checking to see if the current adjacency list has any matching words earlier in the list.
	//rowNum is the current row of the synnonyms being added
	addToList(rowNum); 
		
		
	rowNum++;
}

/*
not used
*/
void adjacencyList::printList() {

	shortListCheck.open("shList1.txt");
	node *current = NULL;
	int j = 0;
	//works
	for (int i = 0; i < graph.size(); i++) {

		if (graph[i].first != NULL) {
			current = graph[i].first;

			while (j < graph[i].size) {
				shortListCheck << current->_word << " ";
				//cout << current->_word << " ";
				current = current->next;
				j++;
			}
			j = 0;
			shortListCheck << endl;
			cout << endl;
		}
	}


}
/*
@name: setRows
@parameters: fstream &inf
@returns: none
@throws: none implemented
@description: After the user has entered a valid file for the synonnym list, the setRows function loops through the entire user
entered file and determines how many lines there are. After the file has been looped through, the graph vector uses the 
resize function (from the vector library) on the rows variable.
*/
void adjacencyList::setRows(fstream &inf) {

	string line;

	while (getline(inf, line)) {

		rows++; //incrementing the number of rows
	}

	graph.resize(rows);
	//Graph = new adjList[rows];
}

void adjacencyList::destroyGraph() {

	node *current = NULL;
	node *trailCurrent = NULL;
	for (int i = 0; i < rows; i++) {

		//if the first node is not null
		if (graph[i].first != NULL) {

			graph[i].last->next = NULL;
			graph[i].last = NULL;
			current = graph[i].first;
			trailCurrent = graph[i].first;
			graph[i].first = NULL;

			while (current != NULL) {
				trailCurrent = current;
				current = current->next;
				trailCurrent->next = NULL;
				delete trailCurrent;
			}
		}

	}
}
/*
@name: changeParagraph
@parameters: string file
@returns: none
@throws: none implemented
@description: changeParagraph function is executed if the user decides to do synnonym replacements. The parameter,
string file, is the entire paragraph from the inputfile. This function builds the paragraph slowly, each word
is created by checking for non word characters. After the word is created, it is checked in the wordrepalcement
function and concateneated to the variable newParagraph.
*/
void adjacencyList::changeParagraph(string file) {


	
	
	setCycle();
	string line, newWord;
	paragraph1.open(file);
	
	int nextIndex = 1;
	while (getline(paragraph1, line)) {

		copyParagraph.append(line);
	}

	for (int index =0, index2=0; index < copyParagraph.length(); index++) {

		if (copyParagraph[index] != '.' && copyParagraph[index] != ',' && copyParagraph[index] != '!' && copyParagraph[index] != '?' && copyParagraph[index] != ' ' && copyParagraph[index] != ';') {

			newWord+=copyParagraph[index];
			if (index2 == 0) {
				newWord[index2] = toUnder(newWord[index2]);
			}
			index2++;

		}
		else {

			if (newWord.length() > 0) {
				newParagraph += wordReplacement(newWord);
				
			}
				newWord.clear();
				index2 = 0;
			if (copyParagraph[index] == '.') {
				newParagraph += '.';
				//index++;
			}
			else if (copyParagraph[index] == '!') {
				newParagraph += '!';
				//index++;
			}
			else if (copyParagraph[index] == '?') {
				newParagraph += '?';
				//index++;
			}
			else if (copyParagraph[index] == ' ') {
				newParagraph += ' ';
				//index++;
			}
			else if (copyParagraph[index] == ',') {
				newParagraph += ',';
				//index++;
			}
			else if (copyParagraph[index] == ';') {

				newParagraph += ';';
			}


		}
	}

	//printing the new paragraph
	cout << newParagraph << endl;
	outFile.open("output1.txt");
	outFile << newParagraph;

}
/*
@name: wordReplacement
@parameters: string str
@returns: string str
@throws: none implemented
@description: word replacement is executed in the changeParagraph function. If the number of replacements does not exceed the paragraph 
size, then 
*/
string adjacencyList::wordReplacement(string str) {

	bool found = false;
	node *current = NULL;
	int j = 0;
	for (int i = 0; i < graph.size(); i++) {

		//if the first pointer to the adjacency list is not NULL
		if (graph[i].first != NULL) {
			current = graph[i].first;

			//if the word from the paragraph equals the first node
			if (str == graph[i].first->_word) {

				current = graph[i].first;
				//if the number of replacements is less than the list size at the graphs index.
				if (graph[i].size > numReplacements) {
					//looping until we go through the number of replacements


					while (j < numReplacements) {

						current = current->next;
						j++;
					}
					str = current->_word;
					return str;
				}
				//break will only be encountered if the number of replacements exceeds the size of the adjacency list,
				//and str will be returned at the bottom of the function.
				break;
			}

			//case that the word does not match the first index.
			else {

				//look to see if the word appears in the linked list
				current = graph[i].first->next; //advancing current to the next node
				for (int y = 1; y < graph[i].size; y++) {
					if (current->_word == str) {
						found = true;
						break;
					}
					else {
						current = current->next;
					}
				}
				
				//if the word was found
				if (found == true) {

					//if the number of replacements is less than the size of the adjacency list
					if (graph[i].size < numReplacements) {

						while (j < numReplacements) {

							current = current->next;
							j++;
						}
						str = current->_word;
						return str;
					}
					//if the size of the linked list is less than 2
					if (graph[i].size < 3) {
						while (j < numReplacements) {

							current = graph[i].first;
							j++;
						}
						str = current->_word;
						return str;
					}
					//if the linked list is greater than 2
					else {

						while (j < numReplacements) {

							current = current->next;
							j++;
						}
						str = current->_word;
						return str;
					}
				}
			}
		}
		
	}

	return str;
}
/*
@name: addToList
@parameters: int x
@retruns: 0 if no synnonyms are added to different rows, int index if synnonyms are added to a earlier row.
@throws: none implemented
@description: addToList function takes in the current row from the setRow function.
If a earlier row has a word in the current synnonym list, then the current synnonym list is added
to the earlier row and the current row's first and last pointers are set to NULL since the current
row has no use anymore. Then, the earlier row checks for word duplicates and deletes the duplicated word.
*/
int adjacencyList::addToList(int x) {

	int i = 0;
	bool found = false;
	//creating a node to traverse the adjacency list to check for earlier words in the list
	node *earlyRow = NULL;
	node *trailPtr = NULL;
	node *laterRow = NULL;
	int index = 0;
	//if the row in the adjacency list is greater than 0
	if (x > 0) {

		if (graph[x].first != NULL) {
		for (i; i < x; i++) {

			/*here we see if a word has appeared earlier in the adjacency list. If the word has, then we add the
			approite verticies to the adjacency list at the specified row, which is i
			*/
			if (graph[i].first != NULL) {
				earlyRow = graph[i].first;
				//trailPtr = graph[i].first;
				laterRow = graph[x].first;
				//while the pointer to the adjacency list that we are testing (graph[x]) does not equal last's next pointer
				while (laterRow != graph[x].last->next) {

					//if later row's word equals the earlier row's word, add nodes from graph[x] to graph[i]
					if (laterRow->_word == earlyRow->_word) {
						
						graph[i].size += graph[x].size;
						graph[i].last->next = graph[x].first;
						graph[x].last->next = NULL;
						graph[i].last = graph[x].last;
						graph[x].first = NULL;
						graph[x].last = NULL;
						
						index = i;
						found = true;
						break;
					}
					else {
						trailPtr = earlyRow;
						earlyRow = earlyRow->next;
						//if the earlyRow is at the end of the list
						if (earlyRow == graph[i].last->next) {
							earlyRow= graph[i].first;
							trailPtr = graph[i].first;
							//advancing the later row pointer
							laterRow = laterRow->next;
						}
					}


				}

				//if found is true, we exit the for loop
				if (found == true) {
					break;
				}
			}
		}
		
		//checking for duplicates if more synnonyms were added to a row
		if (found == true) {
			//current1 = NULL;
			node *current = graph[index].first->next;

			node *trailcurrent = graph[index].first;
			node *flag = graph[index].first;
			/*
			Here, the flag pointer will only advance if current has reached the end of the list (is NULL)
			*/
			while (flag->next != NULL) {

				//if 2 words match
				if (current->_word == flag->_word) {

					graph[index].size--;//decrementing the size since a word will be deleted
					//if the last word matches a earlier word
					if (current == graph[index].last) {
						graph[index].last = trailcurrent;//setting the last node to trail current
						trailcurrent->next = NULL;//setting trailcurrent's next to be NULL
						graph[index].last->next = NULL;
						delete current;
						//now going back to the flag
						flag = flag->next;
						current = flag->next;
						trailcurrent = flag;

					}

					//if word other than the last word matches a earlier word
					else {
						//if currents next pointer is not null
						if (current->next != NULL) {
							trailcurrent->next = current->next;
							current->next = NULL;
							delete current;
							current = flag->next;
							trailcurrent = flag;
						}
						
					}
				}
				//if we get to the end of the list and there are no duplicates
				else if (current == graph[index].last) {

					flag = flag->next;
					current = flag->next;
					trailcurrent = flag;
				}
				//words dont match
				else {
					trailcurrent = current;
					current = current->next;

				}

			}

			return index; //returning the index for adding to a adjacency list
		}
		return 0;//returning zero for not adding to a adjacency list
	}
}

	return 0; //returning zero for not adding to a adjacency list

}
/*
@name: setCycle
@parameters: none
@returns: none
@throws: none implemented
@description: setCycle function is called at the end of the secondPass function. If the size of the current list in the
adjacency list is greater then 2, then a cycle is set on the current row with the list.
*/
void adjacencyList::setCycle() {

	for (int i = 0; i < graph.size(); i++) {

		if (graph[i].first != NULL) {

			//setting the cycle if the size of the list is greater than 2.
			if (graph[i].size > 2) {
				graph[i].last->next = graph[i].first;
			}
		}
	}
}
/*
@name: secondPass
@parameters: none
@returns: none
@throws: none implemented
@description: secondPass function (executes after the setList function) goes through the adjacencyList backwards, starting at the last index. Some of the 
words that are the same were not able to be connected when the adjacency list was set up. Going from the bottom of 
the adjacency list up to the top (after going from the top to the bottom of the list) will match all remaining synnonyms
togeather.
*/
void adjacencyList::secondPass() {
	

	//having to go through the graph again, but this time starting at the last index.
	for (int i = rowNum-1; i > -1; i--) {
		addToList(i);
	}
	//setting the last pointer to point their next pointer to the first pointer if the list size is greater than 2
	setCycle();
	//printList();
}
/*
@name: setParagraphs
@parameters: string file, string file2
@returns: none
@throws: none implemented
@description: setParagraphs function takes in the string representation of the file names
for both paragraphs. After each paragraph is opened, each word from the file is added to a vector.
If the size of both vectors differ, then the program terminates since the paragraphs have different word counts.
If the size of both vectors are the same, then the BFS search algorithm is used on words that are different.

*/

void adjacencyList::setParagraphs(string file, string file2) {

	//setCycle();
	//getting the data for paragraph 1
	string line, newWord;
	paragraph1.open(file);
	while (getline(paragraph1, line)) {

		copyParagraph.append(line);
	}

	//getting the data for paragraph 2
	paragraph2.open(file2);
	while (getline(paragraph2, line)) {

		copyParagraph2.append(line);
	}

	//getting all words from paragraph1 and putting them into a vector
	for (int index = 0, index2 = 0; index < copyParagraph.length(); index++) {

		if (copyParagraph[index] != '.' && copyParagraph[index] != ',' && copyParagraph[index] != '!' && copyParagraph[index] != '?' && copyParagraph[index] != ' ') {

			newWord += copyParagraph[index];
			if (index2 == 0) {
				newWord[index2] = toUnder(newWord[index2]);
			}
			index2++;
		}
		else {

			if (newWord.length() > 0) {
				listWords1.push_back(newWord);
			}
			newWord.clear();
			index2 = 0;
		}
	}

	//getting all words from paragraph2 and putting them into a vector
	for (int index = 0, index2=0; index < copyParagraph2.length(); index++) {

		if (copyParagraph2[index] != '.' && copyParagraph2[index] != ',' && copyParagraph2[index] != '!' && copyParagraph2[index] != '?' && copyParagraph2[index] != ' ') {

			newWord += copyParagraph2[index];
			if (index2 == 0) {
				newWord[index2] = toUnder(newWord[index2]);
			}
			index2++;
		}
		else {

			if (newWord.length() > 0) {
				
				listWords2.push_back(newWord);
			}
			newWord.clear();
			index2 = 0;



		}
	}

	/*checking to see if the 2 paragraphs have the same length. If they do, then 
	the BFS search algorithm will be used to compare both words. 
	*/
	if (listWords1.size() == listWords2.size()) {

		for (int i = 0; i < listWords1.size(); i++) {

			//if the words match in both paragraphs, which will be words that are not found in the synonnym graph.
			if (listWords1[i] == listWords2[i]) {

			}

			//if the words don't match
			else {

				/* Since both words don't match, then the paragraphs are not similar 
				IF a word from the first paragraph is not in any subgraph.
				*/
				/*Here, if a synnonym in the first paragraph does not exist, then the program will terminate*/
				
				if ((inList(listWords1[i])) == false) {
					cout << "The paragraphs do not match. " << listWords1[i] << " does not match " << "any words in the ";
					cout << "adjacency List and does not match " << listWords2[i] << endl;
					return;
				}
				/*Case that the word from the first paragraph is in the graph*/
				else {

					/*If paragraph 1 and paragraph 2 do not a synnonyms that are similar to each other, then
					the program terminates*/
					if ((BFS(graphFound[graphFoundIndex], listWords1[i], listWords2[i])) == false) {
						cout << "Paragraphs do not match. Terminating the program...." << endl;
						return;
					}
				}
			}
		}

		cout << "Both paragraphs are similar. The hemming distance is " <<hammingDistance << endl;
	}
	//if the number of words in both paragraphs are different.
	else {
		cout << "Paragraphs do not have the same length. Terminating program...." << endl;
		return;
	}

	
}
/*
@name: inList
@parameters: string str
@returns: true if the synnonym is in any subgraph, false if the synnonym(str) is not in the subgraph
@throws: none implemented
@description: This function tests to see if the word(str) is a synnonym. If the words from
paragraph 1 and paragraph 2 don't match, then this function gets executed. This function is executed in the setParagraphs
function.
*/

bool adjacencyList::inList(string str) {

	int index = 0;
	node *current;
	node *trailCurrent = NULL;
	for (int i = 0; i < graph.size(); i++) {

		//if there is a adjacency list at the index
		if (graph[i].first != NULL) {

			current = graph[i].first;
			while(trailCurrent != graph[i].last){
				trailCurrent = current;
				//if the word is found in the adjacency list
				if (current->_word == str) {
					graphFound.push_back(i);//pushing the found row into a integer vector
					return true;
				}
				trailCurrent = current;
					current = current->next;
				
			}

		}
	
	
	
	}


	return false;
}
/*
@name: BFS
@parameters: int x, string correctWord, attemptedWord
@returns: false on the BFS failed, true on the BFS sucessful
@throws: none implemented
@description: BFS search algorithm attempts to find the attempted word in comparisson to the corrected word. 
If the attempted word is found in the same adjacency list row, then the algorithm ends and true is returned. If the
attempted word is not found, then false is returned and the program terminates since the paragraphs are not similar.
*/

bool adjacencyList::BFS(int x, string correctWord, string attemptedWord) {

	bool found = false;
	bool inSet = false;
	vector<string> discoveredSet;
	vector<string> frontierQueue;
	node *current = graph[x].first;//pointing to the index of the adjacency list were a synnonym was found 


	//finding where the correctWord is in the adjacency graph.
	while (found == false) {

		//if the word from paragraph1 is found, break the loop
		if (current->_word == correctWord) {
			break;
		}
		//advancing the current pointer
		current = current->next;
	}
	//creating a string that will represent a verticie in the graph
	string currentVertice;

	/*
		Starting the BFS algorithm

		now, pushing the first node of the graph index to the discovered set and the frontierQueue
	*/

	frontierQueue.push_back(current->_word);
	discoveredSet.push_back(current->_word);

	//while the frontier queue is not empty
	while (frontierQueue.size() > 0) {
		
		//having the current verticie equal to the first index of the frontier queue
		currentVertice = frontierQueue[0];
		//poping the queue by erasing the first element
		frontierQueue.erase(frontierQueue.begin());
		//visiting the next node
		current = current->next;
		hammingDistance++;

		
		//checking to see if the next verticie is in the discovered set. If it is, nothing is added to the frontier queue
		if (current->_word == discoveredSet[0]) {
			inSet = true;
		}
		
		//checking to see if the current verticie(word) is in the discovered set. If it's not, then we
		//continue the algorithm by adding to the frontier queue
		if (inSet == false) {
			frontierQueue.push_back(current->_word);
			discoveredSet.push_back(current->_word);
		}

		if (attemptedWord == currentVertice) {//if the word from paragraph 2 is found
			graphFoundIndex++; //graphFoundIndex is incremented to check for the next set of synnonyms.
			return true;
		}

	}


	//if no word is found, then false is returned and the paragraphs are not similar
	return false;
}

char adjacencyList::toUnder(char c) {

	if (c == 'A') {
		return 'a';
	}
	else if (c == 'B') {
		return 'b';
	}
	else if (c == 'C') {
		return 'c';
	}
	else if (c == 'D') {
		return 'd';
	}
	else if (c == 'E') {
		return 'e';
	}
	else if (c == 'F') {
		return 'f';
	}
	else if (c == 'G') {
		return 'g';
	}
	else if (c == 'H') {
		return 'h';
	}
	else if (c == 'I') {
		return 'i';
	}
	else if (c == 'J') {
		return 'j';
	}
	else if (c == 'K') {
		return 'k';
	}
	else if (c == 'L') {
		return 'l';
	}
	else if (c == 'M') {
		return 'm';
	}
	else if (c == 'N') {
		return 'n';
	}
	else if (c == 'O') {
		return 'o';
	}
	else if (c == 'P') {
		return 'p';
	}
	else if (c == 'Q') {
		return 'q';
	}
	else if (c == 'R') {
		return 'r';
	}
	else if (c == 'S') {
		return 's';
	}
	else if (c == 'T') {
		return 't';
	}
	else if (c == 'U') {
		return 'u';
	}
	else if (c == 'V') {
		return 'v';
	}
	else if (c == 'W') {
		return 'w';
	}
	else if (c == 'X') {
		return 'x';
	}
	else if (c == 'Y') {
		return 'y';
	}
	else if (c == 'Z') {
		return 'z';
	}
	return c;
}