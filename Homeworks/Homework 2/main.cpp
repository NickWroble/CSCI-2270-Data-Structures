#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct wordRecord {
    string word;
    int count;
};

//Function declarations
//Function completed, runs in coderunner
void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]);

//Function completed, runs in coderunner
bool isIgnoreWord(string word, string ignoreWords[]);

//Function completed, runs in coderunner
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length);

void sortArray(wordRecord distinctWords[], int length);

//Function completed, runs in coderunner
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords);

//double d'at d'array
void doubleArray(wordRecord *&array, int *length);

//checks if word was already inseted into array. If so, returns index of the repeated word to main and increments array[x].count
bool isInserted(wordRecord array[], string word, int numWords);

//self explanatory
void sortArray(wordRecord array[], int length);
//End function declarations

int main(int argc, char * argv[]){
    if(argc != 4){//check if good input
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return 0;
    }
    int N = stoi(argv[1]); 
    ifstream inputWordFile;
    inputWordFile.open(argv[2]);
    if(!inputWordFile.is_open()){ //check if good open
        cout << "Failed to open " << argv[2] << endl;
        return 0;
    }
    string ignoreWordsList[50]; //array for ignore words
    getIgnoreWords(argv[3], ignoreWordsList); //stores ignoreWords.txt into the array
    int arrayDoubleCount = 0; //self explanatory 
    int uniqueWordCount = 0; //counts number of non repeating non ignore words
    int nonIgnoreCount = 0; //counts number of non ignore words
    int wordRecordSize = 100; //length of the dynamic array
    wordRecord *inputWords = new wordRecord[wordRecordSize]; //variable array for unique words
    for(int i = 0; i < 100; i++) inputWords[i].count = 0; //int the counts of the unique words
    string currentLine, currentWord; //used for ifstream   
    while(inputWordFile >> currentLine){//reading unitl eof
        stringstream ss(currentLine); 
        while(ss >> currentWord){//while currentLine still contains words
            if(isIgnoreWord(currentWord, ignoreWordsList)) continue; //if word is on ignoreWords.txt, don't do rest of stuff in while loop
            nonIgnoreCount ++; //increments the count of all non ignore words
            if(isInserted(inputWords, currentWord, uniqueWordCount)) continue; //if the word was repeated, increment array[x].count and continue while loop
            uniqueWordCount++; //word is not ignored or repeated, increment dis count
            if(wordRecordSize == uniqueWordCount){ //check if array needs to be doubled
                doubleArray(inputWords, &wordRecordSize);
                arrayDoubleCount++;
            } 
            //insert into inputWords if word is nonignore and new
            inputWords[uniqueWordCount - 1].word = currentWord; //must decrement array index cuz arrays start a 0
            inputWords[uniqueWordCount - 1].count++;
        }     
    }
    sortArray(inputWords, uniqueWordCount); //I wonder what this does
    cout << "Array doubled: " << arrayDoubleCount << endl;
    cout << "Distinct non-common words: " << uniqueWordCount << endl;
    cout << "Total non-common words: " << nonIgnoreCount<< endl;
    printTenFromN(inputWords, N, nonIgnoreCount);
    inputWordFile.close();
    delete [] inputWords;
    return 0;
}

//Function completed, runs in coderunner
void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]){
    ifstream inputFile;
    inputFile.open(ignoreWordFileName);
    if (!inputFile.is_open()) {
        cout << "Failed to open " << ignoreWordFileName << endl;
        return;
    }
    string line;
    for(int i = 0; i < 50; i++){
        getline(inputFile, line);
        line.erase(remove(line.begin(), line.end(), '\r'), line.end() ); // clears "/r" from end of string, was causing problems when comparing to a string later in program
        //https://stackoverflow.com/questions/2528995/remove-r-from-a-string-in-c
        ignoreWords[i] = line.c_str();
       
    }
    inputFile.close();
    return;
}

//Function completed, runs in coderunner
bool isIgnoreWord(string word, string ignoreWords[]){
     for(int i = 0; i < 50; i++){
         if (word == ignoreWords[i]) return true;
     }
     return false;
}

//Function completed, runs in coderunner
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length){
    int numberOfWords = 0;
    for(int i = 0; i < length; i++){
        numberOfWords += distinctWords[i].count;
    }
    return numberOfWords;
}

//Function completed, runs in coderunner
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords){
    cout << "Probability of next 10 words from rank " << N << endl;
    cout << "---------------------------------------" << endl;
    for(int i = N; i < N + 10; i++){
        printf("%.5f", (float)distinctWords[i].count/totalNumWords); //prints to 5 decimals
        cout<<" - " << distinctWords[i].word << endl;;
    }
    return;
}

void doubleArray(wordRecord *&array, int *length){
    //length is ptr so can be returned to main for cout later
    wordRecord *newArray = new wordRecord[*length * 2];
    for(int i = 0; i < *length; i++) newArray[i] = array[i]; //copy old array over to first half of new array
    for(int i = *length; i < *length * 2; i++) newArray[i].count = 0; //init new counts of the words
    delete [] array;
    array = newArray;
    *length = *length * 2;
}

bool isInserted(wordRecord array[], string currentWord, int numWords){
    for(int i = 0; i < numWords + 1; i++){
        if(array[i].word == currentWord){
            array[i].count++;
            return 1;
        }
    }
    return 0;
}

void sortArray(wordRecord array[], int length){
    for(int j = 1; j < length; j++){//sort alphabetically first
        wordRecord originalAplha = array[j];
        int i = j - 1;
        while(i >= 0 && array[i].word > originalAplha.word){
            array[i + 1] = array[i];
            i--;
        array[i + 1] = originalAplha;
        }
    }
    for(int j = 1; j < length; j++){// then sort based on word count
        wordRecord originalNumer = array[j];
        int i=j-1;
        while(i >= 0 && array[i].count < originalNumer.count){
            array[i + 1] = array[i];
            i--;
        array[i + 1] = originalNumer;
        }
    }
}