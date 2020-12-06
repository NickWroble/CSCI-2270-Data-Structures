#include "dll.hpp"


DLL::DLL(){ //constructor for the DLL
    head = nullptr;
}

bool DLL::isEmpty(){ // checks if the DLL is emtpy by seeing if the head is null
    if(!head)
        return true;
    return false;
}

void DLL::display(void){ //printz the DLL by crawling from the head
    Node *temp = head;
    while (temp){
        cout << temp->key << " -> ";
        temp = temp->next;
    }
    cout << "END\n";
}

Node *DLL::search(int key){ //searches for a node in the DLL, returns null if the node was not found
    if(isEmpty()) //first check if the DLL is empty
        return nullptr;
    Node *temp = head; 
    while(temp) //crawl the DLL starting at the head of  the linked list
        if(temp->key == key)
            return temp;
        else
            temp = temp->next;
    return nullptr;
}

bool DLL::insert(int key){ //Inserts a link into the DLL
    Node *temp = new Node(); //Allocate memory for a new node
    temp->key = key; //Initialize it
    if(isEmpty()) //if the list is empty, set the head of the list to the new node
        head = temp;
    else{ //otherwise put the node at the front of the list. 
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
    return true;
}
