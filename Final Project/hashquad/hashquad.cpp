#include "hashquad.hpp"


HashTable::HashTable(int bsize){  // Constructor
    tableSize     = bsize;
    numOfcolision = 0;
    table         = new int[bsize];
    for(int i = 0; i < tableSize; i++) // -1 is used as a null entry
        table[i] = -1;
}

// inserts a key into hash table returns false if the key was not able to be inserted
bool HashTable::insert(int key){ 
    int hash = hashFunction(key); //get hash of the key
    int originalHash = hash; //for use in quadratic probing 
    for(int i = 0; i < tableSize; i++){ //perform quadratic probing until the value has not been set.
        if(table[hash] == -1){ //if a value has not been inserted, insert the new key
            table[hash] = key;
            return true;
        }
        numOfcolision++;
        hash = (originalHash + (i * i)) % tableSize;
    }
    cout << "Unable to insert: " << key << endl;
    return false;
}

unsigned int HashTable::hashFunction(int key){ //modulo hash function of tableSize
    return key % tableSize;
}


void HashTable::printTable(int a, int b){ //prints the hash table from index a to index b
    if(a > b || a < 0 || b > tableSize - 1)
        cout << "Invalid print indicies." << endl;
    else
        for(int i = a; i < b; i++){
            cout << i;
            cout << " || ";
            cout << table[i] << endl;
        }
}

int HashTable::getNumOfCollision(){ //I wonder what this does
    return numOfcolision;
}

int HashTable::search(int key){ //Search for a key in the hash table
    int hash =  hashFunction(key); //get the hash of the key
    int originalHash = hash;
    for(int i = 0; i < tableSize; i++){ //perform quadratic probing until the key is found
        hash = (originalHash + (i * i)) % tableSize;
        if(table[hash] == key)
            return hash;
    }
    //cout << "null" << endl;
    cout << "" << endl;
    return -1; //if the value was not found in the hash table
}
