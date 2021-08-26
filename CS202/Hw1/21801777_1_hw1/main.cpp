#include "sorting.h"

/*
* Title: Sorting and Algorithm Efficiency
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 1
* Description: main function tests sorting functions, first with small arrya then with the help of a function called performanceAnalysis()
*/

int main(int argc, char* argv[]) {

	int arrSelect[] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	int compCount = 0;
	int moveCount = 0;
	selectionSort(arrSelect, 16, compCount, moveCount);
	cout << "For selection sort number of key comparisons are " << compCount << " and number of data moves are " << moveCount << endl;
	displayArray(arrSelect, 16);
	cout << endl;
	cout << endl;

	int arrMerge[] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	compCount = 0;
	moveCount = 0;
	mergeSort(arrMerge, 16, compCount, moveCount);
	cout << "For merge sort number of key comparisons are " << compCount << " and number of data moves are " << moveCount << endl;
	displayArray(arrMerge, 16);
	cout << endl;
	cout << endl;

	int arrQuick[] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	compCount = 0;
	moveCount = 0;
	quickSort(arrQuick, 16, compCount, moveCount);
	cout << "For quick sort number of key comparisons are " << compCount << " and number of data moves are " << moveCount << endl;
	displayArray(arrQuick, 16);
	cout << endl;
	cout << endl;

	int arrRadix[] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	compCount = 0;
	moveCount = 0;
	radixSort(arrRadix, 16);
	cout << "Radix Sort" << endl;
	displayArray(arrRadix, 16);

	performanceAnalysis();



	/*
	int* a1 = new int[100];
	int* a2 = new int[100];
	int* a3 = new int[100];
	int* a4 = new int[100];
	createAscendingArrays(a1, a2, a3, a4, 100);
	int compCount;
	int moveCount;
	quickSort(a1, 0, 99, compCount, moveCount);
	*/
}