#include "heapsort.hpp"

#define DOC_SIZE 10000

int main(int argc, char* argv[]){
    int testData[DOC_SIZE];

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cout << "File open error." << endl;
        return -1;
    }
    string line, dataString;
    int lineNumber = 0;
    while(getline(inputFile, line) && lineNumber < DOC_SIZE){
        istringstream myline(line);
        while(getline(myline, dataString, ',') && lineNumber < DOC_SIZE){
            testData[lineNumber] = stoi(dataString);
            lineNumber++;
        }
    }

/*********** TIMING ANALYSIS BEGIN *******************/
    float insert[100];
    float sort[100];
    auto start  = steady_clock::now();
    auto startMaster  = steady_clock::now();
    ofstream outputCSV("Heap_timing_analysis.csv");
    outputCSV << "Insert" << ',' << "Sort" << endl;

    heapSort myHeap(DOC_SIZE);

    for(int i = 0; i < 100; i++){
        //cout << i << endl;
        //Begin insert timing
        start = steady_clock::now();
        for(int j = 0; j < 100; j++)
            myHeap.insert(testData[(i * 100) + j]);
        insert[i] = duration_cast<nanoseconds>(steady_clock::now() - start).count() / 100;

        //Begin sort timing
        start = steady_clock::now();
        myHeap.heapify();
        sort[i] = duration_cast<nanoseconds>(steady_clock::now() - start).count() / 100;

        outputCSV << insert[i] << ',' << sort[i] << endl;
    }
    cout << (float)duration_cast<microseconds>(steady_clock::now() - startMaster).count() / 1000000 << " seconds to complete.\n";
    //myHeap.display(0, 500);
/*********** TIMING ANALYSIS END *******************/
    return 0;
}