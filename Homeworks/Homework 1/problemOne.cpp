#include<iostream>

#include<fstream>

#include<string>

using namespace std;

int addToArrayAsc(float sortedArray[], int numElements, float newValue) {
  if (numElements < 0 || numElements > 100) {
      cout<<"numele error"<<endl;
      return -1; //check if bad input
  }
  //cout<<numElements<<endl;
  float tempArray[100];
  int i = 0;
  while (sortedArray[i ] < newValue && i < numElements){ //store all values less than newValue
    tempArray[i] = sortedArray[i];
    i++;
  }
  tempArray[i] = newValue; //store newValue where it should go 
  i++;
  for (i; i < numElements + 1; i++) tempArray[i] = sortedArray[i - 1]; //resume storing values larger than newValue
  for (i = 0; i < numElements + 1; i++) sortedArray[i] = tempArray[i]; //store values back into sorted array
  for (i = 0; i < numElements; i++) { //print them out
    cout << tempArray[i] << ",";
  }
  cout << tempArray[i] << endl;

  /*
  static float * first(&sortedArray[0]); //get memory address of first index of sortedArray
  static float * last(first + numElements + 1); //get memory address of last index of sortedArray based on numElements
  sort(first, last); //sort from first point to last pointer
  int i;
  for (i = 0; i < numElements; i++) cout << sortedArray[i] << ",";//print out floats
  cout << sortedArray[i] << endl;
  */
  return numElements++;
}

int main(int argc, char ** argv) {
  //checking for good input
  string fileName = argv[1]; //storing commandline argument into fileName var

  ifstream inputFile(fileName);

  if (inputFile.fail()) { //check if failed fstream input
    cout << "Failed to open the file." << endl;
  } else if (!inputFile.is_open()) { //check if failed fstream input
    cout << "Failed to open the file." << endl;
  } else {

    //end checking good input

    //storing numbers into unsortedFloats  
    ///*
    float unsortedFloats[100];
    int i = 0;
    string line;
    while (!inputFile.eof()) {
      line = ""; //emtpy string to store each line of inputFile into
      getline(inputFile, line); //gets the current line of input1.txt

      unsortedFloats[i] = stof(line); //converts current line contents into float and stores into unsorted floats
      i++;
    }

    inputFile.close();
    //*/
    //i = 20; //uncomment so input1.txt doesn't print all 100 lines
    //float unsortedFloats[] = {20.2,15};
    //i = 2;
    for (int j = 0; j < i; j++) { //goes through unsortedFloats and sorts them
      addToArrayAsc(unsortedFloats, j, unsortedFloats[j]);
    }
  }
  return 0;
}