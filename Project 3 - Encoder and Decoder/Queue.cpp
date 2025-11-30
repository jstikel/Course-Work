//This code is taken from the Textbook with slight modifications

#include <iostream>
#include "Queue.h"
#include <cstdlib>
using namespace std;

Queue::Queue()
{
    front = nullptr;
    rear = nullptr;
}

Queue::~Queue()
{
    QueueNode *garbage = front;
    while (garbage != nullptr)
    {
        front = front->next;
        garbage->next = nullptr;
        delete garbage;
        garbage = front;
    }
}

void Queue::enqueue(char num)
{
    if (isEmpty())
    {
        front = new QueueNode(num);
        rear = front;
    }
    else
    {
        rear->next = new QueueNode(num);
        rear = rear->next;
    }
}

void Queue::dequeue(char &num)
{
    QueueNode *temp = nullptr;
    if (isEmpty())
    {
        cout << "The queue is empty.\n";
        exit(1);
    }
    else
    {
        num = front->value; //Get the value of the front node
        temp = front;
        front = front->next; //Move the front pointer to the next node
        delete temp; 
    }
}

bool Queue::isEmpty() const //Simply checks to see if the queue is empty or not
{
    if (front == nullptr)
        return true;
    else
        return false;
}

bool Queue::isFull() const //Checks to make sure that there are less than 100 items in the queue, and if not, it returns true
// This is a simple check to see if the queue is full. It does not check for memory allocation errors.
{
    QueueNode *temp;
    try
    {
        temp = new QueueNode(0); //If there is not enough memory, this will throw an exception
        delete temp;
        int count = 0;
        QueueNode *current = front;
        while (current != nullptr) //iterate through the queue and count the number of items
        {
            count++;
            if (count >= 100)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    catch (const std::bad_alloc&)
    {
        return true;
    }
}

void Queue::clear()
{
    char value;
    while (!isEmpty())
        dequeue(value);
}
