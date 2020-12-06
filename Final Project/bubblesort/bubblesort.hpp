#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <bits/stdc++.h> 

using namespace std;
using namespace chrono;

class BubbleSort{
    int arraySize;
    int *array;
    int numOfElements;

    public:
        BubbleSort(int size);
        void insert(int key);
        int search(int key);
        void display(int a, int b);
        void sort();
};