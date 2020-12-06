#include "dll.hpp"

#define DOC_SIZE 10000

int main(int argc, char *argv[]){
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
    float search[100];
    auto start = steady_clock::now();
    auto startMaster = steady_clock::now();

    int searchRandom[100];

    ofstream outputCSV("DLL_timing_analysis.csv");
    outputCSV << "Insert" << ',' << "Search" << endl;
    
    DLL myDLL;
    for(int i = 0; i < 100; i++){
        //Begin insert timing
        start = steady_clock::now();
        for(int j = 0; j < 100; j++)
            myDLL.insert(testData[(i * 100) + j]);
        insert[i] = duration_cast<nanoseconds>(steady_clock::now() - start).count() / 100;

        //Begin search timing
        for(int j = 0; j < 100; j++)
            searchRandom[j] = rand() % (100 * (i + 1));
        start = steady_clock::now();
        for(int j = 0; j < 100; j++)
            myDLL.search(testData[searchRandom[j]]);
        search[i] = duration_cast<nanoseconds>(steady_clock::now() - start).count() / 100;

        outputCSV << insert[i] << ',' << search[i] << endl; 
    }
    cout << (float)duration_cast<microseconds>(steady_clock::now() - startMaster).count() / 1000000 << " seconds to complete.\n";

/*********** TIMING ANALYSIS END *******************/
    return 0;
}