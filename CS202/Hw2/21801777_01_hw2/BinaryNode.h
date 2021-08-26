#ifndef BINARY_NODE_H
#define BINARY_NODE_H

/*
* Title: Binary Search Trees
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 2
* Description: header file of the BinaryNode Class
*/
class BinaryNode {

	//PROPERTIES
	private:
		int item;
		BinaryNode* leftChildPtr;
		BinaryNode* rightChildPtr;

	//CONSTRUCTORS
	public:
		BinaryNode();
		BinaryNode(const int& item);
		BinaryNode(const int& item, BinaryNode* rightChildPtr, BinaryNode* leftChildPtr);

	//METHODS
		void setItem(const int& anItem);
		int getItem() const;
		bool isLeaf() const;
		BinaryNode* getLeftChildPtr() const;
		BinaryNode* getRightChildPtr() const;
		void setLeftChildPtr(BinaryNode* leftPtr);
		void setRightChildPtr(BinaryNode* rightPtr);
};

#endif 
