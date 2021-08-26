
#include <iostream>
#include "Queue.h"
using namespace std;

/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Arman Engin Sucu
* ID: 21801777
* Section : 1
* Assignment : 4
* Description : Source file for the queue(main reason for implementing queue is to enable breadth first search)
**/

//CONSTRUCTORS & DESTRUCTORS
Queue::Queue(){
	queue = new int [5757];
	front = 0;
	back = 0;
}

Queue::~Queue() {
	delete[] queue;
}

int Queue::dequeue() {
	int result = queue[front];
	if (isEmpty()) {
		return -1;//return -1 if the queue is empty
	}
	else {
		front = (front + 1) % 5757;//implementing with circular array
	}
	return result;
}
void Queue::enqueue(int item) {
	if ((back + 1) % 5757 == front) {//if the queue is full return without adding new item to the queue
		return;
	}
	else {
		queue[back] = item;
		back = (back + 1) % 5757;//implementing with circlular array
	}
}

bool Queue::isEmpty() {
	return front == back;
}