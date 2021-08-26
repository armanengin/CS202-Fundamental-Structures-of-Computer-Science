#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

/*
* Title: Binary Search Trees
* Author: Arman Engin Sucu
* ID: 21801777
* Section: 1
* Assignment: 2
* Description: source file of the BinarySearchTree class
*/

//CONSTRUCTORS
BinarySearchTree::BinarySearchTree() {
	root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
	deleteTree(root);
	root = NULL;
}

//MAIN METHODS
bool BinarySearchTree::isEmpty() {
	return root == NULL;
}

int BinarySearchTree::getHeight() {
	return getHeightHelper(root);
}

int BinarySearchTree::getNumberOfNodes() {
	return getNumberOfNodesHelper(root);
}

bool BinarySearchTree::add(const int newEntry) {
	return getAddHelper(root, newEntry);
}

bool BinarySearchTree::remove(const int anEntry) {
	return getRemoveHelper(root, anEntry);
}

bool BinarySearchTree::contains(const int anEntry) {
	return getContainsHelper(root, anEntry);
}

void BinarySearchTree::preorderTraverse() {
	preorder(root);
}

void BinarySearchTree::inorderTraverse() {
	inorder(root);
}

void BinarySearchTree::postorderTraverse() {
	postorder(root);
}

void BinarySearchTree::levelorderTraverse() {
	levelorder(root);
}

int BinarySearchTree::span(const int a, const int b) {
	int result = 0;
	if (root == NULL) {
		return 0;
	}
	else if (root->getItem() == a) {
		result++;
		result += findSmallerThan(root->getRightChildPtr(), b);
	}
	else if (root->getItem() == b) {
		result++;
		result += findBigerThan(root->getLeftChildPtr(), a);
	}
	else if (root->getItem() > a && root->getItem() < b) {
		result++;
		result += findBigerThan(root->getLeftChildPtr(), a);
		result += findSmallerThan(root->getRightChildPtr(), b);
	}
	return result;
}

void BinarySearchTree::mirror() {
	swap(root);
}

//AUXILIARY METHODS
int BinarySearchTree::getHeightHelper(BinaryNode* root) const {
	if (root == NULL) {
		return 0;
	}
	else{
		return 1 + max(getHeightHelper(root->getLeftChildPtr()), getHeightHelper(root->getRightChildPtr()));
	}
}

int BinarySearchTree::getNumberOfNodesHelper(BinaryNode* root) const {
	if (root == NULL) {
		return 0;
	}
	else {
		return 1 + getNumberOfNodesHelper(root->getLeftChildPtr()) + getNumberOfNodesHelper(root->getRightChildPtr());
	}
}

bool BinarySearchTree::getContainsHelper(BinaryNode* root, int anEntry) const{
	if (root == NULL)
		return false;
	if (root->getItem() == anEntry)
		return true;
	if(root->getItem() > anEntry)
		return getContainsHelper(root->getLeftChildPtr(), anEntry);
	if(root->getItem() < anEntry )
	return getContainsHelper(root->getRightChildPtr(), anEntry);
}

bool BinarySearchTree::getAddHelper(BinaryNode*& treePtr, int newEntry) {
	if (contains(newEntry)) {
		cout << "The item already exists." << endl;
			return false;
	}
		
	if (treePtr == NULL) { // method gets inside this method in only one case which is the root is NULL
		treePtr = new BinaryNode(newEntry);
		return true;
	}
	BinaryNode* leftPtr = treePtr->getLeftChildPtr();
	BinaryNode* rightPtr = treePtr->getRightChildPtr();

	if (treePtr->getItem() > newEntry) {
		if (leftPtr == NULL) {
			treePtr->setLeftChildPtr(new BinaryNode(newEntry));
			return true;
		}
		return getAddHelper(leftPtr, newEntry); // if letPtr is not NULL than go to method again
	}
	else if (treePtr->getItem() < newEntry) {// if rightPtr is not NULL than go to method again
		if(rightPtr == NULL){
			treePtr->setRightChildPtr(new BinaryNode(newEntry));
			return true;
		}
		return getAddHelper(rightPtr, newEntry);
	}
}

bool BinarySearchTree::getRemoveHelper(BinaryNode*& treePtr, int anEntry) {
	BinaryNode* leftPtr = treePtr->getLeftChildPtr();
	BinaryNode* rightPtr = treePtr->getRightChildPtr();
	if (treePtr == NULL) {
		cout << "There is no item! Delete Failed!!!" << endl;
		return false;
	}
	else if (treePtr->getItem() == anEntry) {
		deleteNode(treePtr);
		return true;
	}
	else if (treePtr->getItem() > anEntry) {
		bool result = (getRemoveHelper(leftPtr, anEntry));
		treePtr->setLeftChildPtr(leftPtr);
		return result;
	}
	else {
		bool result (getRemoveHelper(rightPtr, anEntry));
		treePtr->setRightChildPtr(rightPtr);
		return result;
	}
}
void BinarySearchTree::deleteNode(BinaryNode*& nodePtr) {
	int replacementItem;
	BinaryNode* delItem;
	BinaryNode* rightPtr = nodePtr->getRightChildPtr();

	if (nodePtr->isLeaf()) { //case for leaf
		delete nodePtr;
		nodePtr = NULL;
	}
	else if (nodePtr->getLeftChildPtr() == NULL) {// case for no left child
		delItem = nodePtr;
		nodePtr = nodePtr->getRightChildPtr();
		delItem->setRightChildPtr(NULL);
		delete delItem;
		delItem = NULL;
	}
	else if (nodePtr->getRightChildPtr() == NULL) { // case for no right child
		delItem = nodePtr;
		nodePtr = nodePtr->getLeftChildPtr();
		delItem->setLeftChildPtr(NULL);
		delete delItem;
		delItem = NULL;
	}
	else {// case for two children
		processLeftmost(rightPtr, replacementItem);
		nodePtr->setRightChildPtr(rightPtr);
		nodePtr->setItem(replacementItem);
	}
}
void BinarySearchTree::processLeftmost(BinaryNode*& nodePtr, int& replacementItem) {
	BinaryNode* leftPtr = nodePtr->getLeftChildPtr();
	BinaryNode* delPtr;
	if (nodePtr->getLeftChildPtr() == NULL) {
		delPtr = nodePtr;
		replacementItem = nodePtr->getItem();
		nodePtr = nodePtr->getRightChildPtr();
		delPtr->setRightChildPtr(NULL);
		delete delPtr;
	}
	else {
		processLeftmost(leftPtr, replacementItem);
		nodePtr->setLeftChildPtr(leftPtr);
	}
}

void BinarySearchTree::visit(BinaryNode* node) {
	cout << node->getItem()  << ", ";
}

void BinarySearchTree::preorder(BinaryNode* node) {
	if (node != NULL) {
		visit(node);
		preorder(node->getLeftChildPtr());
		preorder(node->getRightChildPtr());
	}
}

void BinarySearchTree::inorder(BinaryNode* node) {
	if (node != NULL) {
		inorder(node->getLeftChildPtr());
		visit(node);
		inorder(node->getRightChildPtr());
	}
}

void BinarySearchTree::postorder(BinaryNode* node) {
	if (node != NULL) {
		postorder(node->getLeftChildPtr());
		postorder(node->getRightChildPtr());
		visit(node);
	}
}

void BinarySearchTree::levelorder(BinaryNode* node) {
	int maxLevel = getHeightHelper(node);
	for (int level = 1; level <= maxLevel; level++) {
		printTheLevel(root, level);
	}
}

void BinarySearchTree::printTheLevel(BinaryNode* node, int level) {
	if (node != NULL) {
		if (level == 1) {
			visit(node);
		}
		else if (level > 1) {
			printTheLevel(node->getLeftChildPtr(), level - 1);
			printTheLevel(node->getRightChildPtr(), level - 1);
		}
	}
}

int BinarySearchTree::findBigerThan(BinaryNode* node, int a) {// finds the number of numbers that bigger than a or equal to a in the tree
	if (node == NULL) {
		return 0;
	}
	int result = 0;
	if (a == node->getItem()) {
		result++;
		result += findBigerThan(node->getRightChildPtr(), a);
	}
	else if(a < node->getItem()){
		result++;
		result += findBigerThan(node->getRightChildPtr(), a);
		result += findBigerThan(node->getLeftChildPtr(), a);
	}
	else if (a > node->getItem()) {
		result += findBigerThan(node->getRightChildPtr(), a);
	}
	return result;
}
int BinarySearchTree::findSmallerThan(BinaryNode* node, int b) {// finds the number of items that smaller than a or equal to a in the tree
	if (node == NULL) {
		return 0;
	}
	int result = 0;
	if (b == node->getItem()) {
		result++;
		result += findSmallerThan(node->getLeftChildPtr(), b);
	}
	else if (b > node->getItem()) {
		result++;
		result += findSmallerThan(node->getRightChildPtr(), b);
		result += findSmallerThan(node->getLeftChildPtr(), b);
	}
	else if (b < node->getItem()) {
		result += findSmallerThan(node->getLeftChildPtr(), b);
	}
	return result;
}

void BinarySearchTree::swap(BinaryNode* node) {
	if (node != NULL) {
		swap(node->getLeftChildPtr());
		swap(node->getRightChildPtr());
		BinaryNode* temp = node->getLeftChildPtr();
		node->setLeftChildPtr(node->getRightChildPtr());
		node->setRightChildPtr(temp);
	}
}

bool BinarySearchTree::deleteTree(BinaryNode* node) {
	if (node) {
		if (deleteTree(node->getLeftChildPtr())) {
			node->setLeftChildPtr(NULL);
		}
		if (deleteTree(node->getRightChildPtr())) {
			node->setRightChildPtr(NULL);
		}
		delete node;
		return true;
	}
	else
		return false;
}