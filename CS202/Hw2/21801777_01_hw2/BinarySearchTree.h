#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "BinaryNode.h"
using namespace std;
/*
* Title: Binary Search Trees
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 2
* Description: header file of the BinarySearchTree class
*/

class BinarySearchTree{
	//PROPERTIES
private:
	BinaryNode* root;

	//CONSTRUCTIRS
public:
	BinarySearchTree(); //default constructor
	~BinarySearchTree(); //destructor

	//MAIN METHODS OF BST
	bool isEmpty();
	int getHeight();
	int getNumberOfNodes();
	bool add(const int newEntry);
	bool remove(const int anEntry);
	bool contains(const int anEntry);
	void preorderTraverse();
	void inorderTraverse();
	void postorderTraverse();
	void levelorderTraverse();
	int span(const int a, const int b);
	void mirror();

	//AUXILIARY METHODS
	int getHeightHelper(BinaryNode* root) const;
	int getNumberOfNodesHelper(BinaryNode* root) const;
	bool getContainsHelper(BinaryNode* root, int anEntry) const;
	bool getAddHelper(BinaryNode*& treePtr, int newEntry);
	bool getRemoveHelper(BinaryNode*& treePtr, int anEntry);
	void deleteNode(BinaryNode*& nodePtr);
	void processLeftmost(BinaryNode*& nodePtr, int& replacementItem);
	void visit(BinaryNode* node);
	void preorder(BinaryNode* node);
	void inorder(BinaryNode* node);
	void postorder(BinaryNode* node);
	void levelorder(BinaryNode* node);
	void printTheLevel(BinaryNode* node, int level);
	int findBigerThan(BinaryNode* node, int a); // finds the number of numbers that bigger than a in the tree
	int findSmallerThan(BinaryNode* node, int b);// finds the number of numbers that smaller than a in the tree
	void swap(BinaryNode* node); //a recursive helper method for mirror. 
	bool deleteTree(BinaryNode* node); // a recursive megthod to delete tree.
};
#endif // !BINARY_SEARCH_TREE_H