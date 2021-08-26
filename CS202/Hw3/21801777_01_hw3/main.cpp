#include <iostream>
#include "simulator.h"
using namespace std;

/*
* Title: Heaps
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 3
* Description: main file 
*/

int main() {

	string fileName;
	int avgWaitingTime;

	cin >> fileName;
	cin >> avgWaitingTime;

	Simulator sim = Simulator(fileName);
	sim.simulation(avgWaitingTime);

}