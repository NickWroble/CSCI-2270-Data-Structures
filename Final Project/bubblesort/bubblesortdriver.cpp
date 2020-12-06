#include "bubblesort.hpp"

#define TABLE_SIZE 40009
#define DOC_SIZE 10000

int main(int argc, char* argv[]){\
    int testData[DOC_SIZE];

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cout << "File open error." << endl;
        return -1;
    }
    string line, dataString;
    int lineNumber = 0;
    while(getline(inputFile, line) && lineNumber < TABLE_SIZE){
        istringstream myline(line);
        while(getline(myline, dataString, ',') && lineNumber < TABLE_SIZE){
            testData[lineNumber] = stoi(dataString);
            lineNumber++;
        }
    }

/*********** TIMING ANALYSIS BEGIN *******************/
    float insert[100];
    float sort[100];
    auto start  = steady_clock::now();
    auto startMaster  = steady_clock::now();
    ofstream outputCSV("Bubble_timing_analysis.csv");
    outputCSV << "Insert" << ',' << "Sort" << endl;
    BubbleSort myBubble(DOC_SIZE);
    for(int i = 0; i < 100; i++){
        //Begin insert timing
        start = steady_clock::now();
        for(int j = 0; j < 100; j++)
            myBubble.insert(testData[(i * 100) + j]);
        insert[i] = duration_cast<nanoseconds>(steady_clock::now() - start).count() / 100;

        //Begin sort timing
        start = steady_clock::now();
        myBubble.sort();
        sort[i] = duration_cast<nanoseconds>(steady_clock::now() - start).count() / 100;

        outputCSV << insert[i] << ',' << sort[i] << endl;
    }
    cout << (float)duration_cast<microseconds>(steady_clock::now() - startMaster).count() / 1000000 << " seconds to complete.\n";
    //myBubble.display(0, 30);
/*********** TIMING ANALYSIS END *******************/
    return 0;
}