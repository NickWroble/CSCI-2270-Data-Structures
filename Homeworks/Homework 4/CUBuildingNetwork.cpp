/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of Building structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
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
 * Purpose: Add a new building to the network between the building *previous and the building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    // if we are passed an empty list, just create a new head node, and return

    if (head == NULL)
    {
        cout << "adding: " << buildingName << " (HEAD)" << endl;
        head = new CUBuilding;
        head->name = buildingName;
        head->numberMessages = 0;
        head->totalRoom = numOfroom;

        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        cout << "adding: " <<buildingName<< " (HEAD)" << endl;
        CUBuilding *c = new CUBuilding;
        c->name = buildingName;
        c->numberMessages = 0;
        c->next = head;
        c->totalRoom = numOfroom;

        head = c;
    }else{
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
        CUBuilding *newBuilding = new CUBuilding;
        newBuilding->name = buildingName;
        newBuilding->numberMessages = 0;
        newBuilding->next = previous->next;
        newBuilding->totalRoom = numOfroom;

        previous->next = newBuilding;
    }
}

/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    int num_buildings = 6;
    string buildings[] = {"FLMG", "DLC", "ECOT", "CASE", "AERO", "RGNT"};
    int rooms[] = {2,10,6,5,4,9};
    head = NULL;
    CUBuilding* prev = NULL;
    for(int i = 0; i < num_buildings; i++)
    {
        addBuildingInfo(prev, buildings[i],rooms[i]);
        prev = searchForBuilding(buildings[i]);
    }
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // Search until the head is NULL, or we find the building
    CUBuilding* ptr = head;
    while (ptr != NULL && ptr->name != buildingName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    CUBuilding* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr != NULL)
        {
            cout << ptr->name << "(" << ptr->totalRoom << ")" <<" -> ";
            ptr = ptr->next;
        }
        //cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
  }

/*
 * Purpose: delete the building in the network with the specified name.
 * @param buildingName name of the building to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) {
    //TODO: Complete this function
    if(head == NULL) return; //check if empty list
    if(searchForBuilding(buildingName) == NULL){ 
        cout << "Building does not exist." << endl;
        return;
    }
    CUBuilding * pres;
    if(head->name == buildingName){ //if head is buildingName     
        pres = head->next; //go to next node
        delete head; 
        head = pres; //make pres the currenet head node
        return;
    }
    pres = head->next;
    CUBuilding * prev = head;
    while(pres->next != NULL && pres->name != buildingName){ //searches for building name or until list is at end
        pres = pres->next;
        prev = prev->next;
    }
    if(pres->name == buildingName) { //if while loop broke because of second condition
        prev->next = pres->next;
        delete pres;
        return;
    }
}

/*
* Purpose: Creates a loop from last node to the building specified.
* @param buildingName name of the building to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) {
    //TODO: Complete this function
    if(head == NULL){
        cout <<  "nothing in path" << endl;
        return NULL;
    }
    CUBuilding * tailPtr = head;
    while(tailPtr->next != NULL) tailPtr = tailPtr->next;
    if(searchForBuilding(buildingName) != NULL) tailPtr->next = searchForBuilding(buildingName); //create loop if building is in list
    return tailPtr;
}

/*
 * Purpose: deletes all buildings in the network starting at the head building.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork(){
    CUBuilding* current = head;  
    CUBuilding* next;  
  
    while (current != NULL)  
    {  
        next = current->next;  
        cout << "deleting: " << current->name << endl;
        free(current);  
        current = next;  
    } 
    head = NULL;
    
    cout << "Deleted network" << endl;
}

/*
 * Purpose: to detect loop in the linkedlist
 * @return: true if loop is detected.
 */
bool CUBuildingNetwork::detectLoop() {
    //based on https://stackoverflow.com/questions/2663115/how-to-detect-a-loop-in-a-linked-list
    if(head == NULL)
        return false;
    CUBuilding *slow = head;
    CUBuilding *fast = head;
    while(1){
        slow = slow->next;
        if(fast->next != NULL)
            fast = fast->next->next;
        else
            return false;
        if(slow == NULL || fast == NULL)
            return false;
        if(slow == fast)
            return true;
    }
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk at the end of the List
 * @param: start index, end index
 * @return: none
 */
void CUBuildingNetwork:: readjustNetwork(int start_index, int end_index){
    if(head == NULL){ //check if empty
        cout << "Linked List is Empty" << endl;
        return;
    }
    int linkedListLength = 0;
    CUBuilding * tailPtr = head;
    while(tailPtr->next != NULL){
        tailPtr = tailPtr->next;
        linkedListLength++;
    }
    if(end_index > linkedListLength){
        cout << "Invalid end index" << endl;
        return;
    }
    if(start_index >= linkedListLength || start_index < 0){
        cout << "Invalid start index" << endl;
        return;
    }
    if(start_index > end_index){
        cout << "Invalid indices" << endl;
        return;
    }
    CUBuilding * prev1 = head;
    CUBuilding * prev2 = head;
    if(end_index == 1){ //If elements 0 and 1 are called
        prev2 = head->next;
        head = prev2->next;
        tailPtr->next = prev1;
        prev2->next = NULL;
        return;
    }
    for(int i = 0; i < start_index - 1; i++)
        prev1 = prev1->next;
    for(int i = 0; i < end_index - 1; i++)
        prev2 = prev2->next;
    CUBuilding * startNode = prev1->next;
    CUBuilding * endNode = prev2->next;
    prev1->next = endNode->next;
    tailPtr->next = startNode;
    endNode->next = NULL;
}