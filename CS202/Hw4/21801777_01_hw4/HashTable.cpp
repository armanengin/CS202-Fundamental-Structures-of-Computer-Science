#include <iostream>
#include "HashTable.h"

/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Arman Engin Sucu
* ID: 21801777
* Section : 1
* Assignment : 4
* Description : Source file for the hash table(main reason for implementing hash table is to create graph easily)
**/

//CONSTRUCTORS & DESTRUCTORS
HashTable::HashTable() {
	hashTable = new Entry* [CAPACITY]; //initializing all hash table with new Entry pointers
	for (int i = 0; i < CAPACITY; i++) {
		hashTable[i] = NULL;// all initialized to NULL
	}
}

HashTable::~HashTable() {
	for (int i = 0; i < CAPACITY; i++) {
		if (hashTable[i] != NULL) {
			Entry* entry = hashTable[i];
			Entry* temp;
			while (entry != NULL) {
				temp = entry->node;
				entry->node = NULL; //safety
				delete entry;
				entry = temp;
			}
		}
	}
	delete[] hashTable;
}

//METHODS
int HashTable::hash(const string& key, const int capacity) const{
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		hashVal = hashVal * 37 + key[i];
	}
	hashVal %= capacity;
	if (hashVal < 0) {
		hashVal += capacity;
	}
	return hashVal;
}

bool HashTable::add(const string& searchKey, const int& newItem) const{
	int hashIndex = hash(searchKey, CAPACITY);
	if (hashTable[hashIndex] == NULL) {//if the hash index is empty
		hashTable[hashIndex] = new Entry(searchKey, newItem);
	}
	else {//if the hash index is already used
		Entry* newEntry = new Entry(searchKey, newItem);
		newEntry->node = hashTable[hashIndex];
		hashTable[hashIndex] = newEntry;
	}
	return true;
}

int HashTable::getItem(const string& searchKey) const{
	int hashIndex = hash(searchKey, CAPACITY);
	Entry* entry = hashTable[hashIndex];
	if (entry == NULL) {
		return -1; //-1 for not found
	}
	while (entry != NULL) {
		if (entry->key == searchKey) {//if the item is found return it
			return entry->item;
		}
		else {//else look up the other entry with same hash value
			entry = entry->node;
		}
	}
	return -1;//the item is not found
}