#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct studentData {
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};

char calcLetter(double avg){
  if(avg >= 90) return 'A';
  else if(avg >= 80) return 'B';
  else if(avg >= 70) return 'C';
  else if(avg >= 60) return 'D';
  else return 'F';
}

void printList(const studentData students[], int length){
  for(int i = 0; i < length; i++) {
    if(students[i].studentName == "") return;
    cout<<students[i].studentName<<" earned "<<students[i].average<<" which is an "<<calcLetter(students[i].average)<<endl;}
}

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length)
{
  students[length].studentName = studentName;
  students[length].homework = homework;
  students[length].recitation = recitation;
  students[length].quiz = quiz;
  students[length].exam = exam;
  students[length].average = ((double)(homework+recitation+exam+quiz))/4;
}

int main(int argc, char* argv[])
{
    if (argc != 5) {
        cout << "Command line format: <inputFile> <outputFile> <lowerBound> <upperBound>" << endl;
        return 0;
    }
    else {
        string inputFileName = argv[1];
        string outputFileName = argv[2];
        char lowerBound = argv[3][0];
        char upperBound = argv[4][0];
        //cout<<inputFileName<<outputFileName<<lowerBound<<upperBound<<endl;

        ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            cout << "File open error." << endl;
            return 0;
        }
        string line, name, temp;
        int homework, quiz, recitation, exam;
        studentData students[10];
        int length = 0;
        while (length < 10 && !inputFile.eof()) {
            getline(inputFile, line);
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, temp, ',');
            stringstream homeworkData;
            homeworkData << temp;
            homeworkData >> homework;

            getline(ss, temp, ',');
            stringstream recitationData;
            recitationData << temp;
            recitationData >> recitation;

            getline(ss, temp, ',');
            stringstream quizData;
            quizData << temp;
            quizData >> quiz;

            getline(ss, temp, ',');
            stringstream examData;
            examData << temp;
            examData >> exam;
            // insert the data into the array
            addStudentData(students, name, homework, recitation, quiz, exam, length);
            length++; // increment the length
        }
        inputFile.close();
        printList(students, length);
        char grade;
        ofstream outputFile(outputFileName);
        for(int i = 0; i < length; i++){
          grade = calcLetter(students[i].average);
          if(i >= length) break;
          if(grade <= lowerBound && grade >= upperBound){
            //cout<<"test"<<endl;
            if(students[i].studentName == "") break;
            outputFile<<students[i].studentName<<","<<students[i].average<<","<<grade<<endl;
          }
        }
        outputFile.close();
        return 0;
    }
}

