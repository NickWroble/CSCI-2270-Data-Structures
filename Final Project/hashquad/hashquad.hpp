#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)
    // Pointer to an array containing buckets
    int *table;
    int numOfcolision = 0;
public:

    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insert(int key);

    // hash function to map values to key
    unsigned int hashFunction(int key);
    
    //Print from index a to index b 
    void printTable(int a, int b);
    int getNumOfCollision();

    int search(int key);

};