#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>

using namespace std;

/*
* Title: Heaps
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 3
* Description: header file for simuulator
*/

class Simulator {
public:

	//STRUCT
	struct printerRequest {
		int id;
		int priority;
		int requestTime;
		int processTime;

		printerRequest() {// default constructor 
			this->id = 0;
			this->priority = 0;
			this->requestTime = 0;
			this->processTime = 0;
		}

		printerRequest(const int id, const int priority, const int requestTime, const int processTime) {
			this->id = id;
			this->priority = priority;
			this->requestTime = requestTime;
			this->processTime = processTime;
		}
	};

	struct printer {
		bool isPrinting;
		printerRequest request;
		int startedTime;
		printer() {
			this->isPrinting = false;
			this->startedTime = 0;
		}
	};

	//CONSTRUCTORS
	Simulator(const string textFile);
	~Simulator();

	//METHODS
	void insertToPriorityQueue(printerRequest request);
	printerRequest deleteFromPriorityQueue();
	void heapRebuild(int root);
	double calculateAvgTime(int printerNum);
	bool hasPrinterFinished(int time, int size, printer** printerArray );
	bool hasPrinterStarted(int time, int size, printer** printerArray, int& currentRequestNum, double& avgWaitTime);
	bool queueIsEmpty();
	int findMinRequiredPrinter(int maxAvgWaitTime, double& avgWaitTime);
	void printSimulation(int neededPrinterNum); //kind of remaked calculateAvgTime method
	void auxilaryPrintSimulation(int time, int printerNum, printer** printerArray, int& currentRequestNum ); //auxilary method for printSimulaton and remaked version of hasPrinterStarted
	void simulation(int maxAvgWaitTime); //final method which simulates the printer simulation


private:
	printerRequest* priorityQueue;
	printerRequest** requestsArray;
	string* result;
	int resultSize;
	int size; //size(max-1) for the both priorityQueue and requestsArray
	int queueSize; // size for number of elements in the queue
};

#endif // !SIMULATOR_H