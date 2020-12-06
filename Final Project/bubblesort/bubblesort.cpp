#include "bubblesort.hpp"


BubbleSort::BubbleSort(int size){ // Constructor
    array           = new int[size];
    numOfElements   = 0;
    for(int i = 0; i < size; i++) // -1 is used as a null entry
        array[i] = -1;
}

void BubbleSort::insert(int key){ //inserts the key at the end of the array
    array[numOfElements] = key;
    numOfElements++;
}

int BubbleSort::search(int key){ //searches for the key by going through the array starting at 
// index 0. returns the index of the key or -1 if the value was not found. 
    for(int i = 0; i < numOfElements; i++)
        if(array[i] == key)
            return i;
    return -1;
}

void BubbleSort::display(int a, int b){ //displays the array of values from index a to index b
    if(a < 0 || a > b || b > numOfElements)
        cout << "Bad display indicies. \n";
    else
        for(int i = a; i < b; i++)
            cout << array[i] << endl;
}

void BubbleSort::sort(){ //sort the array
    int temp;
    for (int i = 0; i < numOfElements - 1; i++)
        for (int j = 0; j < numOfElements - i - 1; j++)  
            if (array[j] > array[j + 1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j + 1] = temp;
            } 
}