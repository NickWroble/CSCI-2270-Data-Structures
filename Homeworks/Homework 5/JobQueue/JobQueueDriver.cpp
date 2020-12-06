/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
#include <string>
#include<iomanip>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[]){
	JobQueue myQueue;
	string stringInput; //for user input of type string
	int intInput;		//for user input of type int
	while(true){
		menu();
		cin >> intInput; 	//gets option menu number
		switch (intInput){	//switch from 1, 2, 3
		case 1:
			cout << "Enter the number of jobs to be created:" << endl;
			cin >> intInput;
			for (int i = 0; i < intInput; i++){
				cout << "job" << i + 1 << ":" << endl; 
				cin >> stringInput;
				myQueue.enqueue(stringInput);
			}
			break;
		case 2:
			cout << "Enter the number of jobs to be dispatched:" << endl;
			cin >> intInput;
			for (int i = 0; i < intInput; i++){
				if(myQueue.isEmpty()){
					cout<< "No more jobs to be dispatched from queue" << endl;
					break;
				}
				cout << "Dispatched: " << myQueue.peek() << endl;
				myQueue.dequeue();
			}
			break;
		case 3:
			cout << "Number of jobs in the queue:" << myQueue.queueSize();
			return 0;
		default:
			return -1;
		}
	}
}
