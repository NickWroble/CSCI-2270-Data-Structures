// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash value
unsigned int HashTable::hashFunction(int key){
    return (key % tableSize);
}

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key){
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //TODO: Search the list at that specific index and return the node if found
    node *temp = table[index];

    while(temp && temp->key != key)
        temp = temp->next;
    if(temp)
        if(temp->key == key)
            return temp;
    return nullptr;
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
    if(!searchItem(key)){
        // TODO :
        // Use the hash function on the key to get the index/slot,
        // create a new node with the key and insert it in this slot's list
        node *temp = table[hashFunction(key)];
        if(temp){ //if the current hash index is not empty
            while (temp->next) //go to the end of the linked list
                temp = temp->next;
            temp->next = createNode(key, nullptr); //set the end of the LL to the new data
        }
        else //if the current hash index is not empty
            table[hashFunction(key)] = createNode(key, nullptr);
        return true;
    }
    cout<<"duplicate entry: "<<key<<endl;
    return false;
}

//TODO Complete this function
// function to display hash table
void HashTable::printTable(){
    node *temp;
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        temp = table[i];
        while(temp){
            cout << temp->key << " ";
            temp = temp->next;
        }
        cout << endl;
    }
 }
