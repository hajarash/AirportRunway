/*--- LQueue.cpp ----------------------------------------------------------
 This file implements LQueue member functions.
 From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
 by Larry Nyhoff
 -------------------------------------------------------------------------*/
#include <iostream>

//using namespace std;

#include "LQueue.h"






//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
    myFront = myBack = 0;
    if (!original.empty())
    {
        // Copy first node
        myFront = myBack = new Queue::Node(original.front());
        
        // Set pointer to run through original's linked list
        Queue::NodePointer origPtr = original.myFront->next;
        while (origPtr != 0)
        {
            myBack->next = new Queue::Node(origPtr->data);
            myBack       = myBack->next;
            origPtr      = origPtr->next;
        }
    }
}

//--- Definition of Queue destructor
Queue::~Queue()
{
    // Set pointer to run through the queue
    Queue::NodePointer prev = myFront,
    ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
    if (this != &rightHandSide)         // check that not q = q
    {
        this->~Queue();                  // destroy current linked list
        if (rightHandSide.empty())       // empty queue
            myFront = myBack = 0;
        else
        {                                // copy rightHandSide's list
            // Copy first node
            myFront = myBack = new Queue::Node(rightHandSide.front());
            
            // Set pointer to run through rightHandSide's linked list
            Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
            while (rhsPtr != 0)
            {
                myBack->next = new Queue::Node(rhsPtr->data);
                myBack = myBack->next;
                rhsPtr = rhsPtr->next;
            }
        }
    }
    return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{
    return (myFront            == 0);
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
    Queue::NodePointer newptr = new Queue::Node(value);
    if (empty())
        myFront = myBack = newptr;
    else
    {
        myBack->next = newptr;
        myBack = newptr;
    }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
    Queue::NodePointer ptr;
    for (ptr = myFront; ptr != 0; ptr = ptr->next)
        out << ptr->data << "  ";
    out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
    if (!empty())
        return (myFront->data);
    else
    {
        return 0;
    }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
    if (!empty())
    {
        Queue::NodePointer ptr = myFront;
        myFront = myFront->next;
        delete ptr;
        if (myFront             == 0)     // queue is now empty
            myBack = 0;
    }
    else
        cerr << "*** Queue is empty -- can't remove a value ***\n";
}

//--- Definition of move_to_front

void Queue::move_to_front(const QueueElement & moveIt)
{
    
    if (!empty())
    {
        Queue::NodePointer preNode = myFront;
        if (myFront->data     == moveIt)
        {
            return;
        }
        else
        {
            Queue::NodePointer tmp = myFront->next;
            while (tmp != NULL)
            {
                if (tmp->data == moveIt)
                {
                    preNode->next = tmp->next;
                    tmp->next = myFront;
                    myFront = tmp;
                    return;
                }
                preNode = preNode->next;
                tmp = tmp->next;
            }
        }
        
    }
    else
    {
        cerr << "*** Queue is empty -- can't remove a value ***\n";
    }
}


int Queue::getSize()
{
    int size = 0;
    if (this->empty())
        return size;
    Queue::NodePointer q1 = this->myFront;
    while (q1 != NULL)
    {
        size++;
        q1 = q1->next;
    }
    
    return size;
    
}
void Queue::merge_two_queues(Queue& anotherQueue)
{
    Queue::NodePointer q1 = this->myFront;
    Queue::NodePointer q2 = anotherQueue.myFront;
    Queue::NodePointer q1Prev = this->myFront;
    
    if (empty() && anotherQueue.empty())
    {
        cerr << "Both queues are empty";
        return;
    }
    while (q1 != NULL && q2 != NULL)
    {
        if (q1 == this->myFront)
        {
            if (q1->data < q2->data)
            {
                q1 = q1->next;
            }
            else
            {
                Queue::NodePointer newptr = new Queue::Node(q2->data);
                newptr->next = q1;
                this->myFront = newptr;
                q1 = this->myFront;
                anotherQueue.dequeue();
                q2 = anotherQueue.myFront;
            }
        }
        else
        {
            if (q1->data < q2->data)
            {
                q1Prev = q1;
                q1 = q1->next;
            }
            else
            {
                Queue::NodePointer newptr = new Queue::Node(q2->data);
                newptr->next = q1;
                q1Prev->next = newptr;
                q1Prev = q1Prev->next;
                anotherQueue.dequeue();
                q2 = anotherQueue.myFront;
            }
        }
    }
    if (anotherQueue.empty())
    {
        return;
    }
    else 
    {
        while (!anotherQueue.empty())
        {
            this->enqueue(anotherQueue.myFront->data);
            anotherQueue.dequeue();
        }
    }
}
