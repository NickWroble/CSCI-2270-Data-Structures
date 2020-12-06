#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

class heapSort{
    private:
        int *data;
        int heapSize;

    public:
        heapSort(int size);
        void insert(int key);
        int search(int key);
        void display(int a, int b);
        void heapify();
};