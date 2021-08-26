#include <iostream>
#include "BinaryNode.h"

/*
* Title: Binary Search Trees
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 2
* Description: source file of the BinaryNode class
*/

//CONSTRUCTORS
BinaryNode::BinaryNode() { //default constructor
	item = 0;
	leftChildPtr = NULL;
	rightChildPtr = NULL;
}
BinaryNode::BinaryNode(const int& item) {
	this->item = item;
	leftChildPtr = NULL;
	rightChildPtr = NULL;
}
BinaryNode::BinaryNode(const int& item, BinaryNode* leftChildPtr, BinaryNode* rightChildPtr) {
	this->item = item;
	this->leftChildPtr = leftChildPtr;
	this->rightChildPtr = rightChildPtr;
}

//METHODS
void BinaryNode::setItem(const int& anItem) {
	item = anItem;
}
int BinaryNode::getItem() const{
	return item;
}
bool BinaryNode::isLeaf() const{
	if (leftChildPtr == NULL && rightChildPtr == NULL) {
		return true;
	}
	return false;
}
BinaryNode* BinaryNode::getLeftChildPtr() const{
	return leftChildPtr;
}
BinaryNode* BinaryNode::getRightChildPtr() const {
	return rightChildPtr;
}
void BinaryNode::setLeftChildPtr(BinaryNode* leftPtr) {
	leftChildPtr = leftPtr;
}
void BinaryNode::setRightChildPtr(BinaryNode* rightPtr) {
	rightChildPtr = rightPtr;
}