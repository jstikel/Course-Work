//Code taken from the textbook with slight modifications

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <memory>
#include <cstdlib>
using namespace std;

 class Queue
 {
    struct QueueNode
    {      
      char value;
       QueueNode *next;
       QueueNode(char value1, QueueNode *next1 = nullptr)
      {
          value = value1;
         next = next1;
      }
    };
    // These track the front and rear of the queue
    QueueNode *front;
    QueueNode *rear;
 public:
    // Constructor and Destructor
    Queue();
    ~Queue();
 
    // Member functions
    void enqueue(char);
    void dequeue(char &);
    bool isEmpty() const;
    bool isFull() const;
    void clear();
 };
#endif