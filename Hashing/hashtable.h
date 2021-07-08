#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>

using namespace std;
namespace Hash {
	class HashTable {
	public:
		HashTable(int size);		// Konstruktor
		~HashTable();				// Destruktor
		int insert(int item);		// fügt ein Element der Hashtabelle hinzu
		int at(int i);				// Liefert das i-te Element der Hashtabelle zurück
		int getCollisionCount();    // Liefert die Anzahl der Kollisionen zurück
		int getSize();				// Liefert die Größe der Hashtabelle zurück
		int getElements();			// Liefert die Anzahl der Elemente der Hashtabelle zurück
	private:
		int size;					// Größe der HashTable
		int elements;				// Anz. d. Elemente in HashTable
		int collisionCount;			// Anz. d. Kollisionen beim Einfügen
		vector<int>* hashTable;		// HashTable
		int hashValue(int item);	// Hashindex berechnen
	};
}

#endif 