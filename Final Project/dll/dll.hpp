#ifndef DLL_HPP
#define DLL_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node{
    int key;
    Node *next;
    Node *prev;
};

class DLL{
    private:
        Node *head;
    public: 
        DLL();
        bool isEmpty();
        bool insert(int key);
        Node *search(int key);
        void display(void);
};


#endif