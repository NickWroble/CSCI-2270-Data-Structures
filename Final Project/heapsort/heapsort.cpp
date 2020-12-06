#include "heapsort.hpp"


heapSort::heapSort(int size){ //constructor
    data = new int[size];
    heapSize = 0;
}

void heapSort::insert(int key){ //inserts element at the end of the array
    data[heapSize] = key; 
    heapSize++; 
}

int heapSort::search(int key){ //searches for a key in the array, returns the index of the key
    for(int i = 0; i < heapSize; i++)
        if(data[i] == key)
            return i;
    return -1;
}

void heapSort::display(int a, int b){ //prints values of the array from index a to b
//the for loop is a bit messy since a max heap was used
    if(a > b || b > heapSize - 1 || a < 0)
        return;
    for(int i = (heapSize - a); i > heapSize - b; i--){
        cout << data[i] << endl;
    }
}

void heapifyDriver(int array[], int n, int i){
    int smallest = i; // Initialize smalles as root 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 
  
    // If left child is smaller than root 
    if (l < n && array[l] < array[smallest]) 
        smallest = l; 
  
    // If right child is smaller than smallest so far 
    if (r < n && array[r] < array[smallest]) 
        smallest = r; 
  
    // If smallest is not root 
    if (smallest != i) { 
        swap(array[i], array[smallest]); 
  
        // Recursively heapify the affected sub-tree 
        heapifyDriver(array, n, smallest); 
    } 
}

void heapSort::heapify(){
    // Build heap (rearrange array) 
    for (int i = heapSize / 2 - 1; i >= 0; i--) 
        heapifyDriver(data, heapSize, i); 
  
    // One by one extract an element from heap 
    for (int i = heapSize - 1; i >= 0; i--) { 
        // Move current root to end 
        swap(data[0], data[i]); 
  
        // call max heapify on the reduced heap 
        heapifyDriver(data, i, 0); 
    }
}