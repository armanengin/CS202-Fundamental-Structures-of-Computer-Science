#include <iostream>
#include <fstream>
#include <string>
#include "simulator.h"

using namespace std;

/*
* Title: Heaps
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 3
* Description: source file of the simulator 
*/

//CONSTRUCTORS
Simulator::Simulator(const string textFile) {
	ifstream printerRequestData;
	string fileName = textFile;
	string sizeString;

	string idString;
	string priorityString;
	string requestTimeString;
	string processTimeString;

	//Open the stream for the data file
	printerRequestData.open(fileName.c_str(), ios_base::in);
	printerRequestData.clear();
	printerRequestData.seekg(0, printerRequestData.beg);

	getline(printerRequestData, sizeString, '\n'); // get the number of print requests
	int sizeInt = stoi(sizeString);
	//cout << "size of the requests are: " << sizeInt << endl;
	requestsArray = new printerRequest* [sizeInt];

	int index = 0;
	while (printerRequestData.eof() == false) {
		getline(printerRequestData, idString, ' ');
		//cout << "id string: " << idString << endl;
		getline(printerRequestData, priorityString, ' ');
		//cout << "priorityString: " << priorityString << endl;
		getline(printerRequestData, requestTimeString, ' ');
		//cout << "requestTimeString: " << requestTimeString << endl;
		getline(printerRequestData, processTimeString, '\n');
		//cout << "processTimeString: " << processTimeString << endl;

		int idInt = stoi(idString);
		int priorityInt = stoi(priorityString);
		int requestTimeInt = stoi(requestTimeString);
		int processTimeInt = stoi(processTimeString);

		requestsArray[index++] = new printerRequest(idInt, priorityInt, requestTimeInt, processTimeInt);
	}

	this->priorityQueue = new printerRequest[sizeInt]; // a priority queue with capacity of sizeInt(number of datas in the txt file)
	this->queueSize = 0;
	this->size = sizeInt;
}

Simulator::~Simulator() {
	for (int i = 0; i < size; i++) {
		delete requestsArray[i];
	}
	delete[] requestsArray;
		delete priorityQueue;
}

//METHODS
void Simulator::insertToPriorityQueue(printerRequest request) {
	priorityQueue[queueSize] = request; // add new item

	int place = queueSize;
	int parent = ( place - 1 )/2;
	while ( place > 0 && ( (priorityQueue[place].priority > priorityQueue[parent].priority) || ( (priorityQueue[place].priority == priorityQueue[parent].priority) && (priorityQueue[place].id < priorityQueue[parent].id) ) ) ) {
		printerRequest temp = priorityQueue[place];
		priorityQueue[place] = priorityQueue[parent];
		priorityQueue[parent] = temp;
		place = parent;
		parent = (place - 1) / 2;
	}
	queueSize++;
}

Simulator::printerRequest Simulator::deleteFromPriorityQueue() {
	printerRequest result = priorityQueue[0];
	if (queueSize > 0) {
		priorityQueue[0] = priorityQueue[--queueSize];
		heapRebuild(0);
	}
	return result;
}

void Simulator::heapRebuild(int root) {
	int child = 2 * root + 1; // child is the left child of the root
	if (child < queueSize) {
		int rightChild = child + 1;
		if ( ( priorityQueue[child].priority < priorityQueue[rightChild].priority ) || ( ( priorityQueue[child].priority == priorityQueue[rightChild].priority) && ( priorityQueue[child].id > priorityQueue[rightChild].id ) ) ) {
			child = rightChild;//get the larger child of the root
		}

		if ((priorityQueue[child].priority > priorityQueue[root].priority) || ((priorityQueue[child].priority == priorityQueue[root].priority) && (priorityQueue[child].id < priorityQueue[root].id))) {//if child greater than root swap 
			printerRequest temp = priorityQueue[child];
			priorityQueue[child] = priorityQueue[root];
			priorityQueue[root] = temp;
			heapRebuild(child);//keep doing the same until finding the place of the root 
		}
	}
}

double Simulator::calculateAvgTime(int printerNum) {
	int time = 1;
	double waitTime = 0;
	int printernum = 0;
	int index = 0;
	int currentRequestNum = 0;
	printer** printerArray = new printer*[printerNum];

	for (int i = 0; i < printerNum; i++) {
		printerArray[i] = new printer(); //initialize the printers
	}

	do {	
		while (index < size) {
			if (requestsArray[index]->requestTime <= time) { //selecting the printed request according to priorities
				insertToPriorityQueue(*requestsArray[index]);
				index++;
			}
			else
				break;
		}


			hasPrinterStarted(time, printerNum, printerArray, currentRequestNum, waitTime);
			
			if (hasPrinterFinished(time, printerNum, printerArray)) {
				hasPrinterStarted(time, printerNum, printerArray, currentRequestNum, waitTime);// if any printer is finished check if there are any printers ready to start
			}
			
			time++;

	} while (currentRequestNum < size);// if currentRequestNum = size then we have printed all requests finish the loop

	//delete allocated heap for printerArray
	for (int i = 0; i < printerNum; i++) {
		delete printerArray[i];
	}
	delete[] printerArray;

			return waitTime / size;
}


bool Simulator::hasPrinterFinished(int time, int printerNum, printer** printerArray) {
	bool result = false;
	for (int i = 0; i < printerNum; i++) {
		if ((printerArray[i]->startedTime + printerArray[i]->request.processTime) == time) {
			printerArray[i]->isPrinting = false;
			result = true;
		}
	}
	return result;
}

bool Simulator::hasPrinterStarted(int time, int printerNum, printer** printerArray, int& currentRequestNum, double& waitTime) {
	bool result = false;
	for (int index = 0; index < printerNum; index++) {
		if (!(printerArray[index]->isPrinting) && !queueIsEmpty()) {
			result = true;
			printerRequest currRequest = deleteFromPriorityQueue();
			printerArray[index]->isPrinting = true;
			printerArray[index]->request = currRequest;
			printerArray[index]->startedTime = time;
			currentRequestNum++;
			waitTime += double(time - currRequest.requestTime);
		}
	}
	return result;
}

bool Simulator::queueIsEmpty() {
	return (queueSize == 0);
}

int Simulator::findMinRequiredPrinter(int maxAvgWaitTime, double& avgWaitTime) {
	int printerNum = 1;
	double waitingTime = calculateAvgTime(printerNum++);
	//double tempWaitingTime = calculateAvgTime(printerNum++);

		while (waitingTime > double(maxAvgWaitTime)) {
			//tempWaitingTime = waitingTime; //tempWaitingTime has the previous waitingTime
			waitingTime = calculateAvgTime(printerNum++);
		}
	avgWaitTime = waitingTime;
	return (printerNum - 1);
}

void Simulator::printSimulation(int neededPrinterNum) {//kind of remaked calculateAvgTime method

	cout << "Minimum number of printers required: " << neededPrinterNum << endl;
	cout << endl;
	cout << "Simulation with " << neededPrinterNum << " printers:" << endl;
	cout << endl;

	int time = 1;
	int index = 0;
	int currentRequestNum = 0;
	printer** printerArray = new printer * [neededPrinterNum];

	for (int i = 0; i < neededPrinterNum; i++) {
		printerArray[i] = new printer(); //initialize the printers
	}

	do {
		while (index < size) {
			if (requestsArray[index]->requestTime <= time) { //selecting the printed request according to priorities
				insertToPriorityQueue(*requestsArray[index]);
				index++;
			}
			else
				break;
		}


		auxilaryPrintSimulation(time, neededPrinterNum, printerArray, currentRequestNum);

		if (hasPrinterFinished(time, neededPrinterNum, printerArray)) {
			auxilaryPrintSimulation(time, neededPrinterNum, printerArray, currentRequestNum);// if any printer is finished check if there are any printers ready to start
		}

		time++;

	} while (currentRequestNum < size);// if currentRequestNum = size then we have printed all requests finish the loop

	//delete allocated heap for printerArray
	for (int i = 0; i < neededPrinterNum; i++) {
		delete printerArray[i];
	}
	delete[] printerArray;
}

void Simulator::auxilaryPrintSimulation(int time, int printerNum, printer** printerArray, int& currentRequestNum ) { //auxilary method for printSimulaton and remaked version of hasPrinterStarted
	bool result = false;
	for (int index = 0; index < printerNum; index++) {
		if (!(printerArray[index]->isPrinting) && !queueIsEmpty()) {
			result = true;
			printerRequest currRequest = deleteFromPriorityQueue();
			printerArray[index]->isPrinting = true;
			printerArray[index]->request = currRequest;
			printerArray[index]->startedTime = time;
			currentRequestNum++;
			cout << "Printer " << index << " prints print request " << currRequest.id << " at minute " << time << " (wait: " << time - currRequest.requestTime << " mins)" << endl;
		}
	}
}

void Simulator::simulation(int maxAvgWaitTime) { //final method which simulates the printer simulation
	double avgWaitTime;
	int neededPrinter = findMinRequiredPrinter(maxAvgWaitTime, avgWaitTime);
	printSimulation(neededPrinter);
	cout << endl;
	cout << "Average waiting time: " << avgWaitTime << " minutes" << endl;
}