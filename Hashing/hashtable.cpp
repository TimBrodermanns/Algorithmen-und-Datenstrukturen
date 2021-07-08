#include "hashtable.h"
#include <iostream>

using namespace std;

namespace Hash {

	HashTable::HashTable(int size) {

		//*****************************
		// implement constructor here *
		//*****************************
		collisionCount = 0;
		elements = 0;
		hashTable = new vector<int>;
		hashTable->resize(size, -1);
		this->size = size;
	}

	HashTable::~HashTable()
	{
		//****************************
		// implement destructor here *
		//****************************
		delete hashTable;
	}

	int HashTable::hashValue(int item) {

		int index = -1; //dummy initializtation

		//******************************************
		// implement calculation of hashindex here *
		//******************************************

		int i = 0;

		while (hashTable->at(((item + i * i) % size)) != -1) {
			i++;
			collisionCount++;
		}

		index = ((item + i * i) % size);

		return index;

	}

	int HashTable::insert(int item) {

		//******************************************
		// implement insertion of new element here *
		//******************************************
		hashTable->at(hashValue(item)) = item;
		elements++;

		return 0; //dummy return
	}


	int HashTable::at(int i) {
		return hashTable->at(i);
	}

	int HashTable::getCollisionCount() {
		return this->collisionCount;
	}

	int HashTable::getSize() {
		return this->size;
	}

	int HashTable::getElements() {
		return this->elements;
	}
}
