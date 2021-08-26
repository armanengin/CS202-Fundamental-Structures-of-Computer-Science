
#include "WordNetwork.h"
#include <fstream>
#include <string>

using namespace std;

/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Arman Engin Sucu
* ID: 21801777
* Section : 1
* Assignment : 4
* Description : Source file for WordNetwork program
**/

//CONSTRUCTORS & DESTRUCTORS
WordNetwork::WordNetwork(const string vertexFile, const string edgeFile) {
	//initialize adjMatrix
	adjMatrix = new int* [5757];
	for (int i = 0; i < 5757; i++) {
		adjMatrix[i] = new int[5757];
		for (int j = 0; j < 5757; j++) {
			adjMatrix[i][j] = 0;
		}
	}
	//get words from the vertexFile and add them to the hash table
	ifstream vertexfileStream;
	string word;// this string holds the keys for hash table from the vertexFile
	vertexfileStream.open(vertexFile.c_str(), ios_base::in);
	vertexfileStream.clear();
	vertexfileStream.seekg(0, vertexfileStream.beg);
	int lineNum = 0;
	while (vertexfileStream.eof() != true) {
		getline(vertexfileStream, word, '\n'); //get the words from the vertexFile
		wordArray[lineNum] = word;// add word to the wordArray
		hashTable.add(word, lineNum++);//add wprds to the hash table
	}

	//get edgeinformation from the edgeFile and create the adjacency matrix accordiing to it
	ifstream edgeFileStream;
	string edge1;
	string edge2;
	int line1;
	int line2;
	edgeFileStream.open(edgeFile.c_str() , ios_base::in);
	edgeFileStream.clear();
	edgeFileStream.seekg(0, edgeFileStream.beg);
	while (edgeFileStream.eof() != true) {
		getline(edgeFileStream, edge1, ',');//get the first edge from the edgeFile
		getline(edgeFileStream, edge2, '\n');//get the second edge from the edgeFile

		line1 = hashTable.getItem(edge1);
		line2 = hashTable.getItem(edge2);

		//create the undirected edges
		adjMatrix[line1][line2] = 1;
		adjMatrix[line2][line1] = 1;
	}
}

WordNetwork::~WordNetwork() {
	for (int i = 0; i < 5757; i++) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
}

//MAIN METHODS
void WordNetwork::listNeighbors(const string word) {
	int index = hashTable.getItem(word);
	if (index == -1) {
		cout << "The word does not exist in the graph" << endl;
	}
	else {
		cout << "Neighbors of " << word << " :" << endl;
		for (int i = 0; i < 5757; i++) {
			if (adjMatrix[index][i] == 1) {
				cout << wordArray[i] << endl;
			}
		}
	}
	cout << endl;//to make the output readable
}

void WordNetwork::listNeighbors(const string word, const int distance) {
	int index = hashTable.getItem(word);
	if (index == -1) {
		cout << "The word does not exist in the graph" << endl;
	}
	else {
		cout << "Neighbours of " << word << " with the distance " << distance << " :" << endl;
		dfsWithDistance(index, word, distance);
	}
	cout << endl;//to make the output readable
}

void WordNetwork::listConnectedComponents() {
	int numOfConnection = 0;
	bool* visited = new bool[5757];//create an array to keep the info of which vertex has been traversed
	for (int i = 0; i < 5757; i++) {
		visited[i] = false;//initalize all values with false
	}
	for (int i = 0; i < 5757; i++) {
		if (visited[i] == false) {
			numOfConnection++;
			cout << "Connected component " << numOfConnection << ":" << endl;
			dfsForConnectedComponents(i, visited);
		}
	}
	delete[] visited;//deallocate the visited array
	cout << endl;//to make the output readable
}

void WordNetwork::findShortestPath(const string word1, const string word2) {
	int start = hashTable.getItem(word1);
	int end = hashTable.getItem(word2);
	bool finded = false;
	if (hashTable.getItem(word1) == -1 && hashTable.getItem(word2) != -1) {
		cout << "Shortest path from " << word1 << " to " << word2 << " couldn't find, since " << word1 << " does not exist in the graph." << endl;
	}
	else if (hashTable.getItem(word2) == -1 && hashTable.getItem(word1) != -1) {
		cout << "Shortest path from " << word1 << " to " << word2 << " couldn't find, since " << word2 << " does not exist in the graph." << endl;
	}
	else if (hashTable.getItem(word2) == -1 && hashTable.getItem(word1) == -1) {
		cout << "Shortest path from " << word1 << " to " << word2 << " couldn't find, since both of the words do not exist in the graph." << endl;
	}
	else {
		int* path = bfsToFindShorthestPath(start, end, finded);
		if (finded == false) {
			cout << "Shortest path from " << word1 << " to " << word2 << " does not exist." << endl;
		}
		else {
			cout << "Shortest path from " << word1 << " to " << word2 << " : " << endl;
			cout << word1 << endl;
			reversePrintShortestPath(path, start, end);
			cout << word2 << endl;
		}
		delete[] path;//deallocate the represantation of shorthest path which was allocated in reversePrintShortestPath method
	}
	cout << endl;//to make the output readable
}

//AUXILIARY METHODS
void WordNetwork::dfsWithDistance(int vertex, const string word, int distance) {
	bool visited[5757];
	for (int i = 0; i < 5757; i++) {
		visited[i] = false;
	}
	visited[vertex] = true; //Mark start vertex as visited
	dfsWithDistanceHelper(vertex, word, distance, distance, visited);
}

void WordNetwork::dfsWithDistanceHelper(int vertex, const string word, int distance, int const constDistance, bool visited[]) {
	if (distance == 0) {
		if(findDifferentLetters(wordArray[vertex], word) == constDistance) //check if number of different letters is equal to constDistance, because of the circles some time different letter number is smaaler than the constDistance
		cout << wordArray[vertex] << endl;
		return;
	}
	for (int i = 0; i < 5757; i++) {
		if (adjMatrix[vertex][i] == 1 && visited[i] != true) {
			visited[i] = true;
			dfsWithDistanceHelper(i, word, distance - 1, constDistance, visited);
		}
	}
}

int WordNetwork::findDifferentLetters(string word1, string word2) {// a method finds number of different letter between 2 strings(an helper method for dfsWithDistance)
	int result = 0;
	for (int i = 0; i < 5; i++) {//we know that strings' size is 5 
		if (word1[i] != word2[i])
			result++;
	}
	return result;
}

void WordNetwork::dfsForConnectedComponents(int vertex, bool* visited) {
	if (visited[vertex] == false) {
		string word = wordArray[vertex];//print the vertex since it is being traversed now
		cout << word << endl;
		visited[vertex] = true; //mark as true to not traverse it again
		for (int i = 0; i < 5757; i++) {
			if (adjMatrix[vertex][i] == 1) { //if it is a adjacent vertex
				dfsForConnectedComponents(i, visited);
			}
		}
	}
}

int* WordNetwork::bfsToFindShorthestPath(int vertexStart, int vertexDestination, bool& finded) {
	int* path = new int[5757];//allocate memory from heap for shortest path represantation
	bool visited[5757];
	for (int i = 0; i < 5757; i++) {
		visited[i] = false;
	}
	Queue queue;
	queue.enqueue(vertexStart);
	visited[vertexStart] = true;// mark start vertex as visited already

	while (queue.isEmpty() != true) {//keep going until queue is empty
		int currVer = queue.dequeue();
		for (int i = 0; i < 5757; i++) {
			if (adjMatrix[currVer][i] == 1 && visited[i] != true) {
				queue.enqueue(i);
				visited[i] = true;
				path[i] = currVer;
				if (i == vertexDestination) {//if destination is found return and prevent unnecessary traverses
					finded = true;//the shorthest path is exist
					return path;
				}
			}
		}
	}
	finded = false;//the shorthest path does npt exist
	return path;
}

void WordNetwork::reversePrintShortestPath(int* path, int startVer, int destVer) {//recursively prints the vertex that belongs to the shorthest path
	if (startVer != path[destVer]) {
		reversePrintShortestPath(path, startVer, path[destVer]);
		cout << wordArray[path[destVer]] << endl;
	}
}