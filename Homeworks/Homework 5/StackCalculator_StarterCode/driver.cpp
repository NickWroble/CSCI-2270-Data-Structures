#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"
#include<string>

using namespace std;



int main()
{
  // stack to hold the operands
  StackCalculator stack;

  int numElement = 0;
  string* inparr = new string[50];

  // enter a number
  string number;
  cout << "Enter the operators and operands ('+', '*') in a prefix format" << endl;
  
  while(true)
  {
    cout << "#> ";
    getline(cin, number);
    if(number == "="){ //check if user wants to evaluate expression
      if(numElement == 0){ //if no elements inside inparr
        cout << "No operands: Nothing to evaluate" << endl;
        return 0;
      }
      if(!stack.evaluate(inparr, numElement)) //check if evaluate() was successful
        return 0;
      cout << "Result= " << stack.peek()->number << endl; //print the result
      return 0;
    } 
    inparr[numElement] = number; //else store the element in inparr and numElement++
    numElement++;
  }
  return 0;
}
