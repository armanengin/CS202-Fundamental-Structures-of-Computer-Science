
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Arman Engin Sucu
* ID: 21801777
* Section : 1
* Assignment : 4
* Description : Header file for the queue(main reason for implementing queue is to enable breadth first search)
**/

class Queue {
public:
	//CONSTRUCTORS & DESTRUCTORS
	Queue();
	~Queue();

	//METHODS
	int dequeue();
	void enqueue(int item);
	bool isEmpty();

private:
	int* queue;
	int back;
	int front;
};
#endif 