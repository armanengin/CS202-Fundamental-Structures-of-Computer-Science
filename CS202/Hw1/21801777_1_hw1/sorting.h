#ifndef sorting_h
#define sorting_h
#include <iostream>
using namespace std;

/*
* Title: Sorting and Algorithm Efficiency
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 1
* Description: description of your code
*/

//assignment functions
void selectionSort(int* arr, const int size, int& compCount, int& moveCount);
void mergeSort(int* arr, const int size, int& compCount, int& moveCount);
void quickSort(int* arr, const int size, int& compCount, int& moveCount);
void radixSort(int* arr, const int size);

//auxiliary assignment functions
void mergeSortHelper(int* arr, const int first, const int last, int& compCount, int& moveCount);
void quickSortHelper(int* arr, const int first, const int last, int& compCount, int& moveCount);
void displayArray(const int* arr, const int size);
void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size);
void createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size);
void createDescendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size);

//helper functions
void swap(int& a, int& b, int& moveCount);
int indexOfLargest(int*arr, int size, int& compCount, int& moveCount);
void merge(int* arr, const int first, int mid, const int last, int& compCount, int& moveCount);
void partition(int* arr, const int first, const int last, int& pivotIndex, int& compCount, int& moveCount);
int getMax(int* arr, const int size);

//analysis function
void performanceAnalysis();

//helpers for analysis function
int** createArrays(int const size);
void printArrayAnalysis(string algorithm, int* arr, const int size, int& compCount, int& moveCount);
void printAlgorithmAnalysis(string algorithm, int** arr6000, int** arr10000, int** arr14000, int** arr18000, int** arr22000, int** arr26000, int** arr30000, int& compCount, int& moveCount);
#endif
