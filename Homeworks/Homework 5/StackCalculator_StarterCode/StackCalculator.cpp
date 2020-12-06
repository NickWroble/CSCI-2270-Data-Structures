#include <iostream>
#include "StackCalculator.hpp"
#include <string>


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' && !point) 
        point = true;
      else if(s[i]=='.' && point) 
        return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  //TODO:
  stackHead = nullptr;
}

StackCalculator::~StackCalculator()
{
  while(!isEmpty())
    pop();
}

bool StackCalculator::isEmpty()
{ 
  if(stackHead == NULL) 
    return true;
  return false;
}

void StackCalculator::push(float number)
{
  Operand * newNumber = new Operand;
  newNumber->number = number;
  newNumber->next = stackHead;
  stackHead = newNumber;
}

void StackCalculator::pop()
{
	//TODO:
  if(isEmpty()){ //if empty stack
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }
  if(stackHead->next == NULL){ //if only one node on stack
    free(stackHead);
    stackHead = nullptr;
    return;
  }
  Operand * newHead = stackHead->next; //passed all checks
  free(stackHead);
  stackHead = newHead;
}

Operand* StackCalculator::peek()
{
  if(!isEmpty()){
    return stackHead;
  }
  cout << "Stack empty, cannot peek." << endl;
    return nullptr;
}

bool StackCalculator:: evaluate(string* s, int size)
{
    /*TODO: 1.scan the array from the end
            2.Use isNumber function to check if the input is an operand
            3.push all operands to the stack
            4.If operator take two element of from the stack,
              compute and put the result back in stack
            5.Handle the boundery cases as required.
            6.Read the writeup for more details
    */
  float operandOne;
  float operandTwo;
  for(int i = size - 1; i > -1; i--){
    if(isNumber(s[i]))      
      push(stof(s[i]));
    else if(s[i] == "+" || s[i] == "*"){
      if(isEmpty()){
        cout << "err: not enough operands" << endl;
        return false;
      }
      operandOne = peek()->number;
      pop();
      if(isEmpty()){
        cout << "err: not enough operands" << endl;
        push(operandOne);
        return false;
      }
      operandTwo = peek()->number;
      pop();
      if(s[i] == "+")
        push(operandOne + operandTwo);
      else
        push(operandOne * operandTwo);
      continue;
    }
    else if(s[i] == "=")
      return true;
    else{
      cout << "err: invalid operation" << endl;
      return false;
    }
  }
  return false;
}
