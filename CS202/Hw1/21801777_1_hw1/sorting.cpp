#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sorting.h"
using namespace std;

/*
* Title: Sorting and Algorithm Efficiency
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 1
* Description: a cpp file contains all selection, merge quick and radix sorts with their auxiliary functions
*/

//------IMPLEMENTATIONS FOR ASSIGNMENT FUNCTIONS------
void selectionSort(int* arr, const int size, int& compCount, int& moveCount) {
	// iterate the array from the end 
	for (int lastIndexOfUnsorted = size - 1; lastIndexOfUnsorted >= 1; lastIndexOfUnsorted--) {
		int largest = indexOfLargest(arr, lastIndexOfUnsorted+1, compCount, moveCount);
		swap(arr[largest], arr[lastIndexOfUnsorted], moveCount);
	}
}

void mergeSort(int* arr, const int size, int& compCount, int& moveCount) {
	mergeSortHelper(arr, 0, size - 1, compCount, moveCount);
}

void quickSort(int* arr, const int size, int& compCount, int& moveCount) {
	quickSortHelper(arr, 0, size - 1, compCount, moveCount);
}

void radixSort(int* arr, const int size) {
	int max = getMax(arr, size);
	
	for (int power = 1; max / power > 0; power *= 10) {

		int counter[10] = { 0 };
		int* output = new int[size];

		for (int i = 0; i < size; i++) { // grouped the numbers according to their digits
			counter[arr[i] / power % 10]++;
		}

		for (int i = 1; i < 10; i++) {  
			counter[i] = counter[i] + counter[i - 1];
		}

		for (int i = size - 1; i >= 0; i--) { // sorting the numbers according to their digits
			output[counter[arr[i] / power % 10] - 1] = arr[i];
			counter[arr[i] / power % 10]--;
		}	

		for (int i = 0; i < size; i++) {
			arr[i] = output[i];
		}
		delete[] output;
	}	
}



//------IMPLEMENTATIONS FOR HELPER FUNCTIONS-------
void mergeSortHelper(int* arr, const int first, const int last, int& compCount, int& moveCount) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSortHelper(arr, first, mid, compCount, moveCount),
			mergeSortHelper(arr, mid + 1, last, compCount, moveCount);
		merge(arr, first, mid, last, compCount, moveCount);
	}
}

void quickSortHelper(int* arr, const int first, const int last, int& compCount, int& moveCount) {
	int pivotIndex;
	if (first <= last) {
		partition(arr, first, last, pivotIndex, compCount, moveCount);
		quickSortHelper(arr, first, pivotIndex - 1, compCount, moveCount);
		quickSortHelper(arr, pivotIndex + 1, last, compCount, moveCount);
	}
}
void swap(int& a, int& b, int& moveCount) {
	int temp = a;
	moveCount++;
	a = b;
	moveCount++;
	b = temp;
	moveCount++;
}

//auxiliary method for selection sort
int indexOfLargest(int* arr, int size, int& compCount, int& moveCount) {
	int max = -1000000;
	int result = 0;
	//iterating over the array to find max element from along the unsorted elements
	for (int i = 0; i < size; i++) {
		compCount++;
		if (arr[i] > max) {
			max = arr[i];
			result = i;
			moveCount++;
		}
	}
	return result;
}

//auxiliary method for merge sort
void merge(int* arr, const int first, int mid, const int last, int& compCount, int& moveCount) {
	//variables
	int* tempArr = new int [last + 1]; //temporary array with same size with the arr
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;
	int curIndex = first;

	for (; first1 <= last1 && first2 <= last2; curIndex++) {
		compCount++;
		if (arr[first1] < arr[first2]) {
			moveCount++;
			tempArr[curIndex] = arr[first1++];
		}
		else {
			moveCount++;
			tempArr[curIndex] = arr[first2++];
		}
	}

	// put remain parts from the first half of the array
	for (; first1 <= last1; curIndex++, first1++) {
		moveCount++;
		tempArr[curIndex] = arr[first1];
	}

	// put remain parts from the second half of the array
	for (; first2 <= last2; curIndex++, first2++) {
		moveCount++;
		tempArr[curIndex] = arr[first2];
	}

	//get sorted values from the tempArr
	for (int i = first; i < last + 1; i++) {
		moveCount++;
		arr[i] = tempArr[i];
	}
	// delete the tempArr from the heap
	delete[] tempArr;
}

//auxiliary method for quick sort
void partition(int* arr, const int first, const int last, int& pivotIndex, int& compCount, int& moveCount) {
	int lastS1 = first;
	int firstUnknown = first + 1;
	for (; firstUnknown <= last; firstUnknown++) {
		//cout << "bu mu" << endl;
		compCount++;
		if (arr[first] > arr[firstUnknown]) { // firstUnknown belongs to S1
			lastS1++;
			swap(arr[lastS1], arr[firstUnknown], moveCount);
		}// else it belongs to S2
	}

	swap(arr[first], arr[lastS1], moveCount); // put pivot to its position
	pivotIndex = lastS1;
}

//auxiliary method for radix sort
int getMax(int* arr, const int size) {
	int max = -1000000; // initial negative number to find maximum number in the array
	for (int i = 0; i < size; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

//------IMPLEMENTATIONS FOR AUXILIARY ASSIGNMENT FUNCTIONS------
// a method to display the array
void displayArray(const int* arr, const int size) {
	cout << "{ ";
	for (int i = 0; i < size - 1; i++) {
		cout << arr[i] << ", ";
	}
	if (size > 0) {
		cout << arr[size - 1];
	}
	cout << " }";
}

// a mothod to create 4 random arrays
void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size) {
	srand(time(0));
	for (int i = 0; i < size; i++) {
		arr1[i] = rand();
	}

	for (int i = 0; i < size; i++) {
		arr2[i] = rand();
	}

	for (int i = 0; i < size; i++) {
		arr3[i] = rand();
	}

	for (int i = 0; i < size; i++) {
		arr4[i] = rand();
	}
}

// a method to create 4 arrays in ascending order
void createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size) {
	srand(time(0));
	arr1[0] = rand();
	arr2[0] = rand();
	arr3[0] = rand();
	arr4[0] = rand();
	for (int i = 1; i < size; i++) {
		arr1[i] = arr1[i - 1] + rand();
	}

	for (int i = 1; i < size; i++) {
		arr2[i] = arr2[i - 1] + rand();
	}

	for (int i = 1; i < size; i++) {
		arr3[i] = arr3[i - 1] + rand();
	}

	for (int i = 1; i < size; i++) {
		arr4[i] = arr4[i - 1] + rand();
	}
}

// a method to create 4 arrays in descending order
void createDescendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size) {
	srand(time(0));
	arr1[size - 1] = rand();
	arr2[size - 1] = rand();
	arr3[size - 1] = rand();
	arr4[size - 1] = rand();
	for (int i = size-2; i >= 0; i--) {
		arr1[i] = arr1[i + 1] + rand();
	}

	for (int i = size - 2; i >= 0; i--) {
		arr2[i] = arr2[i + 1] + rand();
	}

	for (int i = size - 2; i >= 0; i--) {
		arr3[i] = arr3[i + 1] + rand();
	}

	for (int i = size - 2; i >= 0; i--) {
		arr4[i] = arr4[i + 1] + rand();
	}
}

void performanceAnalysis() {
	int compCount = 0;
	int moveCount = 0;
	double duration = 0;
	clock_t startTime;
	int** array6000 = createArrays(6000);
	int** array10000 = createArrays(10000);
	int** array14000 = createArrays(14000);
	int** array18000 = createArrays(18000);
	int** array22000 = createArrays(22000);
	int** array26000 = createArrays(26000);
	int** array30000 = createArrays(30000);

	printAlgorithmAnalysis("Selection Sort", array6000, array10000, array14000, array18000, array22000, array26000, array30000, compCount, moveCount);
	compCount = 0;
	moveCount = 0;
	printAlgorithmAnalysis("Merge Sort", array6000, array10000, array14000, array18000, array22000, array26000, array30000, compCount, moveCount);
	compCount = 0;
	moveCount = 0;
	printAlgorithmAnalysis("Quick Sort", array6000, array10000, array14000, array18000, array22000, array26000, array30000, compCount, moveCount);
	compCount = 0;
	moveCount = 0;
	printAlgorithmAnalysis("Radix Sort", array6000, array10000, array14000, array18000, array22000, array26000, array30000, compCount, moveCount);

	//deallocate the arrays
	for (int i = 0; i < 12; i++) {
		delete[] array6000[i]; delete[] array10000[i]; delete[] array14000[i]; delete[] array18000[i];
		delete[] array22000[i]; delete[] array26000[i]; delete[] array30000[i];
	}
	delete[] array6000;
	delete[] array10000;
	delete[] array14000;
	delete[] array18000;
	delete[] array22000;
	delete[] array26000;
	delete[] array30000;
}

// a method that creates all 3 types arrays for all soritng algorithms with specified size
int** createArrays(int const size) {
	int* arrSelRand = new int[size];
	int* arrSelAsc = new int[size];
	int* arrSelDes = new int[size];

	int* arrMergeRand = new int[size];
	int* arrMergeAsc = new int[size];
	int* arrMergeDes = new int[size];

	int* arrQuickRand = new int[size];
	int* arrQuickAsc = new int[size];
	int* arrQuickDes = new int[size];

	int* arrRadixRand = new int[size];
	int* arrRadixAsc = new int[size];
	int* arrRadixDes = new int[size];
	createRandomArrays(arrSelRand, arrMergeRand, arrQuickRand, arrRadixRand, size);
	createAscendingArrays(arrSelAsc, arrMergeAsc, arrQuickAsc, arrRadixAsc, size);
	createDescendingArrays(arrSelDes, arrMergeDes, arrQuickDes, arrRadixDes, size);
	int** result = new int*[12];
	result[0] = arrSelRand;
	result[1] = arrSelAsc;
	result[2] = arrSelDes;
	result[3] = arrMergeRand;
	result[4] = arrMergeAsc;
	result[5] = arrMergeDes;
	result[6] = arrQuickRand;
	result[7] = arrQuickAsc;
	result[8] = arrQuickDes;
	result[9] = arrRadixRand;
	result[10] = arrRadixAsc;
	result[11] = arrRadixDes;
	return result;
}

void printArrayAnalysis(string algorithm, int* arr, const int size, int& compCount, int& moveCount) {
	double duration = 0;
	clock_t startTime = clock();
	if (algorithm == "Selection Sort") {
		startTime = clock();
		selectionSort(arr, size, compCount, moveCount);
		duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
		cout << size << "                      " << duration << " ms           " << compCount << "           " << moveCount << endl;
		duration = 0;
	}
	else if (algorithm == "Merge Sort") {
		startTime = clock();
		mergeSort(arr, size, compCount, moveCount);
		duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
		cout << size << "                      " << duration << " ms           " << compCount << "           " << moveCount << endl;
		duration = 0;
	}
	else if (algorithm == "Quick Sort") {
		startTime = clock();
		quickSort(arr, size, compCount, moveCount);
		duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
		cout << size << "                      " << duration << " ms           " << compCount << "           " << moveCount << endl;
		duration = 0;
	}
	else if (algorithm == "Radix Sort") {
		startTime = clock();
		radixSort(arr, size);
		duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
		cout << size << "                      " << duration << " ms " << endl;
		duration = 0;
	}
}

//prints all kind of possible arrays for that agorithm
void printAlgorithmAnalysis(string algorithm, int** arr6000, int** arr10000, int** arr14000, int** arr18000, int** arr22000, int** arr26000, int** arr30000, int& compCount, int& moveCount) {
	int rand, asc, des;
	if (algorithm == "Selection Sort") {
		rand = 0; asc = 1; des = 2;
	}
	else if (algorithm == "Merge Sort") {
		rand = 3; asc = 4; des = 5;
	}
	else if (algorithm == "Quick Sort") {
		rand = 6; asc = 7; des = 8;
	}
	else if (algorithm == "Radix Sort") {
		rand = 9; asc = 10; des = 11;
	}
	if (algorithm != "Radix Sort") {
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "Analysis of " << algorithm << " with random arrays." << endl;
		cout << "Array Size            Elapsed time            compCount            moveCount" << endl;
		printArrayAnalysis(algorithm, arr6000[rand], 6000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr10000[rand], 10000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr14000[rand], 14000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr18000[rand], 18000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr22000[rand], 22000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr26000[rand], 26000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr30000[rand], 30000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "Analysis of " << algorithm << " with ascending arrays." << endl;
		cout << "Array Size            Elapsed time            compCount            moveCount" << endl;
		printArrayAnalysis(algorithm, arr6000[asc], 6000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr10000[asc], 10000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr14000[asc], 14000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr18000[asc], 18000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr22000[asc], 22000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr26000[asc], 26000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr30000[asc], 30000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "Analysis of " << algorithm << " with descending arrays." << endl;
		cout << "Array Size            Elapsed time            compCount            moveCount" << endl;
		printArrayAnalysis(algorithm, arr6000[des], 6000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr10000[des], 10000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr14000[des], 14000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr18000[des], 18000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr22000[des], 22000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr26000[des], 26000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr30000[des], 30000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
	}
	else { // for radix sort
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "Analysis of " << algorithm << " with random arrays." << endl;
		cout << "Array Size            Elapsed time " << endl;
		printArrayAnalysis(algorithm, arr6000[rand], 6000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr10000[rand], 10000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr14000[rand], 14000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr18000[rand], 18000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr22000[rand], 22000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr26000[rand], 26000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr30000[rand], 30000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		/*
		cout << "Analysis of " << algorithm << " with ascending arrays." << endl;
		cout << "Array Size            Elapsed time " << endl;
		printArrayAnalysis(algorithm, arr6000[asc], 6000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr10000[asc], 10000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr14000[asc], 14000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr18000[asc], 18000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr22000[asc], 22000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr26000[asc], 26000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr30000[asc], 30000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "Analysis of " << algorithm << " with descending arrays." << endl;
		cout << "Array Size            Elapsed time " << endl;
		printArrayAnalysis(algorithm, arr6000[des], 6000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr10000[des], 10000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr14000[des], 14000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr18000[des], 18000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr22000[des], 22000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr26000[des], 26000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		printArrayAnalysis(algorithm, arr30000[des], 30000, compCount, moveCount);
		compCount = 0;
		moveCount = 0;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		*/
	}
}