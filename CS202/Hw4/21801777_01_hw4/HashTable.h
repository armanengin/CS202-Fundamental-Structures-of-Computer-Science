#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
using namespace std;

/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Arman Engin Sucu
* ID: 21801777
* Section : 1
* Assignment : 4
* Description : Header file for the hash table(main reason for implementing hash table is to create graph easily)
**/

class HashTable {//Separete chaining hash table
public:
	//CONSTRUCTORS & DESTRUCTORS
	HashTable();
	~HashTable();

	//STRUCT
	struct Entry {
		Entry* node;
		int item;
		string key;

		Entry() {
			node = NULL;
			item = 0;
			key = "";
		}
		Entry(string key, int item) {
			this->key = key;
			this->item = item;
			node = NULL;
		}
	};

	//METHODS
	int hash(const string& key, const int CAPACITY) const;
	bool add(const string& searchKey, const int& newItem) const;
	int getItem(const string& searchKey) const;

private:
	//PROPERTIES
	const int CAPACITY = 1000; //Capacity of the hashTable
	Entry** hashTable;
};
#endif // !HASHTABLE_H