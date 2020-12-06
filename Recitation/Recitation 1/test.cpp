#include <iostream>
#include<fstream>
using namespace std;

void increment(int &a){
    a++;
    cout << a <<endl;
}

int main(int argc, char* argv[]){
    ofstream outputFile;

    outputFile.open("sample.txt");
    outputFile<<"This is my first line";
    outputFile<<"This is my second line";
    outputFile.close();

    ifstream inputFile("sample.txt");
    char text[50];
    inputFile.getline(text, 50);
    inputFile.getline(text, 50);

    cout << text << endl;
}