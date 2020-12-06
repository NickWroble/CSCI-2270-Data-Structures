/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
//runs in code runner
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    CUBuilding *current = new CUBuilding(); //create new struct instance called current
    current->name = buildingName; //set them vars
    current->totalRoom = numOfroom;
    if(previous == NULL){ //check if first in list
        current->next = head;
        head = current;
        cout << "adding: " << buildingName << " (HEAD)" << endl;
    } else{ //else add it to the list after previous
        current->next = previous->next;
        previous->next = current;
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
    }
}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup(){
    string  buildingNames[]         = {"FLMG", "DLC", "ECOT", "CASE", "AERO", "RGNT"};
    int     buildingRoomNumbers []  = {2, 10, 6, 5, 4, 9}; 
    addBuildingInfo(NULL, buildingNames[0], buildingRoomNumbers[0]); //init the head 
    for(int i = 0; i < 5; i++) CUBuildingNetwork::addBuildingInfo(searchForBuilding(buildingNames[i]), buildingNames[i + 1], buildingRoomNumbers[i + 1]); //init the rest of the rooms
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
//runs in code runner
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName){
    if(isEmpty()) return NULL;
    CUBuilding * current;
    current = CUBuildingNetwork::head;
    while (current != NULL) 
        if (current->name == buildingName) 
            return current;
        else current = current->next;
    return NULL;
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver) {
    if(isEmpty()){
        cout << "Empty List" << endl;
        return;
    }
    if(searchForBuilding(receiver) == NULL){
        cout << "Building not found" << endl;
        return;
    }
    CUBuilding * current = head;
    while(current != NULL && current->name != receiver){
        current->message =  "available room at " + current->name + " is " + to_string(current->totalRoom);
        current->numberMessages++;
        cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << endl;
        current = current->next;
    }
    current->numberMessages++;
    current->message =  "available room at " + current->name + " is " + to_string(current->totalRoom);
    cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << endl;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    cout << "== CURRENT PATH ==" << endl;
    if(isEmpty()){
        cout << "nothing in path" << endl;
        cout << "===" << endl;
        return;
    }
    CUBuilding * current = head;
    while(current != NULL){
        cout << current->name << "(" << current->totalRoom << ")" << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
    cout << "===" << endl;
}

//runs in code runner
bool append(string * &str_arr, string s, int &numEntries, int &arraySize){
    if(numEntries < arraySize){
        str_arr[numEntries] = s;
        numEntries++;
        return false;
    }
    arraySize *=2;
    string * tempArray = new string[arraySize];
    for(int i=0;i<numEntries;i++) tempArray[i] = str_arr[i];
    tempArray[numEntries] = s;
    str_arr = tempArray;
    numEntries++;
    return true;
}
