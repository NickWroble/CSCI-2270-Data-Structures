#include<string>
#include"JobQueue.hpp"
#include<iostream>
using namespace std;

JobQueue::JobQueue(){ //inits JobQueue
  queueEnd = 0;
  queueFront = 0;
  counter = 0;
}

bool JobQueue::isEmpty(){ //I wonder what this does
  if(counter == 0)
    return true;
  return false;
}
bool JobQueue::isFull(){ //if counter > 0 and queueFront and queueEnd are at the same index, queue is full
  if(counter > 0 && (queueFront == queueEnd))
    return true;
  return false;
}

void JobQueue::enqueue(std::string job){ //puts element at end of queue
  if(isFull()){ //check if full
    cout << "Queue full, cannot add new job" << endl;
    return;
  }
  queue[queueEnd] = job; //else add the element to the queue
  if(queueEnd == (SIZE - 1)) //if element inserted at end of queueArray, make queueFront point to index 0
    queueEnd = 0;
  else //else increment queueEnd index
    queueEnd++;
  counter++;
}
void JobQueue::dequeue(){
  if(isEmpty()){
    cout << "Queue empty, cannot dequeue a job" << endl;
    return;
  }
  if(queueFront == SIZE - 1) //if the front of the queue is at the end of the circular array
    queueFront = 0;
  else
    queueFront++; //else increment queueFront index
  counter--;
}
string JobQueue::peek(){
  if(isEmpty()){ 
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
  return queue[queueFront];
}
int JobQueue::queueSize(){
  return counter;
} 