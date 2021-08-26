#ifndef WORDNETWORK_H
#define WORDNETWORK_H

#include <iostream>
#include "HashTable.h"
#include "Queue.h"
using namespace std;

/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Arman Engin Sucu
* ID: 21801777
* Section : 1
* Assignment : 4
* Description : Header file for WordNetwork program
**/

class WordNetwork {
public:
	//CONSTRUCTORS & DESTRUCTORS
	WordNetwork(const string vertexFile, const string edgeFile);
	~WordNetwork();
	//MAIN METHODS
	void listNeighbors(const string word);
	void listNeighbors(const string word, const int distance);
	void listConnectedComponents();
	void findShortestPath(const string word1, const string word2);

	//AUXILIARY METHODS
	void dfsWithDistance(int vertex, const string word, int distance); //Special Depth first search to find the vertex with distance
	void dfsWithDistanceHelper(int vertex, const string word, int distance, int const constDistance, bool visited[]);
	int findDifferentLetters(string word1, string word2);// a method finds number of different letter between 2 strings(an helper method for dfsWithDistance)
	void dfsForConnectedComponents(int vertex, bool* visited);// a method that traverse a connected component of a graph with dfs and prints each vertex that traversed
	int* bfsToFindShorthestPath(int vertexStart, int vertexDestination, bool& finded);//a method to find the shortest path between two vertexes eith bst
	void reversePrintShortestPath(int* path, int startVer, int destVer);//a recursive method to print the vertexes in reverse order(an auxilary method for findShortestPath)
private:
	HashTable hashTable;
	int** adjMatrix;//graph representation(adjacency matrix)
	string wordArray[5757];//an array to allocate all elements of the graph
};

#endif // !WORDNETWORK_H