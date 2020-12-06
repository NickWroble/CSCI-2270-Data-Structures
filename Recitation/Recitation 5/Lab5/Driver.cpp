#include <iostream>
#include "StackLL.hpp"

using namespace std;
bool isValid(string input){
    StackLL stack;
    char x;
    for(int i = 0; i < input.length(); i++){
        if(input[i] == '(' || input[i] == '{' || input[i] == '[')
            stack.push(input[i]);
        if(stack.isEmpty())
            return false;
        switch(input[i]){
            case ')':
                if(stack.peek() == '(')
                    stack.pop();
                else
                    return false;
                break;
                
            case '}':
                if(stack.peek() == '{')
                    stack.pop();
                else
                    return false;
                break;
                
            case ']':
                if(stack.peek() == '[')
                stack.pop();
                else
                    return false;
                break;
        }
    }
return(stack.isEmpty());
}

int main()
{
  int choice;
  while(1)
  {
    cout << "--------------------------------------------------------" << endl;
    cout << "Examine if the pairs and the orders of “{“,”}”,”(“,”)”,”[“,”]” are correct." << endl<< endl;
    cout << "1. Enter the string to be validated  "<< endl;
    cout << "2. Quit  " << endl;
    cout << "--------------------------------------------------------" << endl;

    cout << "Choice: ";
    cin >> choice;
    cout << endl;
    string input;
    switch(choice)
    {
      case 1:

            cout << "Enter the string to be validated: ";
            cin >> input;
            if (isValid(input))
                cout << "------- Balanced ------ "<< endl;
            else
                cout << "------- Not Balanced -------"<< endl;
            break;
      case 2:
            return 0;
      default:
            cout << "------- Oops! Wrong choice ------ " << endl;
            return 0;
    }
  }
    return 0;




}
